#ifndef WEBOPERATION_H
#define WEBOPERATION_H
#include <QObject>
#include <QMap>
#include <QString>

class WebPage;
class WebOperations : public QObject
{
    Q_OBJECT
private:
    WebPage* page;
public:
    WebOperations(WebPage *webPage);
public slots:
    void closeCurrentTab();
//    void saveContext(QObject);
    void saveContext(QString key, QString value);
    QString getContextValue(QString key);
//    QMap<QString, QString> getAllContextValue();
};

#endif // WEBOPERATION_H
