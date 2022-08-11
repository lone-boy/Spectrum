//
// Created by jcc on 22-8-10.
//

#ifndef SPECTRUM_THREAD_IIO_HPP
#define SPECTRUM_THREAD_IIO_HPP

#include "QThread"
#include "iio/iio_device_scan.hpp"
#include <QtWidgets/QTextEdit>
#include "boost/shared_ptr.hpp"
#include "QSharedPointer"
#include "fft/fftw3.h"
#include "QTimer"
#include "QMutex"

#define FFT_N 1024


class iio_thread:public QThread
{
    Q_OBJECT
public:
    iio_thread();
    ~iio_thread();
    void close_thread();

signals:
    void send_info(QString info);
    void send_info_console(QString info);
    void send_fft_data(const QVector<double> fft_data,int fft_n);

private slots:
    void recv_info_ip(QString info);
    void recv_discon_button();
    void time_send_fft();

protected:
    virtual void run();

private:
    volatile bool _is_stop;
    bool _is_run_rx,_is_button_on;
    bool _try_connect;
    std::string _ip;

    QTimer *_tim;

    QSharedPointer<iio> _iio_device;
    fftw_complex *_in;
    fftw_complex *_out;

    QVector<double> _send_data;
    QMutex *_fft_data_mutex;
};

#endif //SPECTRUM_THREAD_IIO_HPP
