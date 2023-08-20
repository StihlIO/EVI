#ifndef OCPP16_CHARGINGPROFILEPURPOSETYPE_H
#define OCPP16_CHARGINGPROFILEPURPOSETYPE_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_ChargingProfilePurposeType : public QString
{
public:

    ClassEnuStringLit(QString, ChargePointMaxProfile);
    ClassEnuStringLit(QString, TxDefaultProfile);
    ClassEnuStringLit(QString, TxProfile);

    DefClassEnuTemplate(OCPP16_ChargingProfilePurposeType)
};

#endif // OCPP16_CHARGINGPROFILEPURPOSETYPE_H
