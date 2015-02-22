#include "serverdialog.h"
#include "ui_serverdialog.h"

ServerDialog::ServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    int i = 0;
    QFile file;
    XMLReader* reader;
    while(i <= 1)
    {
        QString questionFilePath = QFileDialog::getOpenFileName(this, "Выбрать файл вопросов", "", "*.xml");
        file.setFileName(questionFilePath);
        if(!file.exists())
            QMessageBox::information(this, "Ошибка", "Выбранный файл не существует");
        else
        {
            if(!file.open(QFile::ReadOnly))
                QMessageBox::information(this, "Ошибка", "Не удалось открыть файл");
            else
            {
                break;
            }
        }
        i++;
    }
    if(!file.isOpen())
    {
        return;
    }
    else
    {
        reader = new XMLReader(this);
        reader->start(&file);
    }
    QList<Question *> questList = reader->getResult();
    Server* serv = new Server(questList, this);
    serv->startServer();
}

ServerDialog::~ServerDialog()
{
    delete ui;
}

void ServerDialog::on_newUser(int id)
{
}

void ServerDialog::on_setName(int id, QString name)
{

}

void ServerDialog::on_setCompeted(int id, int completed)
{

}
