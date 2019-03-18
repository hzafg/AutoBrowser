#include "browserwindow.h"
#include "tabwidget.h"
#include "webpage.h"
#include "webview.h"
#include <QAuthenticator>
#include <QMessageBox>
#include <QStyle>
#include <QWebEngineCertificateError>
#include "tabwidget.h"

WebPage::WebPage(QWebEngineProfile *profile, QObject *parent)
    : QWebEnginePage(profile, parent)
{
    connect(this, &QWebEnginePage::registerProtocolHandlerRequested, this, &WebPage::handleRegisterProtocolHandlerRequested);
#if !defined(QT_NO_SSL) || QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    connect(this, &QWebEnginePage::selectClientCertificate, this, &WebPage::handleSelectClientCertificate);
#endif
}

TabWidget* WebPage::getParentTab()
{
    return this->parentTab;
}

void WebPage::setParentTab(TabWidget *widget)
{
    this->parentTab = widget;
}

void WebPage::handleRegisterProtocolHandlerRequested(QWebEngineRegisterProtocolHandlerRequest request)
{
    auto answer = QMessageBox::question(
        view()->window(),
        tr("Permission Request"),
        tr("Allow %1 to open all %2 links?")
        .arg(request.origin().host())
        .arg(request.scheme()));
    if (answer == QMessageBox::Yes)
        request.accept();
    else
        request.reject();
}

#if !defined(QT_NO_SSL) || QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
void WebPage::handleSelectClientCertificate(QWebEngineClientCertificateSelection selection)
{
    // Just select one.
    selection.select(selection.certificates().at(0));
}
#endif
