//
// Created by jcc on 22-8-6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_device_config.h" resolved

#include "device_config.h"
#include "forms/ui_device_config.h"
#include "qwidget.h"
#include "qdebug.h"

#define HEAD "Antsdr:"
#define LOG(info) HEAD info

device_config::device_config(QWidget *parent) :
        QWidget(parent), ui(new Ui::device_config) {
    ui->setupUi(this);
    ui->textEdit->document()->setMaximumBlockCount(200);
    ui->textEdit->append(LOG("No device"));


    _tab0 = new QTabWidget();
    ui->verticalLayout->addWidget(_tab0);
    _tb = make_top_block("Specturm");
    _src = blocks::add_ff::make();
    _thr = blocks::throttle::make(sizeof(float),48000);

    _fsnk = qtgui::freq_sink_f::make(1024,fft::window::WIN_HANN,0,48000,"",1);

    _src0 = analog::sig_source_f::make(48000, analog::GR_SIN_WAVE, 1500, 1);
    _tb->connect(_src0,0,_src,0);
    _tb->connect(_src,0,_thr,0);
    _tb->connect(_thr,0,_fsnk,0);

    _qtgui_freq_sink_win = _fsnk->qwidget();

    _tab0->addTab(_qtgui_freq_sink_win,"Freq");
//    connect(ui->button_open, SIGNAL(clicked()),this,SLOT(on_button_open_clicked()));
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

void device_config::on_button_open_clicked() {
    /* show data */
    QString button_text = ui->button_open->text();
    if(!QString::compare(button_text,"open")){
        ui->button_open->setText("close");
        this->start();

    }
    else{
        ui->button_open->setText("open");
        this->quitting();
    }

}

void device_config::start() {
    _tb->start();
}

void device_config::quitting() {
    _tb->stop();
    _tb->wait();
}
