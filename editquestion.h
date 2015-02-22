#ifndef EDITQUESTION_H
#define EDITQUESTION_H

#include <QDialog>
#include <QListWidgetItem>
#include <QAbstractButton>
#include <question.h>

//namespace Ui_2 {
//class EditQuestion;
//}

class EditQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit EditQuestion (Question* question, QWidget *parent = 0);
    ~EditQuestion();
public slots:
    void on_ok_button_clicked(QAbstractButton*btn);
private:
//    Ui_2::EditQuestion *ui;
//    QMap<QListWidgetItem*, int>* answers;
//    Question* quest;

#endif // EDITQUESTION_H
