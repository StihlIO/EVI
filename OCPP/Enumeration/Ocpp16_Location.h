#ifndef OCPP16_LOCATION_H
#define OCPP16_LOCATION_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_Location : public QString
{
public:

    ClassEnuStringLit(QString, Body);
    ClassEnuStringLit(QString, Cable);
    ClassEnuStringLit(QString, EV);
    ClassEnuStringLit(QString, Inlet);
    ClassEnuStringLit(QString, Outlet);

    DefClassEnuTemplate(OCPP16_Location)
};

#endif // OCPP16_LOCATION_H
