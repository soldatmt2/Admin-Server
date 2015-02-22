#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    this->initialize();
}

Gui::~Gui()
{
    delete ui;
}

void Gui::initialize()
{
    ui->addQuestoin->setVisible(false);
    ui->delQuestion->setVisible(false);
    ui->finishQuestions->setVisible(false);
    ui->questionsList->setVisible(false);

    connect(ui->createQuestions, SIGNAL(clicked()), this, SLOT(showMainScreen()));
    connect(ui->addQuestoin, SIGNAL(clicked()), this, SLOT(on_add_question()));
    connect(ui->delQuestion, SIGNAL(clicked()), this, SLOT(on_del_question()));
    connect(ui->questionsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_click_to_list_item(QListWidgetItem*)));
    connect(ui->finishQuestions, SIGNAL(clicked()), this, SLOT(on_finish_clicked()));
    connect(ui->startSrever, SIGNAL(clicked()), this, SLOT(on_start_sever_clicked()));

    this->questions = new QMap<QListWidgetItem*, Question*>();

}

void Gui::showMainScreen()
{
    ui->addQuestoin->setVisible(true);
    ui->delQuestion->setVisible(true);
    ui->finishQuestions->setVisible(true);
    ui->questionsList->setVisible(true);

    ui->createQuestions->setVisible(false);
    ui->startSrever->setVisible(false);
}

void Gui::on_add_question()
{
    Question* quest = new Question();
    quest->setText("test");
    quest->addAnswer("test answer");
    quest->setRightAnswer(quest->addAnswer("test answer2"));

    QListWidgetItem* item = new QListWidgetItem(quest->getText());

    ui->questionsList->addItem(item);
    this->questions->insert(item, quest);
}

void Gui::on_del_question()
{
    QListWidgetItem* item = ui->questionsList->currentItem();
    this->questions->value(item)->deleteLater();
    this->questions->remove(item);
    delete item;
}

void Gui::on_click_to_list_item(QListWidgetItem *item)
{
    EditDialog* edit = new EditDialog(this->questions->value(item));
    edit->setModal(true);
    connect(edit, SIGNAL(question_changed(QString)), this, SLOT(on_question_changed(QString)));
    edit->show();
}

void Gui::on_question_changed(QString text)
{
    if(text.length() >= 70)
        ui->questionsList->currentItem()->setText(text.remove(70, text.length()-70)+"...");
    else
        ui->questionsList->currentItem()->setText(text);
}

void Gui::on_finish_clicked()
{
    XMLGenerator* gen = new XMLGenerator();
    QString text = gen->start(this->questions->values(), true);
    QFile file(QFileDialog::getSaveFileName(this, "", "", "*.xml"));
    if(!file.open(QFile::WriteOnly|QFile::Text))
        QMessageBox::critical(this, "Ошибка", "Невозножно сохранить файл");
    else
    {
        file.write(text.toStdString().c_str());
        file.close();
    }
}

void Gui::on_start_sever_clicked()
{
    ServerDialog* serverDialog = new ServerDialog(this);
    serverDialog->setModal(true);
    serverDialog->show();
}

