#include "mainwindow.h"
#include "QDir"
#include "QDebug"
#include "QFile"
#include "QMessageBox"
#include "./ui_mainwindow.h"

QStringList NotesList;
QListWidgetItem* SelectedItem;
QTextStream in;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateNotes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString FolderPlus(QString fileName){
    return "./Notes/" + fileName + ".txt";
}

void MainWindow::UpdateNotes(){
    QDir dir("Notes");
    if(dir.exists()){
        NotesList.clear();
        ui->listWidget->clear();
        QStringList filters("*.txt");
        NotesList = dir.entryList(filters, QDir::Files);
        for(QString &s : NotesList){
            if(s.endsWith(".txt")){
                s.chop(4);
            }
        }
        ui->listWidget->addItems(NotesList);
    }
    else
        QDir().mkdir("Notes");
}

void MainWindow::on_ExitButton_clicked()
{
    QApplication::quit();
}


void MainWindow::on_NewNoteButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->NewNotePage);
}


void MainWindow::on_SavedNotesButton_clicked()
{
    UpdateNotes();
    ui->stackedWidget->setCurrentWidget(ui->SavedNotesPage);
}


void MainWindow::on_BackButton_clicked()
{
    QString CurrentPage = ui->stackedWidget->currentWidget()->objectName();
    if(CurrentPage == "MainPage"){
        qDebug() << "You are already on Main Page";
    }
    else if(CurrentPage == "NewNotePage"){
        ui->stackedWidget->setCurrentWidget(ui->MainPage);
    }
    else if(CurrentPage == "SavedNotesPage"){
        ui->stackedWidget->setCurrentWidget(ui->MainPage);
    }
    else if(CurrentPage == "EditNotePage"){
        ui->stackedWidget->setCurrentWidget(ui->MainPage);
    }
}

void MainWindow::on_RemoveButton_clicked()
{
    if(SelectedItem){
        QFile file(FolderPlus(SelectedItem->text()));
        file.remove();
        UpdateNotes();
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    SelectedItem = item;
}

QString currentFile;
void MainWindow::on_EditButton_clicked()
{
    qDebug() << "here";
    if(SelectedItem == nullptr){
        QMessageBox::warning(this, "Fail", "It looks like you haven't selected any file to edit.");
        return;
    }

    currentFile = FolderPlus(SelectedItem->text());
    ui->stackedWidget->setCurrentWidget(ui->EditNotePage);
    QFile file(FolderPlus(SelectedItem->text()));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    in.setDevice(&file);
    QString content = in.readAll();

    ui->textEdit_NoteName->setText(SelectedItem->text());
    ui->textEdit_Note->setText(content);

    file.close();
}

void MainWindow::on_save_pushButton_clicked()
{
    UpdateNotes();
    QString newName = ui->textEdit_NoteName->toPlainText();
    QFile::rename(currentFile, FolderPlus(newName));
    QString content = ui->textEdit_Note->toPlainText();
    QFile file(FolderPlus(newName));

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << content;
        file.close();
        QMessageBox::information(this, "File Edited", "Your file has been edited successfully");
        UpdateNotes();
        ui->stackedWidget->setCurrentWidget(ui->SavedNotesPage);
        currentFile.clear();
        SelectedItem = nullptr;
    }
}

void MainWindow::on_NN_save_pushButton_clicked()
{
    UpdateNotes();
    QString newFileName = ui->NN_textEdit_NoteName->toPlainText();
    QFile file(FolderPlus(newFileName));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << ui->NN_textEdit_Note->toPlainText();
        file.close();
        QMessageBox::information(this, "File Saved", "Your new file has been saved successfully");
        UpdateNotes();
        ui->stackedWidget->setCurrentWidget(ui->SavedNotesPage);
        ui->NN_textEdit_Note->setPlainText("");
        ui->NN_textEdit_NoteName->setPlainText("");
    }
}


void MainWindow::on_cancel_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SavedNotesPage);
    ui->textEdit_Note->setText("");
    ui->textEdit_NoteName->setText("");
}


void MainWindow::on_NN_cancel_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->MainPage);
    ui->NN_textEdit_Note->setText("");
    ui->NN_textEdit_NoteName->setText("");
    SelectedItem = nullptr;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->NewNotePage);
}
