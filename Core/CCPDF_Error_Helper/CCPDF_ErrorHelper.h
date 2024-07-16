#ifndef CCPDF_ERRORHELPER_H
#define CCPDF_ERRORHELPER_H
#include <QString>

struct CCPDF_Error_Helper
{
    struct ErrorMessagePackage{
        QString title;
        QString details;
        QString possible_help;
    };

    struct ErrorMessgageUtils
    {
        static const ErrorMessagePackage
        HistoryInvalid(QString path, QString possibleHelp = ""){
            return {
                "历史记录非法",
                "文件:> " + path + "不存在，请检查路径！",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        UnsupportedFormat(QString path, QString possibleHelp = "")
        {
            return {
                "文件格式错误 / 不支持",
                "文件: \n" + path + "\n不被支持查看，请检查格式",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        PageNavigationError(int err_page, QString errorString, QString possibleHelp = ""){
            return {
                "跳转到错误页码: " + QString::number(err_page),
                errorString,
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        PageOverflowError(QString possibleHelp = ""){
            return {
                "发生页码上溢",
                "这已经是跳到最后一页之后了！",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        PageUnderflowError(QString possibleHelp = ""){
            return {
                "发生页码下溢",
                "这已经是跳到第一页之前了！",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        No_TargetPDF(QString possibleHelp = ""){
            return {
                "没有目标操作的PDF",
                "没有目标操作的PDF，请选定一个PDF进行操作",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        Invalid_Page_Index_FMT(QString possibleHelp = ""){
            return {
                "page指定格式错误",
                "page指定格式错误",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        ZoomInMaxOutError(QString possibleHelp = ""){
            return {
                "放大超过最大倍数",
                "放大超过最大倍数了！",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        ZoomOutMinOutError(QString possibleHelp = ""){
            return {
                "放大超过最小倍数",
                "放大超过最小倍数了！",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        UnsupportedDirectCheck(QString possibleHelp = "，尝试使用OCR光学识别模块"){
            return {
                "不支持直接提取文字",
                "文档可能是图像扫描！不支持直接文字提取！",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        NoFileExsits(QString filePath, QString possibleHelp = ""){
            return {
                "文件不存在",
                "文件不存在！ " + (filePath.isEmpty() ? "请选择文件" : ("检查路径:" + filePath)) + "或者重新选择！",
                possibleHelp
            };
        }

        static const ErrorMessagePackage
        PluginFinishButOutPutFileUnread(QString atWhere, QString possibleHelp = "")
        {
            return {
                "出错了！",
                "插件运行结束，但是找不到目标输出文件读入！" + atWhere,
                possibleHelp
            };
        }
    };
};

#endif // CCPDF_ERRORHELPER_H
