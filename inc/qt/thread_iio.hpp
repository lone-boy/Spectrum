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
#include "sdrDevice.h"

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


class iqProcess :public QThread
{
Q_OBJECT
public:
    iqProcess();
    ~iqProcess();
    static iqProcess *pThis;
public:
private slots:
    void recv_info_ip(QString info);
    void recv_discon_button();
    void recv_frequency(QString frequency_s);
    void recv_config_span(QString bd_width);
    void recv_RWB(bool);

    void time_send_fft();
//    void recv_config_value(QString config);
//    void recv_config_bd(QString bd_width);
//
//    void recv_rx_gain_mode(QString rx_mode);
//    void recv_rx_gain_value(QString gain_value);
//
//    void recv_RWB(bool);

signals:
    void send_info(QString info);
    void send_fft_data(const QVector<double> fft_data, int sample_cnt, double frequency, double fs);
    void send_RWB(QString RWB);

private:
    std::shared_ptr<mp::sdrDevice> _device;
    static void get_rx_data(mp::sdr_transfer *transfer);

    bool _isrun;

    /* Spectrum
     * Frequency
     * span
     * rx gain
     * */
    double _frequency;
    double _rx_gain;
    double _fs;
    uint32_t _sample_cnt;

    int _div_cnt;
    int _span;
    double _rbw;

    fftw_complex *_in_iq;
    fftw_complex *_out_iq;
    QVector<double> _send_data;
    QVector<double> _fft_data;
    int _fft_n_coefficient;

    QVector<double> _frequency_scan;
    int _scan_cnt_need;
    volatile int _scan_cnt;
    QTimer *_tim;
    QMutex sync;

protected:
    void run() override;

private:

    void one_sample_fft(int16_t *data);
    void pow2db(void);

    void set_send_rwb();
    void  get_bdwidth_div(double scan_width);
};


#endif //SPECTRUM_THREAD_IIO_HPP
