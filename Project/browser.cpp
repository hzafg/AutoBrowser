#include "browser.h"
#include "browserwindow.h"

#include <QWebEngineProfile>

Browser::Browser()
{
}

BrowserWindow *Browser::createWindow(bool offTheRecord)
{
    auto profile = offTheRecord ? &m_otrProfile : QWebEngineProfile::defaultProfile();
    auto mainWindow = new BrowserWindow(this, profile);
    m_windows.append(mainWindow);
    QObject::connect(mainWindow, &QObject::destroyed, [this, mainWindow]() {
        m_windows.removeOne(mainWindow);
    });
    mainWindow->show();
    return mainWindow;
}

BrowserWindow *Browser::createDevToolsWindow()
{
    auto profile = QWebEngineProfile::defaultProfile();
    auto mainWindow = new BrowserWindow(this, profile);
    m_windows.append(mainWindow);
    QObject::connect(mainWindow, &QObject::destroyed, [this, mainWindow]() {
        m_windows.removeOne(mainWindow);
    });
    mainWindow->show();
    return mainWindow;
}
