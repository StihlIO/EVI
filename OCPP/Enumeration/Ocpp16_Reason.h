#ifndef OCPP16_REASON_H
#define OCPP16_REASON_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_Reason : public QString
{
public:

    ClassEnuStringLit(QString, DeAuthorized);
    ClassEnuStringLit(QString, EmergencyStop);
    ClassEnuStringLit(QString, EVDisconnected);
    ClassEnuStringLit(QString, HardReset);
    ClassEnuStringLit(QString, Local);
    ClassEnuStringLit(QString, Other);
    ClassEnuStringLit(QString, PowerLoss);
    ClassEnuStringLit(QString, Reboot);
    ClassEnuStringLit(QString, Remote);
    ClassEnuStringLit(QString, SoftReset);
    ClassEnuStringLit(QString, UnlockCommand);

    DefClassEnuTemplate(OCPP16_Reason)
};

#endif // OCPP16_REASON_H
