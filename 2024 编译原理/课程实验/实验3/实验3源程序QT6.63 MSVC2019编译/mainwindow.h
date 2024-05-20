#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"treewindow.h"
#include <QMainWindow>
#include "parser.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_file_button_clicked();

    void on_parse_button_clicked();

    void on_gettoken_button_clicked();

private:
    QString filePath;
    void printtoken(TokenType token,const char* tokenString);
    Ui::MainWindow *ui;
    treewindow tree;
};
#endif // MAINWINDOW_H
