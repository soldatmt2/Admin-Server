#include "textdialog.h"
#include "ui_textdialog.h"

TextDialog::TextDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextDialog)
{
    ui->setupUi(this);
    ui->answerText->setText(text);
}

TextDialog::~TextDialog()
{
    delete ui;
}

void TextDialog::accept()
{
    emit answer_changed(ui->answerText->toPlainText().replace(QRegExp("(  )+|(\n)+"), " "));
    reject();
}

void TextDialog::reject()
{
    delete ui;
    this->deleteLater();
}
