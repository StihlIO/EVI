#ifndef OCPP16_PHASE_H
#define OCPP16_PHASE_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_Phase : public QString
{
public:

    ClassEnuStringDef(QString, L1, "L1");
    ClassEnuStringDef(QString, L2, "L2");
    ClassEnuStringDef(QString, L3, "L3");
    ClassEnuStringDef(QString, N, "N");
    ClassEnuStringDef(QString, L1_N, "L1-N");
    ClassEnuStringDef(QString, L2_N, "L2-N");
    ClassEnuStringDef(QString, L3_N, "L3-N");
    ClassEnuStringDef(QString, L1_L2, "L1-L2");
    ClassEnuStringDef(QString, L2_L3, "L2-L3");
    ClassEnuStringDef(QString, L3_L1, "L3-L1");

    DefClassEnuTemplate(OCPP16_Phase)
};

#endif // OCPP16_PHASE_H
