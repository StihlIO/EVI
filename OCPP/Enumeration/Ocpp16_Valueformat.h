#ifndef OCPP16_VALUEFORMAT_H
#define OCPP16_VALUEFORMAT_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_ValueFormat : public QString
{
public:

    ClassEnuStringLit(QString, Raw);
    ClassEnuStringLit(QString, SignedData);

    DefClassEnuTemplate(OCPP16_ValueFormat)
};

#endif // OCPP16_VALUEFORMAT_H
