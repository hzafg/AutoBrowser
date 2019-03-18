#ifndef SCRIPTLOADER_H
#define SCRIPTLOADER_H
#include <string>
#include <vector>

class QString;
class WebPage;
using namespace std;



class ScriptLoader
{
private:
    static vector<string> urls;
    static vector<string> actions;
    static vector<string> files;
    static QString scriptContent;
    static QString loadScript(const string& url, const string& action);
    static void loadConfig();
public:
    static void initial();
    static QString loadFinishScript(string url);
    static QString urlChangeScript(string url);
    static QString tabCloseScript(string url);
    static void runScript(WebPage* page, QString (*func)(string), string url);
};

#endif // SCRIPTLOADER_H
