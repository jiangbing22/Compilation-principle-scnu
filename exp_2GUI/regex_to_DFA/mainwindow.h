#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTableWidget>
#include<QPushButton>
#include <QMainWindow>
#include<to_DFA.h>
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
    void on_save_button_clicked();

    void on_load_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
