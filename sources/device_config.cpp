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
        , _work_thread(){
    _dial_action =  NO;
    ui->setupUi(this);
    _label = new QCPItemText(ui->custom_plot);
    _label->setLayer("overlay");
    _label->setPen(QPen(Qt::white));
    _label->setColor(Qt::white);
    _label->setVisible(false);

    _label1 = new QCPItemText(ui->custom_plot);
    _label1->setLayer("overlay");
    _label1->setPen(QPen(Qt::red));
    _label1->setColor(Qt::red);
    _label1->setVisible(false);

    _label2 = new QCPItemText(ui->custom_plot);
    _label2->setLayer("overlay");
    _label2->setPen(QColor(252, 175, 62));
    _label2->setColor(QColor(252, 175, 62));
    _label2->setVisible(false);

    _label3 = new QCPItemText(ui->custom_plot);
    _label3->setLayer("overlay");
    _label3->setPen(QColor(252, 233, 79));
    _label3->setColor(QColor(252, 233, 79));
    _label3->setVisible(false);

    _label4 = new QCPItemText(ui->custom_plot);
    _label4->setLayer("overlay");
    _label4->setPen(QColor(173, 127, 168));
    _label4->setColor(QColor(173, 127, 168));
    _label4->setVisible(false);

    this->setup_plot();
    ui->number_select_9->setCurValue(1);
    ui->number_select_bw->setRange(1,40);
    ui->number_select_bw->setCurValue(1);
    ui->number_select_gain->setRange(-3,71);
    ui->number_select_gain->setCurValue(70);
    _work_thread.reset(new(iio_thread));

    QObject::connect(this, SIGNAL(send_message(QString)),
                     _work_thread.get(),SLOT(recv_info_ip(QString)));
    QObject::connect(_work_thread.get(),SIGNAL(send_info(QString)),
                     this,SLOT(recv_message(QString)));
    QObject::connect(this, SIGNAL(send_discon_message()),
                     _work_thread.get(), SLOT(recv_discon_button()));
    QObject::connect(_work_thread.get(), SIGNAL(send_fft_data(QVector<double>, int,long long)),
                     this,SLOT(recv_fft_data(QVector<double>, int, long long)));
    QObject::connect(ui->number_select_10,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_9,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_8,SIGNAL(send_value_changed(void)),
                    this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_7,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_6,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_5,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_4,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_3,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_2,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_1,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_bw,SIGNAL(send_value_changed(void)),
                     this,SLOT(recv_seletnumber_change(void)));
    QObject::connect(ui->number_select_gain, SIGNAL(send_value_changed()),
                     this,SLOT(recv_selet_gain_change()));
    QObject::connect(this, SIGNAL(send_config_lo(QString)),
                     _work_thread.get(),SLOT(recv_config_value(QString)));
    QObject::connect(this,SIGNAL(send_config_band_width(QString)),
                     _work_thread.get(),SLOT(recv_config_bd(QString)));
    QObject::connect(this->ui->curson_switch, SIGNAL(dial_is_change(bool)),
                     this,SLOT(dial_change(bool)));
    QObject::connect(this, SIGNAL(send_rx_gain_mode(QString)),
                     _work_thread.get(), SLOT(recv_rx_gain_mode(QString)));
    QObject::connect(this, SIGNAL(send_rx_gain_value(QString)),
                     _work_thread.get(),SLOT(recv_rx_gain_value(QString)));

    _work_thread->start();

}

device_config::~device_config() {
    delete ui;
}



void device_config::on_button_power_clicked() {
    QString ip_addr = ui->ip_edit->text();
    _label->setVisible(true);
    emit send_message(ip_addr);

}

void device_config::on_button_disconnect_clicked() {
    ui->custom_plot->replot();
    emit send_discon_message();
}

void device_config::on_checkBox_1_clicked() {
    if(ui->checkBox_1->checkState() == Qt::Unchecked
       && ui->checkBox_2->checkState() == Qt::Unchecked
       && ui->checkBox_3->checkState() == Qt::Unchecked
       && ui->checkBox_4->checkState() == Qt::Unchecked)
    {
        _dial_action = NO;
    }
    else{
        if(ui->checkBox_1->checkState() == Qt::Checked){
            _dial_action = Box_1;
            _new_cursor = true;
            _label1->setVisible(true);
        }
        else
        {
            _dial_action = NO;
        }
    }
}

