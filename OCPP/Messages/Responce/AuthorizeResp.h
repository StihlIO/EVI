#ifndef AUTHORIZERESP_H
#define AUTHORIZERESP_H

#include "OCPP/Messages/Idtaginfo.h"

#include <QJsonObject>

class AuthorizeResp
{
    IdTagInfo idTagInfo;
    int transactionId;

public:
    AuthorizeResp(const QJsonObject &obj);
    bool IsValid() const;
    IdTagInfo getIdTagInfo() const;
};

#endif // AUTHORIZERESP_H
