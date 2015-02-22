#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <xmlreader.h>
#include <server.h>
#include <xmlgenerator.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void on_newUser(int id);
    void on_setName(int id, QString name);
    void on_setCompeted(int id, int completed);
};

#endif // MAINWINDOW_H
