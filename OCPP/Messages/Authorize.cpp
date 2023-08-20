#include "Authorize.h"

Authorize::Authorize(CLQString idTag)
{
    this->idTag = idTag;
}

QString Authorize::Name() const
{
    return "Authorize";
}

QJsonObject Authorize::Json() const
{
    QJsonObject obj;
    obj.insert("idTag", idTag);
    return obj;
}
