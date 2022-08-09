//
// Created by jcc on 22-8-6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_device_config.h" resolved

#include "device_config.h"
#include "forms/ui_device_config.h"
#include "qwidget.h"
#include "qdebug.h"
#include "QPalette"

#define HEAD "Antsdr:"
#define LOG(info) HEAD info

device_config::device_config(QWidget *parent) :
        QWidget(parent)
        , ui(new Ui::device_config)
        , _is_connect(false){
    ui->setupUi(this);

}

device_config::~device_config() {
    delete ui;
}

void device_config::on_button_power_clicked() {
    QString ip_addr = ui->ip_edit->text();
    _is_connect = !_is_connect;

    if(ip_addr.isEmpty())
    {
        qDebug() << "ip_addr is empty,use default ip:192.168.2.1";
    }
    else
    {
        qDebug() << "use ipaddr:" << ip_addr;
        std::cout << ip_addr.toStdString() << std::endl;
    }

    if(_is_connect){
        ui->status->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);"));
        ui->status->setText("ON");
    }
    else
    {
        ui->status->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 41, 41);"));
        ui->status->setText("OFF");
    }

}
