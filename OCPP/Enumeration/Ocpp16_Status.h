#ifndef OCPP16_STATUS_H
#define OCPP16_STATUS_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_Status : public QString
{
public:

    ClassEnuStringLit(QString, Available);
    ClassEnuStringLit(QString, Preparing);
    ClassEnuStringLit(QString, Charging);
    ClassEnuStringLit(QString, SuspendedEV);
    ClassEnuStringLit(QString, SuspendedEVSE);
    ClassEnuStringLit(QString, Finishing);
    ClassEnuStringLit(QString, Reserved);
    ClassEnuStringLit(QString, Unavailable);
    ClassEnuStringLit(QString, Faulted);

    DefClassEnuTemplate(OCPP16_Status)
};

#endif // OCPP16_STATUS_H
