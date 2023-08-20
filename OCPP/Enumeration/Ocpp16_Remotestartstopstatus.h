#ifndef OCPP16_REMOTESTARTSTOPSTATUS_H
#define OCPP16_REMOTESTARTSTOPSTATUS_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_RemoteStartStopStatus : public QString
{
public:
    ClassEnuStringLit(QString, Accepted);
    ClassEnuStringLit(QString, Rejected);

    DefClassEnuTemplate(OCPP16_RemoteStartStopStatus)
};

#endif // OCPP16_REMOTESTARTSTOPSTATUS_H
