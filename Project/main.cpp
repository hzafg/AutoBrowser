#include <QApplication>
#include <QApplication>
#include <QWebEngineView>
#include <QCoreApplication>
#include <iostream>
#include <QWebEngineSettings>
#include <QSettings>
#include "browserwindow.h"
#include "browser.h"
#include "tabwidget.h"
#include "webview.h"
#include "scriptloader.h"

int main(int argc, char *argv[])
{
    ScriptLoader::initial();
    QCoreApplication::setOrganizationName("AutoBrowser");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QWebEngineProfile::defaultProfile()->setHttpUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36");

    QSettings settings(QString("app.ini"), QSettings::IniFormat);
    QString initUrl = settings.value("Browser/InitUrl", "https://www.baidu.com").toString();

    QUrl url = QUrl(initUrl);
    Browser browser;

    BrowserWindow *window = browser.createWindow();


    window->tabWidget()->setUrl(url);
    window->show();
    return app.exec();
}
