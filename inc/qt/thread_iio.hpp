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
