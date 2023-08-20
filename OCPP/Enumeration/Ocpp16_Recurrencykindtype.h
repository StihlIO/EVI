#ifndef OCPP16_RECURRENCYKINDTYPE_H
#define OCPP16_RECURRENCYKINDTYPE_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_RecurrencyKindType : public QString
{
public:

    ClassEnuStringLit(QString, Daily);
    ClassEnuStringLit(QString, Weekly);

    DefClassEnuTemplate(OCPP16_RecurrencyKindType)
};

#endif // OCPP16_RECURRENCYKINDTYPE_H
