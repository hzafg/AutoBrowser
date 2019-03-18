#ifndef WEBPAGE_H
#define WEBPAGE_H


#include <QWebEnginePage>
#include <QWebEngineRegisterProtocolHandlerRequest>

class TabWidget;
class WebPage : public QWebEnginePage
{
    Q_OBJECT
private:
    TabWidget *parentTab;
public:
    WebPage(QWebEngineProfile *profile, QObject *parent = nullptr);
    TabWidget* getParentTab();
    void setParentTab(TabWidget*);
private slots:
    void handleRegisterProtocolHandlerRequested(QWebEngineRegisterProtocolHandlerRequest request);
#if !defined(QT_NO_SSL) || QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    void handleSelectClientCertificate(QWebEngineClientCertificateSelection clientCertSelection);
#endif
};


#endif // WEBPAGE_H
