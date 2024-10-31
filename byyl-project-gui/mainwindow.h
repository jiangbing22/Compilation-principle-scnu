#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QFileDialog>
#include<QHash>
#include<QRegularExpressionMatch>
#include<QProcess>
#include<QDebug>
#include<QMessageBox>
#include <QMainWindow>
#include<QTextEdit>
#include <LALR.h>
#include<DFA.h>
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
    void on_pushButton_clicked();

    void on_saveButton_clicked();

    void on_generateButton_clicked();

    void on_openreButton_clicked();

    void on_savere_Button_clicked();

    void on_generate_reButton_clicked();

    void on_savecode_Button_clicked();

    void on_openlex_Button_clicked();

    void on_opencode_Button_clicked();

    void on_startana_Button_clicked();

    void on_savelex_Button_clicked();

private:
    Ui::MainWindow *ui;
    QString filePath;
    QString vectorToQString(const std::vector<int> &vec);
    QString sytanxCodePath;
    QString codePath;
};
void printFirstMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& firstMap);
void printFollowMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& followMap);


#endif // MAINWINDOW_H
