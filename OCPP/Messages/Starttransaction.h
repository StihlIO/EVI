#ifndef STARTTRSANSACTION_H
#define STARTTRSANSACTION_H

#include "OCPP/Ocpp16Origin.h"
#include <optional>
#include <QDateTime>

class StartTransaction : public OCPP16Origin
{
    int connectorId;
    QString idTag;
    int meterStart;
    int reservationId;
    std::optional<QDateTime> timestamp;

public:
    StartTransaction(int connectorId, CLQString idTag, int meterStart);
    StartTransaction(int connectorId, CLQString idTag, int meterStart, int reservationId, const QDateTime &timestamp);

    QString Name() const;
    QJsonObject Json() const;
};

#endif // STARTTRSANSACTION_H
