#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>

namespace Ui {
class TextDialog;
}

class TextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextDialog(QString text, QWidget *parent = 0);
    ~TextDialog();

private:
    Ui::TextDialog *ui;
public slots:
    void accept();
    void reject();
signals:
    void answer_changed(QString);
};

#endif // TEXTDIALOG_H
