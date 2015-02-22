#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <xmlreader.h>
#include <server.h>
#include <xmlgenerator.h>

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = 0);
    ~ServerDialog();

private:
    Ui::ServerDialog *ui;
public slots:
    void on_newUser(int id);
    void on_setName(int id, QString name);
    void on_setCompeted(int id, int completed);
};

#endif // SERVERDIALOG_H
