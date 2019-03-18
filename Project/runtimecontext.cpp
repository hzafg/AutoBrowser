#include "runtimecontext.h"
#include "logger.h"
#include <QDebug>
#include <QMap>
#include <QString>

QMap<QString, QString> RuntimeContext::contextMapping;

RuntimeContext::RuntimeContext()
{

}


void RuntimeContext::add(QString key, QString value)
{
    contextMapping[key] = value;
}

QString RuntimeContext::get(QString key)
{
    QMap<QString, QString>::iterator it;
    it = contextMapping.find(key);
    if (it != contextMapping.end())
    {
        return it.value();
    }
    return "";
}

const QMap<QString, QString> RuntimeContext::const_map()
{
    return contextMapping;
}
