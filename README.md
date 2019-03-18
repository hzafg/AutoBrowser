# AutoBrowser
基于QT的开源自动化浏览器的工具，可用来刷学习强国。

## 文件结构
- Project：工程源代码
- Release
    - Windows：目前仅提供Windows的可执行程序，其他平台可自行编译
        - app.ini：可设置入口网址
        - config.txt：可设置每一个页面使用什么脚本
        - js/*js：具体的js脚本

## 如何刷学习强国
1. 下载Release/Windows目录
-. 用户可根据自己需要修改相应的config.txt和js脚本自行DIY
-. 执行AutoBrowser.exe

## 已知问题
-. 第一次登陆不成功可能需要手动登录
-. 目前仅支持刷文章和文章时常