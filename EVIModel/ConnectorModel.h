#ifndef CONNECTORMODEL_H
#define CONNECTORMODEL_H

#include "stdint.h"
#include <functional>

#include <QHash>
#include <QTimer>
#include <QString>
#include <QElapsedTimer>

class ConnectorModel
{
    int id;
    QString name;

    int possibleTypes;
    int64_t meterValue;
    int wattPerSec;

    bool isTransactionStart;
    QElapsedTimer elapsedTimer;
    struct Transaction {
        int transactionId;
        int transactionLimit;
        int64_t transactionMeterValue;
        QString transactionTagId;
    } CurrentTransaction;

    QTimer *authWatcher = nullptr;

    int DownScale(int current, int possible);
    void StartAuthWatch();
    void StopAuthWatch();

public:

    enum class State {
        Undefined,
        Faulted,
        OnPost,
        Authorized,
        OnPostAuthClr,
        Connected2EV,
        Charging,
        InEVButChargeDone
    };

    ConnectorModel(int64_t meterValue, int wattPerSec, QString vendorName, int pTypes = 1);
    void SetId(int id);
    int Id() const;
    QString Name() const;
    int PossibleConnectorTypes() const;

    State Current() const;

    void EnrollTransaction(int id, QString tagId, int limit);
    int Transaction() const;
    QString TransactionTagId() const;

    int Meter() const;
    int ProcessCharging(int possibleCar);
    void ForceStopCharging();

    bool IsCanHandled() const;
    bool IsCanClose() const;
    bool IsCanStart() const;

    void SetPowerState(bool state);
    void Handle();
    void Close();

    void OnStateChange(const void *handler, std::function<void(State newState)> onChange);
    void OnMeterChange(std::function<void(const ConnectorModel *, int, int64_t)> onMeterChange);

private:

    void Set(State state);

    State state = State::Undefined;
    QHash<const void *, std::function<void(State newState)>> stateChangeHandlers;
    std::function<void(const ConnectorModel *connector, int, int64_t meterValue)> onMeterChange = nullptr;
};

#endif // CONNECTORMODEL_H
