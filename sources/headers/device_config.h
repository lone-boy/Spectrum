//
// Created by jcc on 22-8-6.
//

#ifndef SPECTRUM_DEVICE_CONFIG_H
#define SPECTRUM_DEVICE_CONFIG_H

#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include "qtabwidget.h"
#include "qt/thread_iio.hpp"
#include "QSharedPointer"
#include "qt/qcustomplot.h"
#include "QTimer"

QT_BEGIN_NAMESPACE
namespace Ui { class device_config; }
QT_END_NAMESPACE

class draw_gui : public QThread{
Q_OBJECT
public:
    explicit draw_gui(QCustomPlot *draw);
    ~draw_gui();

    void run();

private:
    QCustomPlot *_draw;
//    void draw_fft_data();

public slots:
    void recv_draw_fft_cmd();

};

enum dial_action{
    NO = 0,
    Box_1,
    Box_2,
    Box_3,
    Box_4
};
class device_config : public QWidget {
Q_OBJECT
public:
    explicit device_config(QWidget *parent = nullptr);
    ~device_config() override;

signals:
    void send_message(QString message);
    void send_config_lo(QString config);
    void send_discon_message();
    void send_config_band_width(QString bd_width);
    void send_rx_gain_mode(QString rx_mode);
    void send_rx_gain_value(QString gain_value);
    void send_RWB_change(bool);
    void send_draw_fft();

public slots:
    void on_button_power_clicked();
    void on_button_disconnect_clicked();
    void on_checkBox_1_clicked();
    void on_checkBox_2_clicked();
    void on_checkBox_3_clicked();
    void on_checkBox_4_clicked();
    /* dial change */
    void dial_change(bool);
    void dial_RWB_change(bool);
    /* radio button event */
    void on_radioButton_RG_fast_clicked();
    void on_radioButton_RG_hybrid_clicked();
    void on_radioButton_RG_manual_clicked();
    void on_radioButton_RG_slow_clicked();
    /* line edit event */
    void on_lineEdit_Fq_editingFinished();
    void on_lineEdit_Sp_editingFinished();
    void on_button_screen_shot_clicked();
    void on_avarge_point_editingFinished();

private slots:
    void recv_message(const QString& message);
    void recv_RWB(QString);
    /* value change */
    void recv_seletnumber_change(void);
    void recv_selet_gain_change(void);

    /* draw */
    void recv_fft_data(QVector<double> fft_data, int sample_cnt, double frequency, double fs);


private:
    QSharedPointer<iqProcess> _work_thread;
    QSharedPointer<draw_gui> _draw_thread;
    Ui::device_config *ui;
    virtual void closeEvent(QCloseEvent *event) override;

    /* draw */
    void setup_plot();

    QCPItemText *_label,*_label1,*_label2,*_label3,*_label4;
    int _dial_action;
    bool _new_cursor;
    bool _is_reset_config;
    int _index_1,_index_2,_index_3,_index_4;

    int _avarge_cnt;

    void reset_edit_show(QString &text);
};



#endif //SPECTRUM_DEVICE_CONFIG_H
