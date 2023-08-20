#ifndef OCPP16ORIGIN_H
#define OCPP16ORIGIN_H

#include <stdlib.h>
#include <QString>
#include <QJsonObject>

typedef const QString& CLQString;

class OCPP16Origin
{
public:
    virtual QString Name() const = 0;
    virtual QJsonObject Json() const = 0;
    virtual ~OCPP16Origin() {}
};

#endif // OCPP16ORIGIN_H
