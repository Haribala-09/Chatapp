#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"client.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_conn_clicked();
    void receive_text();
    void on_end_clicked();

private:
    Ui::MainWindow *ui;
    client_soc *c_s;
};
#endif // MAINWINDOW_H
