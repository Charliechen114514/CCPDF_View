#ifndef CCPDF_ABOUT_H
#define CCPDF_ABOUT_H
#include <QString>

struct CCPDF_ABOUT {
    static constexpr short MAJOR_VERISON = __MAJOR_VERSION;
    static constexpr short MINOR_VERSION = __MINOR_VERISON;
    static QString         version_string() {
        return (QString::number(MAJOR_VERISON) + "." +
                QString::number(MINOR_VERSION));
    }
    static constexpr const char* BRIEF_INTRODUCTION =
        "这是一个由Charlie开发的简单的PDF浏览程序！"
        "\n点击HelpWindow窗口以浏览更多！";

    static QString aboutMain() {
        return "当前发行版本: " + version_string() + "\n" + BRIEF_INTRODUCTION;
    }

    static constexpr const char* ApplicationName = "CCPDF_Reader";

    static constexpr const char* aboutTitle = "关于这个PDF浏览器...";
};
#endif  // CCPDF_ABOUT_H
