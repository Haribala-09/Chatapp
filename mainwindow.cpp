#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QLabel>
#include<QVBoxLayout>
#include<QThread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    c_s=new client_soc(8081);
//    connect(c_s, &client_soc::textReceived, this, &MainWindow::on_receive_text);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete c_s;
}
void MainWindow::on_pushButton_clicked()
{

        QString s = ui->sender->toPlainText();
        std::string str=s.toStdString();
        std::cout<<str<<std::endl;
        send(c_s->soc_fd, str.c_str(), str.length()+1, 0);
        ui->sender->clear();

}
//void MainWindow::receive_text()
//{
//    int val = 0;
//    QWidget wid;
//    ui->scrollArea->setWidget(&wid);
//    QString accumulatedText;
//    while (true)
//    {
//        val = read(c_s->soc_fd, c_s->r_buff, 1024 - 1);
//        c_s->r_buff[val] = '\0';
//        accumulatedText+=QString::fromStdString(c_s->r_buff)+"\n";
//        ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());

//    }
//}
void MainWindow::receive_text()
{
    int  bytesRead = 0;
    char buffer[1024];
    while (true)
    {
        bytesRead = read(c_s->soc_fd, buffer, sizeof(buffer) - 1);

        if (bytesRead <= 0) {
            break;
        }

        buffer[bytesRead] = '\0';

        if (ui->textEdit) {
            ui->textEdit->setStyleSheet("color: white;");
            ui->textEdit->append(QString::fromStdString(buffer));
        }


        QThread::msleep(100);
    }
}

//        val = read(c_s->soc_fd, c_s->r_buff, 1024 - 1);
//        c_s->r_buff[val] = '\0';
//        ->setText(QString(c_s->r_buff));
//        x->setStyleSheet("color : red;");
//        ui->verticalLayout->addWidget(x);
//        x->show();
       // ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
//        QTextEdit *messageBox = new QTextEdit();
//        messageBox->setPlainText(QString::fromStdString(std::string(c_s->r_buff)));
//        messageBox->setReadOnly(true);

//        QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
//        if (layout)
//        {
//            layout->addWidget(messageBox);
//        }
void MainWindow::on_conn_clicked()
{
    c_s->connect_();
    c_s->t2=std::thread(&MainWindow::receive_text,this);
//    std::string str=std::string(c_s->r_buff);
//    QString qstr=QString::fromStdString(str);
//    QLabel *lab= new QLabel;
//    lab->setText(qstr);
//    QWidget * w = new QWidget(lab);
//    ui->scrollArea->setWidget(w);
}


void MainWindow::on_end_clicked()
{
    exit(-1);
    if(c_s->t2.joinable())
    {
        c_s->t2.join();
    }
    c_s->close_();
}
