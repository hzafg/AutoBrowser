#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QWebChannel>
#include <regex>
#include <iostream>
#include <sstream>
#include <QtGlobal>
#include <QTextCodec>
#include "logger.h"
#include "scriptloader.h"
#include "runtimecontext.h"
#include "webpage.h"
#include "tabwidget.h"
#include "weboperations.h"

const string PageLoaded = "PageLoaded";
const string TabClosed = "TableClosed";
const string UrlChanged = "UrlChanged";

vector<string> ScriptLoader::urls;
vector<string> ScriptLoader::actions;
vector<string> ScriptLoader::files;

QString ScriptLoader::scriptContent = "";

void ScriptLoader::initial()
{
//    string configFileName = string(QDir::currentPath().toUtf8().constData()) + "/" + "config.txt";

    string configFileName = "config.txt";
    QFile configFile(configFileName.c_str());
    if(!configFile.open(QIODevice::ReadOnly)) {
        Logger::error(string("Cannot open config file: ") + configFileName);
        throw 2;
    }

    QTextStream in(&configFile);

    while(!in.atEnd()) {
        QString line = in.readLine();
        cout << line.toUtf8().constData() << endl;
        QStringList fields = line.split("\t");
        cout << fields.size() << endl;
        string urlPattern = fields[0].toUtf8().constData();
        string actionType = fields[1].toUtf8().constData();
        string fileName = fields[2].toUtf8().constData();
        urls.push_back(urlPattern);
        actions.push_back(actionType);
        files.push_back(fileName);
    }

    configFile.close();

    QFile appScript("channel.js");
    if(!appScript.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::error("Cannot find channel.js");
        throw 2;
    }

    QTextStream scriptin(&appScript);
    scriptin.setCodec(QTextCodec::codecForName("UTF-8"));
    scriptContent = scriptin.readAll();
    appScript.close();
}

string replace(string text, const string& oldstr, const string& newstr)
{
    size_t start_pos = text.find(oldstr);
    if(start_pos == std::string::npos)
        return text;
    return text.replace(start_pos, oldstr.length(), newstr);
}

void ScriptLoader::runScript(WebPage* page, QString (*func)(string), string url)
{
    WebOperations *webobj = new WebOperations(page);
    QWebChannel *channel = new QWebChannel(webobj);
    channel->registerObject("webobj", webobj);
    page->setWebChannel(channel);
    QString scriptContent = func(url);
    if (scriptContent.isNull() || scriptContent.isEmpty())
    {
        return;
    }
    page->runJavaScript(func(url));
}

QString ScriptLoader::loadScript(const string& url, const string& action)
{
    string parsed_url;

    QString preScriptContent = scriptContent;
    QString content = "function __auto_browser_run(){\n";
    content = content + QString("\nvar __auto_browser_url=\"") + QString(parsed_url.c_str()) + QString("\";\n") +
            QString("var __auto_browser_action=\"") + QString(action.c_str()) + QString("\";\n") +
            "var __auto_browser_context = {};\n";

    const QMap<QString, QString> varMap = RuntimeContext::const_map();
    QMap<QString, QString>::const_iterator it = varMap.begin();
    while (it != varMap.end()) {
        content = content + "__auto_browser_context[\"" + it.key() + "\"] = \"" + it.value() + "\";\n";
        ++it;
    }
    for (unsigned i = 0; i < actions.size(); i++) {

        if (actions.at(i) != action)
        {
            continue;
        }
        regex re(urls.at(i));
        smatch m;

        if (!regex_match (url, m, re))
        {
            continue;
        }
        Logger::debug(string("action ") + actions.at(i) + ". action=" + action);
        Logger::debug(string("url pattern ") + urls.at(i) + ". url=" + parsed_url);
        Logger::debug(string("selected file ") + files.at(i) + ". index=" + to_string(i));
        QFile file(files.at(i).c_str());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw 2;
        }
        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("UTF-8"));
        QString str = in.readAll();
        file.close();
        content = content + str + "\n}\n";
        qDebug(content.toLocal8Bit());
        return preScriptContent + content;
    }

    return "";

}

QString ScriptLoader::loadFinishScript(string url)
{
    Logger::debug("load finish script");
    return loadScript(url, PageLoaded);
}
QString ScriptLoader::urlChangeScript(string url)
{
    Logger::debug("url change script");
    return loadScript(url, UrlChanged);
}
QString ScriptLoader::tabCloseScript(string url)
{
    Logger::debug("tab close script");
    return loadScript(url, TabClosed);
}
