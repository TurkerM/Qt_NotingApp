#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

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

    void UpdateNotes();

private slots:
    void on_ExitButton_clicked();

    void on_NewNoteButton_clicked();

    void on_SavedNotesButton_clicked();

    void on_BackButton_clicked();

    void on_RemoveButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_EditButton_clicked();

    void on_save_pushButton_clicked();

    void on_NN_save_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_NN_cancel_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