void device_config::on_checkBox_2_clicked() {
    if(ui->checkBox_1->checkState() == Qt::Unchecked
       && ui->checkBox_2->checkState() == Qt::Unchecked
       && ui->checkBox_3->checkState() == Qt::Unchecked
       && ui->checkBox_4->checkState() == Qt::Unchecked)
    {
        _dial_action = NO;
    }
    else{
        if(ui->checkBox_2->checkState() == Qt::Checked){
            _dial_action = Box_2;
            _new_cursor = true;
            _label2->setVisible(true);
        }
        else
        {
            _dial_action = NO;
        }
    }
}

void device_config::on_checkBox_3_clicked() {
    if(ui->checkBox_1->checkState() == Qt::Unchecked
       && ui->checkBox_2->checkState() == Qt::Unchecked
       && ui->checkBox_3->checkState() == Qt::Unchecked
       && ui->checkBox_4->checkState() == Qt::Unchecked)
    {
        _dial_action = NO;
    }
    else{
        if(ui->checkBox_3->checkState() == Qt::Checked){
            _dial_action = Box_3;
            _new_cursor = true;
            _label3->setVisible(true);
        }
        else
        {
            _dial_action = NO;
        }
    }
}

void device_config::on_checkBox_4_clicked() {
    if(ui->checkBox_1->checkState() == Qt::Unchecked
       && ui->checkBox_2->checkState() == Qt::Unchecked
       && ui->checkBox_3->checkState() == Qt::Unchecked
       && ui->checkBox_4->checkState() == Qt::Unchecked)
    {
        _dial_action = NO;
    }
    else{
        if(ui->checkBox_4->checkState() == Qt::Checked){
            _dial_action = Box_4;
            _new_cursor = true;
            _label4->setVisible(true);
        }
        else
        {
            _dial_action = NO;
        }
    }
}

void device_config::recv_message(const QString& message) {
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
}

