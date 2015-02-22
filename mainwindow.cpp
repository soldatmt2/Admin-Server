#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
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
        delete ui;
        this->deleteLater();
    }
    else
    {
        reader = new XMLReader(this);
        reader->start(&file);
    }
    QList<Question *> questList = reader->getResult();
    XMLGenerator *gen = new XMLGenerator();
    Server* serv = new Server(gen->start(questList, false));
    serv->startServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newUser(int id)
{
}

void MainWindow::on_setName(int id, QString name)
{

}

void MainWindow::on_setCompeted(int id, int completed)
{

}
