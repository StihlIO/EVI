#ifndef OCPP16_READINGCONTEXT_H
#define OCPP16_READINGCONTEXT_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_ReadingContext : public QString
{
public:

    ClassEnuStringDef(QString, Interruption_Begin, "Interruption.Begin");
    ClassEnuStringDef(QString, Interruption_End, "Interruption.End");
    ClassEnuStringDef(QString, Other, "Other");
    ClassEnuStringDef(QString, Sample_Clock, "Sample.Clock");
    ClassEnuStringDef(QString, Sample_Periodic, "Sample.Periodic");
    ClassEnuStringDef(QString, Transaction_Begin, "Transaction.Begin");
    ClassEnuStringDef(QString, Transaction_End, "Transaction.End");
    ClassEnuStringDef(QString, Trigger, "Trigger");

    DefClassEnuTemplate(OCPP16_ReadingContext)
};

#endif // OCPP16_READINGCONTEXT_H
