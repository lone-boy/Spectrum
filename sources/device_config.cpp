//
// Created by jcc on 22-8-6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_device_config.h" resolved

#include "device_config.h"
#include "forms/ui_device_config.h"
#include "qwidget.h"
#include "qdebug.h"
#include "qvalidator.h"


device_config::device_config(QWidget *parent) :
        QWidget(parent)
        , ui(new Ui::device_config)
        , _work_thread() {
    ui->setupUi(this);

    this->setup_plot();

    ui->console->document()->setMaximumBlockCount(100);
    ui->console->append("Antsdr:console");
    ui->console->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);

    QValidator *validator_m = new QIntValidator(70,6000,this);
    ui->le_lo_M->setValidator(validator_m);
    QValidator *validator_k = new QIntValidator(0,999,this);
    ui->le_lo_K->setValidator(validator_k);
    QValidator *validator_h = new QIntValidator(0,999,this);
    ui->le_lo_H->setValidator(validator_h);

    _work_thread.reset(new(iio_thread));
    QObject::connect(this, SIGNAL(send_message(QString)),
                     _work_thread.get(),SLOT(recv_info_ip(QString)));
    QObject::connect(_work_thread.get(), SIGNAL(send_info_console(QString)),
                     this,SLOT(recv_message_console(QString)));
    QObject::connect(_work_thread.get(),SIGNAL(send_info(QString)),
                     this,SLOT(recv_message(QString)));
    QObject::connect(this, SIGNAL(send_discon_message()),
                     _work_thread.get(), SLOT(recv_discon_button()));
    QObject::connect(_work_thread.get(), SIGNAL(send_fft_data(QVector<double>, int)),
                     this,SLOT(recv_fft_data(const QVector<double>, int)));

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
    ui->custom_plot->graph()->setPen(QPen(Qt::blue));
    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void device_config::recv_fft_data(const QVector<double>& fft_data, int fft_n) {
    QVector<double> x;
    x.resize(fft_n);
    for(int i = 0;i<fft_n;i++)
    {
        x[i] = 99.5+(double)i / 1024;
    }
    ui->custom_plot->graph(0)->setData(x,fft_data);
    ui->custom_plot->replot();
    ui->custom_plot->xAxis->rescale();
    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}



