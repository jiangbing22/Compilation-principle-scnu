#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QHash>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_save_button_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->regex_edit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_load_button_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->regex_edit->setText(in.readAll());
            file.close();
        }
    }
}
void MainWindow::on_to_nfa_button_clicked()
{
    QString regexString = ui->regex_edit->toPlainText();
    QMap<QString,QString>regexmap;
    if(!regexString.isEmpty()&&regexString[0]!='_')
    for(auto i = regexString.begin();i!=regexString.end();i++)
    {

    }
}

