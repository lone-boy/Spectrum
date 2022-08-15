//
// Created by jcc on 22-8-6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_device_config.h" resolved

#include <QVector>
#include "device_config.h"
#include "forms/ui_device_config.h"
#include "qwidget.h"
#include "qdebug.h"
#include "qvalidator.h"
#include "fft/fftw3.h"


device_config::device_config(QWidget *parent) :
        QWidget(parent)
        , ui(new Ui::device_config)
        , _work_thread()
        {
    ui->setupUi(this);


    this->setup_plot();
    ui->number_select_M->setRange(0,6000);
    ui->number_select_M->setCurValue(100);
    ui->number_select_K->setRange(0,999);
    ui->number_select_K->setCurValue(0);
    ui->number_select_H->setRange(0,999);
    ui->number_select_H->setCurValue(0);

    ui->console->document()->setMaximumBlockCount(100);
    ui->console->append("Antsdr:console");
    ui->console->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);

    _work_thread.reset(new(iio_thread));
    QObject::connect(this, SIGNAL(send_message(QString)),
                     _work_thread.get(),SLOT(recv_info_ip(QString)));
    QObject::connect(_work_thread.get(), SIGNAL(send_info_console(QString)),
                     this,SLOT(recv_message_console(QString)));
    QObject::connect(_work_thread.get(),SIGNAL(send_info(QString)),
                     this,SLOT(recv_message(QString)));
    QObject::connect(this, SIGNAL(send_discon_message()),
                     _work_thread.get(), SLOT(recv_discon_button()));
    QObject::connect(_work_thread.get(), SIGNAL(send_fft_data(QVector<double>, int,long long)),
                     this,SLOT(recv_fft_data(QVector<double>, int, long long)));
    QObject::connect(ui->number_select_M,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_K,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_H,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(this, SIGNAL(send_config(QString)),
                     _work_thread.get(),SLOT(recv_config_value(QString)));


    _work_thread->start();

}

device_config::~device_config() {
    delete ui;
}



void device_config::on_button_power_clicked() {
    QString ip_addr = ui->ip_edit->text();
    emit send_message(ip_addr);

}

void device_config::on_button_disconnect_clicked() {
    ui->custom_plot->replot();
    emit send_discon_message();
}

void device_config::recv_message_console(QString message) {
    ui->console->append(message);
    ui->console->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
}

void device_config::recv_message(QString message) {
    if(not message.compare("connect"))
    {
        ui->status->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);"));
        ui->status->setText("ON");
    }
    else{
        ui->status->setStyleSheet(QString::fromUtf8("background-color: rgb(239, 41, 41);"));
        ui->status->setText("OFF");
    }
}

void device_config::closeEvent(QCloseEvent *event) {
    emit send_discon_message();
    this->close();
    event->accept();

    _work_thread->exit(0);
}

void device_config::setup_plot() {
    ui->custom_plot->xAxis->setVisible(true);
    ui->custom_plot->xAxis->setTickLabels(true);
    ui->custom_plot->yAxis->setVisible(true);
    ui->custom_plot->yAxis->setTickLabels(true);
    ui->custom_plot->xAxis->setLabel("Freqency");
    ui->custom_plot->yAxis->setLabel("dBm");

    ui->custom_plot->yAxis->setRange(-10,60,Qt::AlignCenter);


    ui->custom_plot->addGraph();
    QPen pen;
    pen.setColor(Qt::blue);
    ui->custom_plot->graph()->setPen(pen);
    ui->custom_plot->addGraph();
    ui->custom_plot->graph(1)->setPen(QPen(Qt::red));
    ui->custom_plot->addGraph();
    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void device_config::recv_fft_data(QVector<double> fft_data, int fft_n, long long lo_hz) {
    double center_M = (double )lo_hz / 1e6;
    QVector<double> x;
    x.resize(fft_n);
    for(int i = 0;i<x.size();i++)
    {
        x[i] = (center_M - (double)2 / 2)+(double)i*2 / fft_n;

    }
    ui->custom_plot->graph(0)->setData(x,fft_data);
    ui->custom_plot->replot();
    ui->custom_plot->xAxis->rescale();
    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void device_config::recv_seletnumber_change(void) {
    QString device_config_para;

    device_config_para.append(ui->number_select_M->getValueStr());
    device_config_para.append(ui->number_select_K->getValueStr());
    device_config_para.append(ui->number_select_H->getValueStr());
    emit send_config(device_config_para);
}






