#ifndef OCCP16CONSTANT_H
#define OCCP16CONSTANT_H

#include <QString>
#include <QJsonValue>

#define NZStringInsert(obj, value) if(value.length() > 0) obj.insert(#value, value)

enum class OCPP16MessageType {
    CALL = 2,
    CALLRESULT = 3,
    CALLERROR = 4
};

#define ClassEnuStringLit(EnumType, StringLiteralNBraces) static inline const EnumType StringLiteralNBraces{#StringLiteralNBraces}
#define ClassEnuStringDef(EnumType, Name, Literal) static inline const EnumType Name{Literal}

#define DefClassEnuTemplate(TYPE) \
    TYPE(){} \
    TYPE(const char *value) : QString(value){ \
    } \
    TYPE(const QString &value) : QString(value){ \
    }


#endif // OCCP16CONSTANT_H
