//
// Created by jcc on 22-8-10.
//
#include "qt/thread_iio.hpp"
#include "QDebug"
#include "QMutex"
#include "cmath"

bool checkout = false;
bool frame = false;

iqProcess *iqProcess::pThis = nullptr;

iqProcess::iqProcess() {
    pThis = this;
    _isrun = false;
    _frequency = 100e6;
    _fs = 3e6;
    _span = 3;      /* 1M bandwidth */
    _rx_gain = 50.0;
    _fft_n_coefficient = 3;
    _sample_cnt = FFT_BASE * pow(2,_fft_n_coefficient);
    _send_data.clear();
    _frequency_scan.resize(1);
    _frequency_scan[0] = _frequency;
    _scan_cnt_need = 1;
    _scan_cnt = 0;
    _tim = new QTimer();
    _tim->setInterval(60);
    connect(_tim,SIGNAL(timeout()),this,SLOT(time_send_fft()));
    _tim->start();
}

iqProcess::~iqProcess(){
    if(_in_iq)
        fftw_free(_in_iq);
    if(_out_iq)
        fftw_free(_out_iq);
}

void iqProcess::recv_info_ip(QString info) {
    /* click power */
    if(not _isrun && not _device){
        if(info.isEmpty()){
            _device = mp::sdrDevice::make_sdrDevice("iio","ip:192.168.1.10");
        }
        else{
            _device = mp::sdrDevice::make_sdrDevice("iio",info.toStdString());
        }
        if(_device){
            _device ->sdr_open();
            _device->sdr_check(0);
            emit send_info("connect");
        }
        else{
            emit send_info("unconnect");
        }
        _isrun = true;
    }
}

void iqProcess::recv_discon_button() {
    if(_isrun){
        _isrun = false;
        if(_device){
            _device->sdr_close();
            _device = nullptr;
            emit send_info("unconnect");
        }
    }
}

void iqProcess::recv_frequency(QString frequency_s) {
    sync.lock();
    _frequency = frequency_s.toDouble();
    if(_span == 1){
        _fs = 3e6;
        _frequency_scan.resize(1);
        _frequency_scan[0] = _frequency;
        if(_isrun){
            this->_device->sdr_set_lo_frequency(_frequency);
            checkout = true;
            _send_data.clear();
        }
    }
    else{
        if(_span < 5){
            _fs = static_cast<double>(this->_span) * 1e6;
            _frequency_scan.resize(1);
            _frequency_scan[0] = _frequency;
            if(_isrun){
                this->_device->sdr_set_lo_frequency(_frequency);
                checkout = true;
                _send_data.clear();
            }
        }
        else{
            double span_M = static_cast<double>(_span)*1e6;
            double frequency_lo_start = _frequency - (span_M / 2.0) + (span_M / pow(2,_div_cnt) / 2.0);
            for(int i=0;i<static_cast<int>(pow(2,_div_cnt));i++){
                _frequency_scan.push_back(frequency_lo_start + (span_M / pow(2,_div_cnt)) * i);
            }
            if(_isrun){
                this->_device->sdr_set_lo_frequency(frequency_lo_start);
                checkout = true;
                _send_data.clear();
            }
        }
    }
    sync.unlock();
}

void iqProcess::recv_config_span(QString bd_width) {
    sync.lock();
    _span = bd_width.toInt();
    _frequency_scan.clear();
    if(_span == 1){
        _fs = 1e6;
        _rbw = _fs / static_cast<double>(this->_sample_cnt);
        _frequency_scan.resize(1);
        _frequency_scan[0] = _frequency;
        this->_scan_cnt_need = 1;
        if(_isrun){
            this->_device->sdr_set_samplerate(_fs,0);
            this->_device->sdr_set_bandwidth(_fs,0);
            this->_device->sdr_set_lo_frequency(_frequency_scan[0]);
        }

    }
    else{
        if(_span <= 5){
            _fs = static_cast<double>(this->_span) * 1e6;
            _rbw = _fs / static_cast<double>(this->_sample_cnt);
            _frequency_scan.resize(1);
            _frequency_scan[0] = _frequency;
            this->_scan_cnt_need = 1;
            if(_isrun){
                fftw_free(_in_iq);
                fftw_free(_out_iq);
                _in_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
                _out_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
                this->_device->sdr_set_bandwidth(_fs,0);
                this->_device->sdr_set_samplerate(_fs,0);
                this->_device->sdr_set_lo_frequency(_frequency);
                checkout = true;
                _scan_cnt = 0;
                _send_data.clear();
            }
        }
        else{
            double span_M = static_cast<double>(_span)*1e6;
            double div_width;
            _div_cnt = 0;
            get_bdwidth_div(_span);
            div_width = span_M / pow(2,_div_cnt);
            this->_scan_cnt_need = pow(2,_div_cnt);
            double frequency_lo_start = _frequency - (span_M / 2.0) + (div_width / 2.0);
            for(int i=0;i<static_cast<int>(pow(2,_div_cnt));i++){
                _frequency_scan.push_back(frequency_lo_start + (div_width) * i);
            }
            _fs = div_width;
            _fft_n_coefficient = 4;
            _sample_cnt = FFT_BASE*pow(2,_fft_n_coefficient);
            _rbw = _fs / static_cast<double>(this->_sample_cnt);

            if(_isrun){
                fftw_free(_in_iq);
                fftw_free(_out_iq);
                _in_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
                _out_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
                this->_device->sdr_set_reset_rx_samplecount(_sample_cnt);
                this->_device->sdr_set_lo_frequency(frequency_lo_start);
                this->_device->sdr_set_samplerate(_fs,0);
                this->_device->sdr_set_bandwidth(_fs,0);
                checkout = true;
                _scan_cnt = 0;
                _send_data.clear();
            }
        }
    }
    set_send_rwb();
    sync.unlock();
}

