//
// Created by jcc on 22-8-6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_device_config.h" resolved

#include "device_config.h"
#include "forms/ui_device_config.h"
#define HEAD "Antsdr:"
#define LOG(info) HEAD info

device_config::device_config(QWidget *parent) :
        QWidget(parent), ui(new Ui::device_config) {
    ui->setupUi(this);
    ui->textEdit->document()->setMaximumBlockCount(200);
    ui->textEdit->append(LOG("No device"));

//    QObject::connect(ui->button_connect,SIGNAL(clicked()),
//                     this,SLOT(on_button_connect_clicked()));
}

device_config::~device_config() {
    delete ui;
}

void device_config::on_button_connect_clicked() {
    QString ip_addr = ui->lineEdit_2->text();
    if(ip_addr.size() == 0)
    {
        ui->textEdit->append(LOG("Use fefault ip:192.168.2.1"));
        ui->textEdit->moveCursor(QTextCursor::End);
    }
    else
    {
        ui->textEdit->append(LOG("Connect device"));
        ui->textEdit->moveCursor(QTextCursor::End);
    }

}

void device_config::on_button_clear_clicked() {
    ui->textEdit->clear();
    ui->textEdit->moveCursor(QTextCursor::End);
}