void device_config::setup_plot() {
    ui->custom_plot->xAxis->setLabelColor(Qt::white);
    ui->custom_plot->yAxis->setLabelColor(Qt::white);
    ui->custom_plot->xAxis->setTickLabelColor(Qt::white);
    ui->custom_plot->yAxis->setTickLabelColor(Qt::white);
    QPen pen = ui->custom_plot->xAxis->basePen();
    pen.setColor(Qt::white);
    ui->custom_plot->xAxis->setTickPen(pen);
    ui->custom_plot->xAxis->setBasePen(pen);
    ui->custom_plot->xAxis->setSubTickPen(pen);
    ui->custom_plot->yAxis->setTickPen(pen);
    ui->custom_plot->yAxis->setBasePen(pen);
    ui->custom_plot->yAxis->setSubTickPen(pen);
    ui->custom_plot->setBackground(Qt::black);
    ui->custom_plot->xAxis->setVisible(true);
    ui->custom_plot->xAxis->setTickLabels(true);
    ui->custom_plot->yAxis->setVisible(true);
    ui->custom_plot->yAxis->setTickLabels(true);
    ui->custom_plot->xAxis->setLabel("Freqency (MHz)");
    ui->custom_plot->yAxis->setLabel("dBm (1000mv)");
    ui->custom_plot->yAxis->setRange(-30,70,Qt::AlignCenter);

    ui->custom_plot->addGraph();
    ui->custom_plot->graph()->setPen(QPen(Qt::green));
    ui->custom_plot->addGraph();
    ui->custom_plot->graph(1)->setPen(QPen(Qt::red));
    ui->custom_plot->addGraph();
    QPen draw_pen;
    draw_pen.setColor(Qt::green);
    draw_pen.setWidth(4);
    ui->custom_plot->graph(2)->setPen(draw_pen);
    ui->custom_plot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->custom_plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,2));
    /*3 4 5 6cursor*/
    ui->custom_plot->addGraph();
    draw_pen.setColor(QColor(239, 41, 41));
    draw_pen.setWidth(4);
    ui->custom_plot->graph(3)->setPen(draw_pen);
    ui->custom_plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->custom_plot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,2));

    ui->custom_plot->addGraph();
    draw_pen.setColor(QColor(252, 175, 62));
    draw_pen.setWidth(4);
    ui->custom_plot->graph(4)->setPen(draw_pen);
    ui->custom_plot->graph(4)->setLineStyle(QCPGraph::lsNone);
    ui->custom_plot->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,2));

    ui->custom_plot->addGraph();
    draw_pen.setColor(QColor(252, 233, 79));
    draw_pen.setWidth(4);
    ui->custom_plot->graph(5)->setPen(draw_pen);
    ui->custom_plot->graph(5)->setLineStyle(QCPGraph::lsNone);
    ui->custom_plot->graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,2));

    ui->custom_plot->addGraph();
    draw_pen.setColor(QColor(173, 127, 168));
    draw_pen.setWidth(4);
    ui->custom_plot->graph(6)->setPen(draw_pen);
    ui->custom_plot->graph(6)->setLineStyle(QCPGraph::lsNone);
    ui->custom_plot->graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDot,2));

    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void device_config::recv_fft_data(QVector<double> fft_data, int fft_n, long long lo_hz) {
    double center_M = (double )lo_hz / 1e6;
    int bd_width = ui->number_select_bw->readValue();
    QVector<double> x;
    x.resize(fft_n);
    for(int i = 0;i<x.size();i++)
    {
        x[i] = (center_M - (double)bd_width / 2)+(double)i*bd_width / fft_n;

    }
    auto max_value = std::max_element(std::begin(fft_data),std::end(fft_data));
    auto position_max = std::distance(std::begin(fft_data),max_value);
    QVector<double>x_plot,y_plot;
    x_plot << x[(int)position_max];
    y_plot << fft_data[(int)position_max];

    QVector<double> max_x(fft_n,*max_value);

    ui->custom_plot->graph(0)->setData(x,fft_data);
    ui->custom_plot->graph(1)->setData(x,max_x);
    ui->custom_plot->graph(2)->setData(x_plot,y_plot);
    _label->position->setCoords(x_plot[0],y_plot[0] + 5);
    _label->setText(QString("%1MHz , %2dBm").arg(x_plot[0]).arg(y_plot[0]));

    if(_new_cursor){
        switch(_dial_action){
            case NO:
                break;
            case Box_1:
                _index_1 = (int)position_max;
                break;
            case Box_2:
                _index_2 = (int)position_max;
                break;
            case Box_3:
                _index_3 = (int)position_max;
                break;
            case Box_4:
                _index_4 = (int)position_max;
                break;
        }
        _new_cursor = false;
    }

    if(ui->checkBox_1->checkState() == Qt::Checked){
        QVector<double>x1_plot,y1_plot;
        x1_plot << x[(int)_index_1];
        y1_plot << fft_data[(int)_index_1];
        _label1->position->setCoords(x1_plot[0],y1_plot[0]+5);
        ui->custom_plot->graph(3)->setData(x1_plot,y1_plot);
        _label1->setText(QString("%1MHz , %2dBm").arg(x1_plot[0]).arg(y1_plot[0]));
    } else{
        ui->custom_plot->graph(3)->data().data()->clear();
        _label1->setVisible(false);
    }
    if(ui->checkBox_2->checkState() == Qt::Checked){
        QVector<double>x2_plot,y2_plot;
        x2_plot << x[(int)_index_2];
        y2_plot << fft_data[(int)_index_2];
        _label2->position->setCoords(x2_plot[0],y2_plot[0]+5);
        ui->custom_plot->graph(4)->setData(x2_plot,y2_plot);
        _label2->setText(QString("%1MHz , %2dBm").arg(x2_plot[0]).arg(y2_plot[0]));
    } else{
        ui->custom_plot->graph(4)->data().data()->clear();
        _label2->setVisible(false);
    }
    if(ui->checkBox_3->checkState() == Qt::Checked){
        QVector<double>x3_plot,y3_plot;
        x3_plot << x[(int)_index_3];
        y3_plot << fft_data[(int)_index_3];
        _label3->position->setCoords(x3_plot[0],y3_plot[0]+5);
        ui->custom_plot->graph(5)->setData(x3_plot,y3_plot);
        _label3->setText(QString("%1MHz , %2dBm").arg(x3_plot[0]).arg(y3_plot[0]));
    } else{
        ui->custom_plot->graph(5)->data().data()->clear();
        _label3->setVisible(false);
    }
    if(ui->checkBox_4->checkState() == Qt::Checked) {
        QVector<double>x4_plot,y4_plot;
        x4_plot << x[(int)_index_4];
        y4_plot << fft_data[(int)_index_4];
        _label4->position->setCoords(x4_plot[0],y4_plot[0]+5);
        ui->custom_plot->graph(6)->setData(x4_plot,y4_plot);
        _label4->setText(QString("%1MHz , %2dBm").arg(x4_plot[0]).arg(y4_plot[0]));
    } else{
        ui->custom_plot->graph(6)->data().data()->clear();
        _label4->setVisible(false);
    }

    ui->custom_plot->replot();
    ui->custom_plot->xAxis->rescale();
    ui->custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void device_config::recv_seletnumber_change(void) {
    QString device_config_para;
    device_config_para.append(ui->number_select_10->getValueStr());
    device_config_para.append(ui->number_select_9->getValueStr());
    device_config_para.append(ui->number_select_8->getValueStr());
    device_config_para.append(ui->number_select_7->getValueStr());
    device_config_para.append(ui->number_select_6->getValueStr());
    device_config_para.append(ui->number_select_5->getValueStr());
    device_config_para.append(ui->number_select_4->getValueStr());
    device_config_para.append(ui->number_select_3->getValueStr());
    device_config_para.append(ui->number_select_2->getValueStr());
    device_config_para.append(ui->number_select_1->getValueStr());

    if(device_config_para.toLongLong() < 70e6 or device_config_para.toLongLong() > 6e9){
        ui->number_select_10->setCurValue(0);
        ui->number_select_9->setCurValue(0);
        ui->number_select_8->setCurValue(7);
        ui->number_select_7->setCurValue(0);
        ui->number_select_6->setCurValue(0);
        ui->number_select_5->setCurValue(0);
        ui->number_select_4->setCurValue(0);
        ui->number_select_3->setCurValue(0);
        ui->number_select_2->setCurValue(0);
        ui->number_select_1->setCurValue(0);
        emit send_config_lo(QString("70000000"));
        ui->lineEdit_Fq->setText("70 000 000");
    }
    else{
        ui->lineEdit_Fq->setText(device_config_para);
        emit send_config_lo(device_config_para);
    }
    emit send_config_band_width(ui->number_select_bw->getValueStr());
}

void device_config::dial_change(bool is_add) {
    if(is_add){
        switch (_dial_action) {
            case NO:
                break;
            case Box_1:
                _index_1++;
                break;
            case Box_2:
                _index_2++;
                break;
            case Box_3:
                _index_3++;
                break;
            case Box_4:
                _index_4++;
                break;
        }
    }
    else{
        switch (_dial_action) {
            case NO:
                break;
            case Box_1:
                _index_1--;
                break;
            case Box_2:
                _index_2--;
                break;
            case Box_3:
                _index_3--;
                break;
            case Box_4:
                _index_4--;
                break;
        }
    }

}

void device_config::on_radioButton_RG_fast_clicked() {
    emit(send_rx_gain_mode("fast_attack"));
}

void device_config::on_radioButton_RG_hybrid_clicked() {
    emit(send_rx_gain_mode("hybrid"));
}

void device_config::on_radioButton_RG_manual_clicked() {
    emit(send_rx_gain_mode("manual"));
}

void device_config::on_radioButton_RG_slow_clicked() {
    emit(send_rx_gain_mode("slow_attack"));
}

void device_config::recv_selet_gain_change(void) {
    emit(send_rx_gain_value(ui->number_select_gain->getValueStr()));
}









