#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QFileDialog>
#include<QHash>
#include<QRegularExpressionMatch>
#include<QDebug>
#include<QMessageBox>
#include <QMainWindow>
#include<QTextEdit>
#include <LALR.h>
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
    // º¯ÊýÉùÃ÷

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_saveButton_clicked();

    void on_generateButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filePath;
};
void printFirstMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& firstMap);
void printFollowMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& followMap);


#endif // MAINWINDOW_H
