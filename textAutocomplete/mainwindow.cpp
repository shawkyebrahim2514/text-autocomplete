#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <trie.h>
#include <QMessageBox>
bool changed = false;
Trie* tree = new Trie();
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile styleFile(":/stylesheet.qss");
    styleFile.open(QFile::ReadOnly);
    QString style = styleFile.readAll();
    styleFile.close();
    qApp->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_searchButton_clicked()
{
    if(changed){
        buildTrie();
        changed = false;
    }
    autoComplete();
}


void MainWindow::on_actionopen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open the file","","Text (*.txt)");
    QFile file(filePath);
    if(file.open(QFile::ReadOnly | QFile::Text)){
        ui->showTextArea->setPlainText(file.readAll());
    }
    file.close();
}


void MainWindow::on_showTextArea_textChanged()
{
    changed = true;
}

void MainWindow::autoComplete()
{
    vector<string> allStrings;
    ui->allMatching->clear();
    printAutoComplete(tree, ui->textField->text().toLower().toStdString(), allStrings);
    for(auto& val : allStrings) ui->allMatching->addItem(QString::fromStdString(val));
}

void MainWindow::buildTrie()
{
    deleteTree(tree);
    tree = new Trie();
    QString area = ui->showTextArea->toPlainText();
    auto lines = area.split('\n');
    QString container;
    for(int i = 0; i < lines.size(); ++i){
        auto strings = lines[i].split(' ');
        for(int i = 0; i < strings.size(); ++i){
            string word = strings[i].toStdString();
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            insert(tree, word);
        }
    }
}
