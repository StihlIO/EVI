#ifndef OCPP16_CHARGINFPROFILEKINDTYPE_H
#define OCPP16_CHARGINFPROFILEKINDTYPE_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_ChargingProfileKindType : public QString
{
public:

    ClassEnuStringLit(QString, Absolute);
    ClassEnuStringLit(QString, Recurring);
    ClassEnuStringLit(QString, Relative);

    DefClassEnuTemplate(OCPP16_ChargingProfileKindType)
};

#endif // OCPP16_CHARGINFPROFILEKINDTYPE_H
