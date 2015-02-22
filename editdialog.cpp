#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(Question* question, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);


    connect(ui->answerList,
            SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,
            SLOT(on_list_item_dubleCliked(QListWidgetItem*)));
    connect(ui->addAnswer, SIGNAL(clicked()), this, SLOT(on_add_answer_clicked()));
    connect(ui->delAnswer, SIGNAL(clicked()), this, SLOT(on_del_answer_clicked()));

    this->answers = new QMap<QListWidgetItem*, int>();
    this->quest = question;

    this->initialize();
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::initialize()
{
    ui->questionText->setText(this->quest->getText());
    QList<int> answersIds = this->quest->getIds();
    int answersCount = answersIds.count();
    int rightId = 0;
    for(int i = 0; i < answersCount; i++)
    {
        int curentId = answersIds.at(i);
        if(curentId == this->quest->getRightAnswer())
            rightId = i;
        ui->rightAnswer->insertItem(i, QString::number(i+1), curentId);
        QListWidgetItem* item = new QListWidgetItem(this->quest->getAnswerText(curentId));
        ui->answerList->addItem(item);
        this->answers->insert(item, curentId);
        ui->questionText->setText(this->quest->getText());
    }
    ui->rightAnswer->setCurrentIndex(rightId);
}

void EditDialog::accept()
{
    this->quest->setRightAnswer((ui->rightAnswer->currentData()).toInt());
    this->quest->setText(ui->questionText->toPlainText().replace(QRegExp("(  )+|(\n)+"), " "));
    emit question_changed(this->quest->getText());
    reject();
}

void EditDialog::reject()
{
    delete ui;
    this->deleteLater();
}

void EditDialog::on_answer_changed(QString text)
{
    this->quest->setAnswerText(this->answers->value(ui->answerList->currentItem()), text);
    if(text.length() >= 40)
        text = text.remove(40, text.length()-40)+"...";
    ui->answerList->currentItem()->setText(text);

}

void EditDialog::on_list_item_dubleCliked(QListWidgetItem *item)
{
    TextDialog* dialog = new TextDialog(this->quest->getAnswerText(this->answers->value(item)));
    dialog->setModal(true);
    connect(dialog, SIGNAL(answer_changed(QString)), this, SLOT(on_answer_changed(QString)));
    dialog->show();
}

void EditDialog::on_del_answer_clicked()
{
    this->quest->deleteAnswer(this->answers->value(ui->answerList->currentItem()));
    delete ui->answerList->currentItem();
}

void EditDialog::on_add_answer_clicked()
{
    if(ui->answerList->count() >= 4)
        return;
    QListWidgetItem* item = new QListWidgetItem("test answer");
    ui->answerList->addItem(item);
    int id = this->quest->addAnswer(item->text());
    this->answers->insert(item, id);
    ui->rightAnswer->insertItem(ui->rightAnswer->count()+1, QString::number(ui->rightAnswer->count()+1), id);
}
