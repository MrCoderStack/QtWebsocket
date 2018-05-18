#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrlQuery>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->location->setEnabled(true);


    connect(&m_webSocket, SIGNAL(connected()), this, SLOT(onOpened()));
    connect(&m_webSocket, SIGNAL(disconnected()), this, SLOT(onClosed()));
    connect(&m_webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{

    QUrl url(ui->location->text());
    QUrlQuery query;
    query.addQueryItem("uid", "fr");
    url.setQuery(query);
    m_webSocket.open(url);


}

void MainWindow::on_disconnectButton_clicked()
{
    m_webSocket.close();
}

void MainWindow::on_sendButton_clicked()
{
    m_webSocket.send(ui->message->text());
}

void MainWindow::on_clearButton_clicked()
{
    ui->log->clear();
}



void MainWindow::onOpened()
{
    ui->log->append(QString("connect success"));
    ui->disconnectButton->setEnabled(true);
    ui->sendButton->setEnabled(true);
    ui->connectButton->setEnabled(false);
    ui->message->setEnabled(true);
    ui->location->setEnabled(false);
    //m_webSocket.send("uid=1222");


}

void MainWindow::onClosed()
{
    ui->log->append(QString("connect closed"));
    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->location->setEnabled(true);
    ui->message->setEnabled(false);
}

void MainWindow::onMessage(const QString &msg)
{
    ui->log->append(QString("server notify: %1").arg(msg));
}









