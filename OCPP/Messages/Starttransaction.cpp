#include "Starttransaction.h"

StartTransaction::StartTransaction(int connectorId, CLQString idTag, int meterStart)
{
    this->connectorId = connectorId;
    this->idTag = idTag;
    this->meterStart = meterStart;
    reservationId = 0;
}

StartTransaction::StartTransaction(int connectorId, CLQString idTag,
                                   int meterStart, int reservationId,
                                   const QDateTime &timestamp) : StartTransaction(connectorId, idTag, meterStart)
{
    this->timestamp = timestamp;
    this->reservationId = reservationId;
}

QString StartTransaction::Name() const
{
    return "StartTransaction";
}

QJsonObject StartTransaction::Json() const
{
    QJsonObject obj;
    obj.insert("timestamp", timestamp.value_or(QDateTime::currentDateTime()).toString(Qt::ISODateWithMs));
    obj.insert("connectorId", connectorId);
    obj.insert("idTag", idTag);
    obj.insert("meterStart", meterStart);
    obj.insert("reservationId", reservationId);
    return obj;
}
