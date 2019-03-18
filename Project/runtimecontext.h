#ifndef RUNTIMECONTEXT_H
#define RUNTIMECONTEXT_H
#include <QMap>
#include <QString>

class RuntimeContext
{
private:
    static QMap<QString, QString> contextMapping;

public:
    RuntimeContext();
    static void add(QString key, QString value);
    static QString get(QString key);
    static const QMap<QString, QString> const_map();
};

#endif // RUNTIMECONTEXT_H
