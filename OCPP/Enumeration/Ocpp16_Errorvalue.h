#ifndef OCPP16_ERRORVALUE_H
#define OCPP16_ERRORVALUE_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_ErrorValue : public QString
{
public:
    ClassEnuStringLit(QString, ConnectorLockFailure);
    ClassEnuStringLit(QString, EVCommunicationError);
    ClassEnuStringLit(QString, GroundFailure);
    ClassEnuStringLit(QString, HighTemperature);
    ClassEnuStringLit(QString, InternalError);
    ClassEnuStringLit(QString, LocalListConflict);
    ClassEnuStringLit(QString, NoError);
    ClassEnuStringLit(QString, OtherError);
    ClassEnuStringLit(QString, OverCurrentFailure);
    ClassEnuStringLit(QString, OverVoltage);
    ClassEnuStringLit(QString, PowerMeterFailure);
    ClassEnuStringLit(QString, PowerSwitchFailure);
    ClassEnuStringLit(QString, ReaderFailure);
    ClassEnuStringLit(QString, ResetFailure);
    ClassEnuStringLit(QString, UnderVoltage);
    ClassEnuStringLit(QString, WeakSignal);

    DefClassEnuTemplate(OCPP16_ErrorValue)
};

#endif // OCPP16_ERRORVALUE_H
