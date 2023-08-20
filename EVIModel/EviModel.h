#ifndef EVIMODEL_H
#define EVIMODEL_H

#include "OCPP/OcppCore16.h"
#include "ConnectorModel.h"

#include <QHash>
#include <QList>

class EviModel
{
    QMap<int, ConnectorModel *> connectors;

    QString name;
    QString furl;

    bool Connected;

    QString model;
    QString vendor;

    QHash<QString, std::function<OCPP16Origin*(const QJsonObject &)>> translate2Method;
    void AddMethod2Translator(const QString &methodName, std::function<OCPP16Origin*(const QJsonObject &)> calling);
    void InitTranscriptor();

    RemoteStopTransactionResp *RemoteStop(const RemoteStopTransaction &&rst);
    RemoteStartTransactionResp *RemoteStart(const RemoteStartTransaction &&rst);

    ConnectorModel *FindConnector(int connectorId);

    void Invoke(const OCPP16Origin *unit, std::function<void (const QJsonObject &)> onResponce) const;
    void EnrollTransaction(QString tagId, int connectorId, int limit, std::function<void (bool)> isAuth);

public:

    EviModel(const QString &name, const QString &furl, const QString &model = "EVI Fine 01", const QString &vendor = "Unlimited Foundation");

    void ChangeUrl(const QString &newUrl);
    QString getFurl() const;
    bool IsConnected() const;
    void Disconnect() const;

    QList<ConnectorModel *> ConnectorList() const;
    int AddConnector(ConnectorModel *connector);
    void ClearConnectors();

    void Enable(std::function<void(bool)> onConnectionChange);
    void Boot(std::function<void (const QString &, int)> bootResp) const;
    void SendRawStatus(int connectorId, OCPP16_Status status, OCPP16_ErrorValue error, std::function<void()> onResp) const;

    void HeartBeat() const;

    void AuthTag(QString tagId, std::function<void(bool)> isAuth);
};

#endif // EVIMODEL_H
