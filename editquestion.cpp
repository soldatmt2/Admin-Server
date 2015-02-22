#include "editquestion.h"
#include "ui_editquestion.h"

EditQuestion::EditQuestion(Question* question, QWidget *parent) :
    QDialog(parent),
    ui(new Ui_2::EditQuestion)
{
//    this->quest = question;
//    ui->setupUi(this);
//    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(on_ok_button_clicked(QAbstractButton*)));
//    this->answers = new QMap<QListWidgetItem*, int>();
//    ui->questoinText->setText(question->getText());
//    QList<int> answersIds = question->getIds();
//    int answersCount = answersIds.count();
//    int rightId = 0;
//    for(int i = 0; i < answersCount; i++)
//    {
//        int curentId = answersIds.at(i);
//        if(curentId == question->getRightAnswer())
//            rightId = i;
//        ui->comboBox->insertItem(i, QString::number(i+1), curentId);
//        QListWidgetItem* item = new QListWidgetItem(question->getAnswerText(curentId));
//        ui->answersList->addItem(item);
//        this->answers->insert(item, curentId);
//        ui->questoinText->setText(question->getText());
//    }
//    ui->comboBox->setCurrentIndex(rightId);
}

EditQuestion::~EditQuestion()
{
    delete ui;
}

void EditQuestion::on_ok_button_clicked(QAbstractButton * btn)
{
//    if(btn->text()=="OK")
//    {
//        this->quest->setText(ui->questionText->toPlainText());
//        this->quest->setRightAnswer((int)ui->comboBox->currentData());

//    }
//    else
//    {
//        delete ui;
//        this->deleteLater();
//    }
}
