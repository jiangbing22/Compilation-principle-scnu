#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<to_DFA.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "regex_to_DFA_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    RE regex;
    DFA_graph DFA;
    NFA_graph NFA;
    MainWindow w;
    w.show();
    return a.exec();
}
