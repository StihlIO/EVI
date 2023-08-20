/*

Copyright 2023 Lukashevich Daniil

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "ConnectorModel.h"

#include <QEventLoop>
#include <QList>

int ConnectorModel::DownScale(int current, int possible)
{
    if(possible < 2000) {
        current *= 0.5;
    }
    if(possible < 1000) {
        current *= 0.5;
    }
    if(possible < 500) {
        current *= 0.5;
    }
    return current;
}

void ConnectorModel::StartAuthWatch()
{
    if(authWatcher) {
        authWatcher->deleteLater();
    }
    authWatcher = new QTimer();
    QEventLoop::connect(authWatcher, &QTimer::timeout, [ =, this]() {
        if(Current() == State::Authorized) {
            Set(State::OnPostAuthClr);
            Set(State::OnPost);
        }
        authWatcher->deleteLater();
        authWatcher = nullptr;
    });
    authWatcher->start(10000);
}

void ConnectorModel::StopAuthWatch()
{
    if(authWatcher) {
        authWatcher->deleteLater();
        authWatcher = nullptr;
    }
}

ConnectorModel::ConnectorModel(int64_t meter, int wattPerSec, QString vendorName, int pTypes)
{
    this->meterValue = meter;
    this->wattPerSec = wattPerSec;
    name = vendorName;
    this->possibleTypes = pTypes;
}

void ConnectorModel::SetId(int id)
{
    this->id = id;
}

int ConnectorModel::Id() const
{
    return id;
}

QString ConnectorModel::Name() const
{
    return name;
}

int ConnectorModel::PossibleConnectorTypes() const
{
    return possibleTypes;
}

ConnectorModel::State ConnectorModel::Current() const
{
    return state;
}

void ConnectorModel::Set(ConnectorModel::State state)
{
    this->state = state;
    for(auto c : stateChangeHandlers) {
        c(state);
    }
    if(state == State::Charging) {
        StopAuthWatch();
    }
}

void ConnectorModel::EnrollTransaction(int id, QString tagId, int limit)
{
    CurrentTransaction.transactionId = id;
    CurrentTransaction.transactionTagId = tagId;
    CurrentTransaction.transactionLimit = limit;
    CurrentTransaction.transactionMeterValue = 0;
    if(Current() == State::Connected2EV) {
        Set(State::Charging);
    } else if(IsCanStart()) {
        Set(State::Authorized);
        StartAuthWatch();
    }
}

int ConnectorModel::Transaction() const
{
    return CurrentTransaction.transactionId;
}

QString ConnectorModel::TransactionTagId() const
{
    return CurrentTransaction.transactionTagId;
}

int ConnectorModel::Meter() const
{
    return meterValue;
}

int ConnectorModel::ProcessCharging(int possibleCar)
{
    if(Current() != State::Charging) {
        isTransactionStart = false;
        return 0;
    } else {
        if(!isTransactionStart) {
            elapsedTimer.start();
        }
        isTransactionStart = true;
    }

    double deltaSec = elapsedTimer.elapsed() / 1000.;
    elapsedTimer.restart();

    int charging = wattPerSec * deltaSec;

    int availible = CurrentTransaction.transactionLimit ?
                   CurrentTransaction.transactionLimit - CurrentTransaction.transactionMeterValue :
                   possibleCar;
    int actualPossible = availible > possibleCar ? possibleCar : availible;

    charging = DownScale(charging, possibleCar);
    int acc = actualPossible > charging ? charging : actualPossible;

    meterValue += acc;
    CurrentTransaction.transactionMeterValue += acc;
    if(onMeterChange) {
        onMeterChange(this, CurrentTransaction.transactionId, meterValue);
    }

    if(actualPossible == 0) {
        Set(State::InEVButChargeDone);
    }

    return acc;
}

void ConnectorModel::ForceStopCharging()
{
    if(Current() == State::Charging) {
        Set(State::InEVButChargeDone);
    }
    if(Current() == State::Authorized) {
        Set(State::OnPostAuthClr);
        Set(State::OnPost);
    }
}

bool ConnectorModel::IsCanHandled() const
{
    static const QList<State> accesHandleStates = {State::Undefined, State::OnPost, State::Authorized};
    return accesHandleStates.contains(Current());
}

bool ConnectorModel::IsCanClose() const
{
    static const QList<State> accesCloseStates = {State::Connected2EV, State::InEVButChargeDone};
    return accesCloseStates.contains(Current());
}

bool ConnectorModel::IsCanStart() const
{
    static const QList<State> forbidStartStates = {State::Faulted, State::Charging, State::InEVButChargeDone};
    return !forbidStartStates.contains(Current());
}

void ConnectorModel::SetPowerState(bool state)
{
    if(state) {
        Set(State::OnPost);
    } else {
        Set(State::Faulted);
    }
}

void ConnectorModel::Handle()
{
    if(Current() == State::Authorized) {
        Set(ConnectorModel::State::Charging);
        return;
    }
    Set(ConnectorModel::State::Connected2EV);
}

void ConnectorModel::Close()
{
    Set(ConnectorModel::State::OnPost);
}

void ConnectorModel::OnStateChange(const void *handler, std::function<void (State)> onChange)
{
    stateChangeHandlers.insert(handler, onChange);
}

void ConnectorModel::OnMeterChange(std::function<void (const ConnectorModel *, int, int64_t meterValue)> onMeterChange)
{
    this->onMeterChange = onMeterChange;
}