/* important */
void iqProcess::get_rx_data(mp::sdr_transfer *transfer) {
    /* iq data get */
    pThis->sync.lock();
    if(transfer->length == pThis->_sample_cnt and not checkout && frame){
        pThis->_scan_cnt++;
        pThis->one_sample_fft(transfer->data);
        pThis->pow2db();
        if(pThis->_scan_cnt_need == pThis->_scan_cnt){
            pThis->emit send_fft_data(pThis->_send_data,pThis->_send_data.size(),pThis->_frequency,static_cast<double>(pThis->_span)*1e6);
            pThis->_scan_cnt = 0;
            if(pThis->_scan_cnt_need > 1){
                pThis->_device->sdr_set_lo_frequency(pThis->_frequency_scan[pThis->_scan_cnt]);
            }
            pThis->_send_data.clear();
            frame = false;
        }
        else if(pThis->_scan_cnt_need != 1){
            /* set frequency */
            pThis->_device->sdr_set_lo_frequency(pThis->_frequency_scan[pThis->_scan_cnt]);
            checkout = true;
        }
    }
    else{
        checkout = false;
    }
    pThis->sync.unlock();


}

void iqProcess::recv_RWB(bool is_add) {
    /*  */
    if(is_add){
        if(_fft_n_coefficient != 8)
            _fft_n_coefficient++;
    }else{
        if(_fft_n_coefficient != 0)
            _fft_n_coefficient--;
    }
    _sample_cnt = FFT_BASE*pow(2,_fft_n_coefficient);
    _rbw = MHZ(_span) / _sample_cnt;
    if(_isrun){
        fftw_free(_in_iq);
        fftw_free(_out_iq);
        _in_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
        _out_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
        this->_device->sdr_set_reset_rx_samplecount(_sample_cnt);
    }

    this->set_send_rwb();
}

void iqProcess::run() {
    _send_data.clear();
    _in_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
    _out_iq = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * _sample_cnt);
    _rbw = _fs / _sample_cnt;
    _device->sdr_set_rx_samplecnt(_sample_cnt);
    _device->sdr_set_bandwidth(_fs,0);
    _device->sdr_set_samplerate(_fs,0);
    _device->sdr_set_lo_frequency(_frequency_scan[0]);

    _device->sdr_start_rx(iqProcess::get_rx_data);

}

void iqProcess::one_sample_fft(int16_t *data) {
    fftw_plan p;
    /* get data */
    for(uint32_t i=0;i<_sample_cnt;i++){
        _in_iq[i][0] = (double)data[i*2];
        _in_iq[i][1] = (double)data[i*2+1];
    }
    p = fftw_plan_dft_1d(_sample_cnt,_in_iq,_out_iq,FFTW_FORWARD,FFTW_ESTIMATE);
    fftw_execute(p);
}

void iqProcess::pow2db(void) {
    _fft_data.resize(_sample_cnt);
    for(int i = _fft_data.size() / 2, j = 0;i<_fft_data.size();i++,j++){
        double M = sqrt(_out_iq[i][0] * _out_iq[i][0] + _out_iq[i][1] * _out_iq[i][1]);
        double A = 2 * M / _sample_cnt;
        _fft_data[j] = 20 * log10(A / 1e3);
    }
    for(int i = 0,j = _fft_data.size() / 2;i<_fft_data.size() / 2;i++,j++){
        double M = sqrt(_out_iq[i][0] * _out_iq[i][0] + _out_iq[i][1] * _out_iq[i][1]);
        double A = 2 * M / _sample_cnt;
        _fft_data[j] = 20 * log10(A / 1e3);
    }
    _send_data.append(_fft_data);
    _fft_data.clear();
}

void iqProcess::set_send_rwb() {
    QString rwb_string("RWB:");
    if(_rbw >= 1000){
        rwb_string.push_back(QString::number(_rbw / 1000,'f',2));
        rwb_string.push_back("KHz");
    }
    else{
        rwb_string.push_back(QString::number(_rbw,'f',2));
        rwb_string.push_back("Hz");
    }
    emit(send_RWB(rwb_string));
}

void iqProcess::get_bdwidth_div(double scan_width) {
    if(scan_width <= 5)
    {
        return ;
    }
    _div_cnt++;
    get_bdwidth_div(scan_width / 2.0f);
}

void iqProcess::time_send_fft() {
    sync.lock();
    frame = true;
    sync.unlock();
}

