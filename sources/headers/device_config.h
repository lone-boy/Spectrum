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

QT_BEGIN_NAMESPACE
namespace Ui { class device_config; }
QT_END_NAMESPACE


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

public slots:
    void on_button_power_clicked();
    void on_button_disconnect_clicked();
    void on_checkBox_1_clicked();
    void on_checkBox_5_clicked();
    void on_checkBox_3_clicked();
    void on_checkBox_4_clicked();
    /* dial change */
    void dial_change(bool);

private slots:
    void recv_message(QString message);
    void recv_message_console(QString message);

    /* value change */
    void recv_seletnumber_change(void);
    /* draw */
    void recv_fft_data(QVector<double> fft_data, int fft_n, long long lo_hz);


private:
    QSharedPointer<iio_thread> _work_thread;
    Ui::device_config *ui;
    virtual void closeEvent(QCloseEvent *event) override;

    /* draw */
    void setup_plot();

    QCPItemText *_label,*_label1,*_label2,*_label3,*_label4;
    int _dial_action;
    bool _new_cursor;
    int _index_1,_index_2,_index_3,_index_4;
};


#endif //SPECTRUM_DEVICE_CONFIG_H
