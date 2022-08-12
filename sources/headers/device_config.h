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

QT_BEGIN_NAMESPACE
namespace Ui { class device_config; }
QT_END_NAMESPACE

class device_config : public QWidget {
Q_OBJECT
public:
    explicit device_config(QWidget *parent = nullptr);
    ~device_config() override;

signals:
    void send_message(QString message);
    void send_config(QString config);
    void send_discon_message();

public slots:
    void on_button_power_clicked();
    void on_button_disconnect_clicked();

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
};


#endif //SPECTRUM_DEVICE_CONFIG_H
