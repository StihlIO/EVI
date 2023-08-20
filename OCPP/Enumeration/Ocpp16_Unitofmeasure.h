#ifndef OCPP16_UNITOFMEASURE_H
#define OCPP16_UNITOFMEASURE_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_UnitOfMeasure : public QString
{
public:

    ClassEnuStringLit(QString, Wh);
    ClassEnuStringLit(QString, kWh);
    ClassEnuStringLit(QString, varh);
    ClassEnuStringLit(QString, kvarh);
    ClassEnuStringLit(QString, W);
    ClassEnuStringLit(QString, kW);
    ClassEnuStringLit(QString, VA);
    ClassEnuStringLit(QString, kVA);
    ClassEnuStringLit(QString, var);
    ClassEnuStringLit(QString, kvar);
    ClassEnuStringLit(QString, A);
    ClassEnuStringLit(QString, V);
    ClassEnuStringLit(QString, Celsius);
    ClassEnuStringLit(QString, Fahrenheit);
    ClassEnuStringLit(QString, K);
    ClassEnuStringLit(QString, Percent);

    DefClassEnuTemplate(OCPP16_UnitOfMeasure)
};

#endif // OCPP16_UNITOFMEASURE_H
