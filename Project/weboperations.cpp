#include <QMap>
#include <QString>
#include <string>
#include "webpage.h"
#include "weboperations.h"
#include "logger.h"
#include "tabwidget.h"
#include "runtimecontext.h"

WebOperations::WebOperations(WebPage *webPage)
{
    this->page = webPage;
}

void WebOperations::closeCurrentTab()
{
    Logger::info("close current tab");
    int currentTab = this->page->getParentTab()->currentIndex();
    this->page->getParentTab()->closeTab(currentTab);
}

void WebOperations::saveContext(QString key, QString value)
{
    Logger::info(string("save context:") + key.toUtf8().constData() + ":" + value.toUtf8().constData());
    RuntimeContext::add(key, value);
}

QString WebOperations::getContextValue(QString key)
{
    Logger::info(string("get context:") + key.toUtf8().constData());
    QString res = RuntimeContext::get(key);
    Logger::info(string() + "content is " + res.toUtf8().constData());
    return res;
}
