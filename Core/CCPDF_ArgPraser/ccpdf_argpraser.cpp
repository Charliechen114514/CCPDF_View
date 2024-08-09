#include "ccpdf_argpraser.h"
#include <QApplication>
#include "CCPDF_About/CCPDF_About.h"
#include "MainWindow/ccpdfview_mainwindow.h"

static constexpr CCPDF_Positional_Arguments_Installee PDFLists_PosArgs = {
    "pdfLists", "the pdf required to load"};

static constexpr CCPDF_Arguments_Installee loader_positional_arguments = {
    "l", "load", "load the requiring pdf"};
namespace {

QCommandLineOption toCommandLineOption(
    const CCPDF_Arguments_Installee& installee) {
    auto options = QCommandLineOption{
        QStringList() << installee.short_op << installee.long_op,
        installee.discriptions};
    options.setValueName(installee.long_op);
    return options;
}

void addPositionals(QCommandLineParser& parser) {
    parser.addPositionalArgument(PDFLists_PosArgs.first,
                                 PDFLists_PosArgs.second);
}
void addOptions(QCommandLineParser& parser) {
    parser.addOption(toCommandLineOption(loader_positional_arguments));
}
}  // namespace

CCPDF_ArgPraser::CCPDF_ArgPraser(CCPDFView_MainWindow* window) {
    this->window = window;
    initializeAppInfo();
    loadArguments();
}

void CCPDF_ArgPraser::loadArguments() {
    parser.addHelpOption();
    parser.addVersionOption();
    addPositionals(parser);
    addOptions(parser);
}

void CCPDF_ArgPraser::initializeAppInfo() {
    QApplication::setApplicationName(CCPDF_ABOUT::ApplicationName);
    QApplication::setApplicationVersion(CCPDF_ABOUT::version_string());
}

void CCPDF_ArgPraser::loadRequiredPdfs() {
    const auto pdfs = parser.positionalArguments();
    for (const auto& each : pdfs) window->loadPDF(each);
}

void CCPDF_ArgPraser::makeProcess() {
    parser.process(*qApp);
    if (!window) return;
    if (parser.isSet(loader_positional_arguments.long_op)) {
        const QString load = parser.value(loader_positional_arguments.long_op);
        window->loadPDF(load);
    }

    loadRequiredPdfs();
}
