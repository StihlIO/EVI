/*

Copyright 2023 Lukashevich Daniil

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "EviModel.h"

#include "OCPP/Ocpp16Messages.h"

void EviModel::AddMethod2Translator(const QString &methodName, std::function<OCPP16Origin *(const QJsonObject &)> calling)
{
    translate2Method.insert(methodName, calling);
}

void EviModel::InitTranscriptor()
{
    AddMethod2Translator("RemoteStopTransaction", [this](const QJsonObject & obj) {
        return RemoteStop(std::move(RemoteStopTransaction(obj)));
    });
    AddMethod2Translator("RemoteStartTransaction", [ this ](const QJsonObject & obj) {
        return RemoteStart(std::move(RemoteStartTransaction(obj)));
    });
}

RemoteStopTransactionResp* EviModel::RemoteStop(const RemoteStopTransaction &&rst)
{
    RemoteStopTransactionResp *conf = nullptr;
    //for(auto:connector) looks better
    auto chargingConnector = std::find_if(std::begin(connectors), std::end(connectors), [&rst](auto c) {
        return c->Transaction() == rst.TransactionId() &&
               (c->Current() == ConnectorModel::State::Charging || c->Current() == ConnectorModel::State::Authorized);
    });
    if(chargingConnector != std::end(connectors)) {
        (*chargingConnector)->ForceStopCharging();
        conf = new RemoteStopTransactionResp(OCPP16_RemoteStartStopStatus::Accepted);
        return conf;
    }
    conf = new RemoteStopTransactionResp(OCPP16_RemoteStartStopStatus::Rejected);
    return conf;
}

RemoteStartTransactionResp *EviModel::RemoteStart(const RemoteStartTransaction &&rst)
{
    RemoteStartTransactionResp *conf = nullptr;
    if(connectors.contains(rst.Connector())) {
        auto c = connectors[rst.Connector()];
        if(c->IsCanStart() && rst.IsValid()) {
            int limit = 0;
            if(rst.Profile().Schedule().SchedulePeriod().count()) {
                limit = rst.Profile().Schedule().SchedulePeriod()[0].Limit();
            }
            qDebug() << "RemoteStart for connector" << rst.Connector() << "with limit" << limit;
            EnrollTransaction(rst.IdTag(), c->Id(), limit, nullptr);
            conf = new RemoteStartTransactionResp(OCPP16_RemoteStartStopStatus::Accepted);
            return conf;
        }
    }
    conf = new RemoteStartTransactionResp(OCPP16_RemoteStartStopStatus::Rejected);
    return conf;
}

ConnectorModel *EviModel::FindConnector(int connectorId)
{
    if(connectorId == 0) {
        ConnectorModel *lastConenctor = nullptr;
        int connectorsInEv = std::count_if(std::begin(connectors), std::end(connectors), [&lastConenctor](auto c) {
            if(c->Current() == ConnectorModel::State::Connected2EV) {
                lastConenctor = c;
                return true;
            }
            return false;
        });
        if(connectorsInEv == 1) {
            return lastConenctor;
        }
    } else if(connectors.contains(connectorId)) {
        return connectors[connectorId];
    }
    return nullptr;
}

void EviModel::Invoke(const OCPP16Origin *unit, std::function<void (const QJsonObject &)> onResponce) const
{
    OcppCore16::I()->MakeMessage(furl, unit, onResponce);
}

void EviModel::EnrollTransaction(QString tagId, int connectorId, int limit, std::function<void (bool)> isAuth)
{
    Q_UNUSED(isAuth);
    auto auth = Authorize(tagId);
    Invoke(&auth, [ =, this ](const QJsonObject & obj) {
        auto sobj = AuthorizeResp(obj);
        if(sobj.IsValid() && sobj.getIdTagInfo().status == OCPP16_AuthorizationStatus::Accepted) {
            auto connector = FindConnector(connectorId);
            if(connector != nullptr) {
                auto start = StartTransaction(connector->Id(), tagId, connector->Meter());
                Invoke(&start, [ =, this ](const QJsonObject & obj) {
                    auto sobj = StartTransactionResp(obj);
                    if(sobj.IsValid() && sobj.getIdTagInfo().status == OCPP16_AuthorizationStatus::Accepted) {
                        connector->EnrollTransaction(sobj.getTransactionId(), tagId, limit);
                    }
                });
            }
        }
    });
}

EviModel::EviModel(const QString &name, const QString &furl, const QString &model, const QString &vendor)
{
    this->name = name;
    this->furl = furl;
    this->model = model;
    this->vendor = vendor;
    Connected = false;
    InitTranscriptor();
}

void EviModel::ChangeUrl(const QString &newUrl)
{
    furl = newUrl;
}

QString EviModel::getFurl() const
{
    return furl;
}

bool EviModel::IsConnected() const
{
    return Connected;
}

void EviModel::Disconnect() const
{
    OcppCore16::I()->Disconnect(furl);
}

void EviModel::SendRawStatus(int connectorId, OCPP16_Status status, OCPP16_ErrorValue error, std::function<void()> onResp) const
{
    StatusNotification statusNotif(connectorId, error, status);
    Invoke(&statusNotif, [ onResp ](auto) {
        onResp();
    });
}

void EviModel::HeartBeat() const
{
    Heartbeat hb;
    Invoke(&hb, nullptr);
}

void EviModel::Enable(std::function<void(bool)> onConnectionChange)
{
    auto onConnected = [ onConnectionChange, this ](bool isConnected) {
        Connected = isConnected;
        onConnectionChange(Connected);
    };
    auto unpendingMessage = [ this ](const QString & action, const QJsonObject & obj) -> OCPP16Origin* {
        if(translate2Method.contains(action))
        {
            return translate2Method[action](obj);
        }
        return nullptr;
    };
    OcppCore16::I()->Start(furl, onConnected, unpendingMessage);
    OcppCore16::I()->Connect(furl);
}

void EviModel::Boot(std::function<void(const QString &, int interval)> bootResp) const
{
    auto boot = BootNotification(model, vendor);
    Invoke(&boot, [ bootResp ](const QJsonObject & obj) {
        BootNotificationResp bnotif(obj);
        bootResp(bnotif.Status(), bnotif.Interval());
    });
}

int EviModel::AddConnector(ConnectorModel *connector)
{
    int id = connectors.count() + 1;
    connector->SetId(id);
    connectors.insert(id, connector);
    connector->OnStateChange(this, [ connector, this ](ConnectorModel::State newState) {
        int id = connector->Id();
        StatusNotification statusNotif(id, OCPP16_ErrorValue::NoError, OCPP16_Status::Available);
        switch(newState) {
            case ConnectorModel::State::Undefined:
                statusNotif = StatusNotification(id, OCPP16_ErrorValue::OtherError, OCPP16_Status::Unavailable);
                break;
            case ConnectorModel::State::Faulted:
                statusNotif = StatusNotification(id, OCPP16_ErrorValue::OtherError, OCPP16_Status::Faulted);
                break;
            case ConnectorModel::State::OnPost:
                break;
            case ConnectorModel::State::Connected2EV:
                statusNotif = StatusNotification(id, OCPP16_ErrorValue::NoError, OCPP16_Status::Preparing);
                break;
            case ConnectorModel::State::Authorized:
            case ConnectorModel::State::Charging:
                statusNotif = StatusNotification(id, OCPP16_ErrorValue::NoError, OCPP16_Status::Charging);
                break;
            case ConnectorModel::State::OnPostAuthClr:
            case ConnectorModel::State::InEVButChargeDone: {
                statusNotif = StatusNotification(id, OCPP16_ErrorValue::NoError, OCPP16_Status::Finishing);
                auto stop = StopTransaction(connector->Transaction(), connector->Meter());
                Invoke(&stop, nullptr);
            }
            break;
        }
        Invoke(&statusNotif, nullptr);
    });
    connector->OnMeterChange([ this ](const ConnectorModel * connector, int transactionId, int64_t meterValue) {
        MeterValue mv = MeterValue(QString::number(meterValue));
        MeterValues mvs = MeterValues(connector->Id(), transactionId, QList<MeterValue> {mv});
        Invoke(&mvs, nullptr);
    });
    return id;
}

void EviModel::ClearConnectors()
{
    connectors.clear();
}

QList<ConnectorModel *> EviModel::ConnectorList() const
{
    return connectors.values();
}

void EviModel::AuthTag(QString tagId, std::function<void (bool)> isAuth)
{
    // proper use for(auto:connector) -> no need to check bounds and currentCharging != std::end(connectors)
    auto currentCharging = std::find_if(std::begin(connectors), std::end(connectors), [tagId](auto c) {
        return c->Current() == ConnectorModel::State::Charging && c->TransactionTagId() == tagId;
    });
    if(currentCharging != std::end(connectors)) {
        (*currentCharging)->ForceStopCharging();
        return;
    }
    EnrollTransaction(tagId, 0, 0, isAuth);
}
