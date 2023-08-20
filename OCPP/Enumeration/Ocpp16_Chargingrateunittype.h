#ifndef OCPP16_CHARGINGRATEUNITYPE_H
#define OCPP16_CHARGINGRATEUNITYPE_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_ChargingRateUnitType : public QString
{
public:

    ClassEnuStringLit(QString, W);
    ClassEnuStringLit(QString, A);

    DefClassEnuTemplate(OCPP16_ChargingRateUnitType)
};

#endif // OCPP16_CHARGINGRATEUNITYPE_H
