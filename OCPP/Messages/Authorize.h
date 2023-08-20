#ifndef AUTHORIZE_H
#define AUTHORIZE_H

#include "OCPP/Ocpp16Origin.h"

class Authorize : public OCPP16Origin
{
    QString idTag;

public:
    Authorize(CLQString idTag);

    QString Name() const;
    QJsonObject Json() const;
};

#endif // AUTHORIZE_H
