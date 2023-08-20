#ifndef OCPP16_AUTHORIZATIONSTATUS_H
#define OCPP16_AUTHORIZATIONSTATUS_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_AuthorizationStatus : public QString
{
public:

    ClassEnuStringLit(QString, Accepted);
    ClassEnuStringLit(QString, Blocked);
    ClassEnuStringLit(QString, Expired);
    ClassEnuStringLit(QString, Invalid);
    ClassEnuStringLit(QString, ConcurrentTx);

    DefClassEnuTemplate(OCPP16_AuthorizationStatus)
};

#endif // OCPP16_AUTHORIZATIONSTATUS_H
