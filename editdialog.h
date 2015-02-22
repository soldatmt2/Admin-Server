#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <question.h>
#include <QListWidgetItem>
#include <textdialog.h>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(Question *question, QWidget *parent = 0);
    ~EditDialog();

private:
    void initialize();

    Ui::EditDialog *ui;
    Question* quest;
    QMap<QListWidgetItem*, int>* answers;

public slots:
    void accept();
    void reject();
    void on_answer_changed(QString text);
    void on_list_item_dubleCliked(QListWidgetItem* item);
    void on_del_answer_clicked();
    void on_add_answer_clicked();
signals:
    void question_changed(QString text);
};

#endif // EDITDIALOG_H
