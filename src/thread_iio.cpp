//
// Created by jcc on 22-8-10.
//
#include "qt/thread_iio.hpp"
#include "QDebug"
#include "QMutex"
#include "cmath"


iio_thread::iio_thread()
{
    _is_stop = false;
    _try_connect = false;
    _ip = std::string("192.168.2.1");
    _iio_device = iio::make_iio();
    _is_run_rx = false;
    _is_button_on = false;
    _fft_data_mutex = new(QMutex);
    _in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
    _out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
    _tmp = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
    _send_data.resize(FFT_N);
    _tim = new QTimer();
    _tim->setInterval(80);
    connect(_tim,SIGNAL(timeout()),this,SLOT(time_send_fft()));
    _tim->start();
}

void iio_thread::close_thread() {
    _is_stop = true;
}

void iio_thread::run() {
    _rx_cfg.lo_hz = MHZ(100);
    _rx_cfg.fs_hz = MHZ(2.5);
    _rx_cfg.bw_hz = MHZ(3);
    _rx_cfg.rfport = "B_BALANCED";
    while(!_is_stop){
        if(_try_connect)
        {
            run_default_config();
        }
        if(_is_run_rx){
            run_get_stream();
        }
        usleep(10);
    }
}

void iio_thread::run_default_config() {
    bool is_connect;
    is_connect = _iio_device->connect_device(_ip);
    if(is_connect){
        emit send_info_console("Connect succeed");
        emit send_info("connect");
        emit send_info_console("Running config device");
        if(_iio_device->set_ad9361_stream_dev(RX, _rx_cfg, 0)){
            emit send_info_console("Config device done");
            emit send_info_console("Enable iio channel");
            emit send_info_console("malloc iio buffer");
            if(_iio_device->malloc_iio_buffer())
                emit send_info_console("malloc iio buffer succed");
            else
                emit send_info_console("malloc iio buffer failed");
            _is_run_rx = true;
        }
        else{
            _is_run_rx = false;
            emit send_info_console("Config device failed");
        }
    }
    else{
        _is_run_rx = false;
        emit send_info_console("Connect failed");
        emit send_info("unconnect");
    }
    _try_connect = false;
}
void iio_thread::run_config_device() {
    emit send_info_console("Config device");
    if(_iio_device->set_ad9361_stream_dev(RX, _rx_cfg, 0)){
        emit send_info_console("Config device done");
        emit send_info_console("Enable iio channel");
        _is_run_rx = true;
    }
    else{
        _is_run_rx = false;
        emit send_info_console("Config device failed");
    }
}
void iio_thread::run_get_stream() {
    fftw_plan p;
    _fft_data_mutex->lock();
    _iio_device->get_iio_data(_in, FFT_N);

    p = fftw_plan_dft_1d(FFT_N,_in,_out,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(p);

    _send_data.resize(FFT_N);
    for(int i = _send_data.size() / 2,j = 0;i<_send_data.size();i++,j++)
    {
        double M = sqrt((_out[i][0])*(_out[i][0]) + (_out[i][1])*(_out[i][1]));
        double A = 2 * M / FFT_N;
        _send_data[j] = fabs(20*log10(A / 1e3));
    }
    for(int i = 0,j = _send_data.size() / 2;i<_send_data.size() / 2;i++,j++)
    {
        double M = sqrt((_out[i][0])*(_out[i][0]) + (_out[i][1])*(_out[i][1]));
        double A = 2 * M / FFT_N;
        _send_data[j] = fabs(20*log10(A / 1e3));
    }
    _fft_data_mutex->unlock();
    if(_is_button_on){
        _is_button_on = false;
    }
}

void iio_thread::recv_info_ip(QString info) {
    if(info.compare("stop") == 0){
        _is_stop  = true;
    }
    else
    {
        if(!_is_run_rx){
            if(info.isEmpty())
            {/*  */
                _ip = "ip:192.168.2.1";
                emit send_info_console("use default ip:192.168.2.1");
            }
            else{
                QString info_send("use ");
                info_send.append(info);
                emit send_info_console(info_send);
                _ip = info.toStdString();
            }
            if(!_is_run_rx)
                _try_connect = true;
        }
        else{
            emit send_info_console("Is running please disconnect first");
        }
    }


}

iio_thread::~iio_thread() {

}

void iio_thread::recv_discon_button() {
    if(_is_run_rx){
        _is_run_rx = false;
        _is_button_on = true;
        emit send_info_console("disconnect device");
        emit send_info("unconnect");
    }
    else{
        emit send_info_console("No device connect");
    }
}

void iio_thread::time_send_fft() {
    if(_is_run_rx){
        _fft_data_mutex->lock();
        emit send_fft_data(_send_data, FFT_N, _rx_cfg.lo_hz);
        _fft_data_mutex->unlock();
    }
}

void iio_thread::recv_config_value(QString config) {
    _rx_cfg.lo_hz = config.toLongLong();
    run_config_device();
}









