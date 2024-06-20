#include "mainwindow.h"
#include "ui_mainwindow.h"
// º¯ÊýÊµÏÖ
void printFirstMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& firstMap) {
    std::ostringstream oss;
    for (const auto& pair : firstMap) {
        oss << "First(" << pair.first << ") = { ";
        for (const auto& item : pair.second) {
            oss << item << " ";
        }
        oss << "}\n";
    }
    textEdit->setPlainText(QString::fromStdString(oss.str()));
}

void printFollowMap(QTextEdit* textEdit, const std::unordered_map<std::string, std::unordered_set<std::string>>& followMap) {
    std::ostringstream oss;
    for (const auto& pair : followMap) {
        oss << "Follow(" << pair.first << ") = { ";
        for (const auto& item : pair.second) {
            oss << item << " ";
        }
        oss << "}\n";
    }
    textEdit->setPlainText(QString::fromStdString(oss.str()));
}
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

void MainWindow::on_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->graEdit->setText(in.readAll());
            file.close();
        }
    }
}


void MainWindow::on_saveButton_clicked()
{
    QString filePath2 = QFileDialog::getSaveFileName(this, "Save File", QString(), "Text Files (*.txt)");
    if (!filePath2.isEmpty()) {
        QFile file(filePath2);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->graEdit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_generateButton_clicked()
{
    std::string temp = filePath.toStdString();
    LALR lalr(temp);
    printFirstMap(ui->firstEdit,lalr.G.firstMap);
    printFollowMap(ui->followEdit,lalr.G.followMap);
    printAutomaton(lalr,lalr.head,ui->LR1);
    printAutomaton(lalr,lalr.LALRhead,ui->LALR1);
    printParsingTable(lalr,ui->LALR1table);

}

