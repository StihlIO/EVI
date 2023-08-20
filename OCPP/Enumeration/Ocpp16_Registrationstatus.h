#ifndef OCPP16_REGISTRATIONSTATUS_H
#define OCPP16_REGISTRATIONSTATUS_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_RegistrationStatus : public QString
{
public:

    ClassEnuStringLit(QString, Accepted);
    ClassEnuStringLit(QString, Pending);
    ClassEnuStringLit(QString, Rejected);

    DefClassEnuTemplate(OCPP16_RegistrationStatus)
};

#endif // OCPP16_REGISTRATIONSTATUS_H
