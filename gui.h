#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <question.h>
#include <QListWidgetItem>
#include <editdialog.h>
#include <xmlgenerator.h>
#include <serverdialog.h>
#include <QFileDialog>


namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();
    QList<Question*> getQuestions();

private:
    void initialize();
    Ui::Gui *ui;
    QMap<QListWidgetItem*, Question*>* questions;

public slots:
    void showMainScreen();
    void on_add_question();
    void on_del_question();
    void on_click_to_list_item(QListWidgetItem* item);
    void on_question_changed(QString text);
    void on_finish_clicked();
    void on_start_sever_clicked();
};

#endif // GUI_H
