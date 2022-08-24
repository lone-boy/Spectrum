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

#define FFT_BASE 128

class iio_thread:public QThread
{
    Q_OBJECT
public:
    iio_thread();
    ~iio_thread();
    void close_thread();

signals:
    void send_info(QString info);
    void send_fft_data(const QVector<double> fft_data, int fft_n, long long lo_hz, long long bw_hz);
    void send_RWB(QString RWB);

private slots:
    void recv_info_ip(QString info);
    void recv_discon_button();
    void time_send_fft();
    void recv_config_value(QString config);
    void recv_config_bd(QString bd_width);

    void recv_rx_gain_mode(QString rx_mode);
    void recv_rx_gain_value(QString gain_value);

    void recv_RWB(bool);

protected:
    virtual void run();

private:
    int FFT_N;
    int _fft_n_coefficient;
    volatile bool _is_stop;
    bool _is_run_rx,_is_button_on;
    bool _try_connect;
    std::string _ip;
    stream_cfg_s _rx_cfg;
    long long _rx_cfg_lo_hz;
    QTimer *_tim;
    QString _control_mode_available;
    uint32_t _samples_count;

    long long _lo_recv;
    QVector<long long> _lo_scan;
    QVector<int> _rx_gain_range;
    QVector<long long> _rx_sampling_fre_range;
    QVector<long long> _rx_bandwidth_range;
    double _rbw;
    int _div_cnt;

    QSharedPointer<iio> _iio_device;
    fftw_complex *_in;
    fftw_complex *_out;
    std::vector<fftw_complex> _data_in;
    float _scan_width;

    QVector<double> _send_data,_send_all_data;
    QMutex *_fft_data_mutex;

    void run_default_config();
    void run_config_device();
    void run_get_stream();

    void run_get_ad9361_setting();
    void set_send_rwb();

    void get_bdwidth_div(float scan_width);
};

#endif //SPECTRUM_THREAD_IIO_HPP
