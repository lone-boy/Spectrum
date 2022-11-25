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
/**
 * This thread is that configure iio device and get IQ data\n
 * after IQ data fft change,then send point by qt signal/slot
 * */
iio_thread::iio_thread()
{
    _is_stop = false;
    _try_connect = false;
    _ip = std::string("192.168.2.1");
    _iio_device = iio::make_iio();
    _is_run_rx = false;
    _is_button_on = false;
    _fft_data_mutex = new(QMutex);
    _fft_n_coefficient = 3;
    FFT_N = FFT_BASE * pow(2,_fft_n_coefficient);
    _in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
    _out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
    _scan_width = 1; /* 1MHz */
    _send_data.resize(FFT_N);
    _div_cnt = 1;
    _lo_recv = MHZ(100);
    _tim = new QTimer();
    _tim->setInterval(60);
    connect(_tim,SIGNAL(timeout()),this,SLOT(time_send_fft()));
    _tim->start();
}

/**
 * This function close thread
 * */
void iio_thread::close_thread() {
    _is_stop = true;
}



/**
 * this function is configure iio_device
 * */
void iio_thread::run_default_config() {
    bool is_connect;
    is_connect = _iio_device->connect_device(_ip);
    if(is_connect){
        emit send_info("connect");
        if(_iio_device->set_ad9361_stream_dev(RX, _rx_cfg, 0)){
            if(_iio_device->malloc_iio_buffer(_samples_count))
                qDebug() << "malloc iio buffer succeed";
            else
                qDebug() << "malloc iio buffer failed";
            _is_run_rx = true;
        }
        else{
            _is_run_rx = false;
            qDebug() << "Config device failed";
        }
    }
    else{
        _is_run_rx = false;
        qDebug() << ("Connect failed");
        qDebug() << ("unconnect");
    }
    _try_connect = false;
}

void iio_thread::run_config_device() {
    if(_iio_device->set_ad9361_stream_dev(RX, _rx_cfg, 0)){
        _is_run_rx = true;
    }
    else{
        _is_run_rx = false;
    }
}


void iio_thread::run_get_ad9361_setting() {
    char tmp[50];
    QString get_str_tmp;
    QStringList get_str_list_tmp;

    _iio_device->get_control_mode_available(RX,0,tmp);
    _control_mode_available = QString(QLatin1String(tmp));
    qDebug() <<_control_mode_available;

    _iio_device->get_rx_gain_value(0,tmp);
    get_str_tmp = QString(QLatin1String(tmp));
    get_str_tmp.remove("[");
    get_str_tmp.remove("]");
    get_str_list_tmp = get_str_tmp.split(" ");
    _rx_gain_range.push_back(get_str_list_tmp.at(0).toInt());
    _rx_gain_range.push_back(get_str_list_tmp.at(2).toInt());
    qDebug() << "* rx gain range *: " << _rx_gain_range;

    _iio_device->get_sampling_frequency_available(RX,0,tmp);
    get_str_tmp = QString(QLatin1String(tmp));
    get_str_tmp.remove("[");
    get_str_tmp.remove("]");
    get_str_list_tmp = get_str_tmp.split(" ");
    _rx_sampling_fre_range.push_back(get_str_list_tmp.at(0).toLongLong());
    _rx_sampling_fre_range.push_back(get_str_list_tmp.at(2).toLongLong());
    qDebug() << "* rx sampling frequency *:" << _rx_sampling_fre_range;

    _iio_device->get_bandwidth_available(RX,0,tmp);
    get_str_tmp = QString(QLatin1String(tmp));
    get_str_tmp.remove("[");
    get_str_tmp.remove("]");
    get_str_list_tmp = get_str_tmp.split(" ");
    _rx_bandwidth_range.push_back(get_str_list_tmp.at(0).toLongLong());
    _rx_bandwidth_range.push_back(get_str_list_tmp.at(2).toLongLong());
    qDebug() << "* rx bandwidth range *:" << _rx_bandwidth_range;
}

void iio_thread::recv_info_ip(QString info) {
    if(info.compare("stop") == 0){
        _is_stop  = true;
        _control_mode_available.clear();
        _rx_gain_range.clear();
        _rx_sampling_fre_range.clear();
        _rx_bandwidth_range.clear();
    }
    else
    {
        if(!_is_run_rx){
            if(info.isEmpty())
            {
                _ip = "ip:192.168.2.1";
                qDebug() << ("use default ip:192.168.2.1");
            }
            else{
                QString info_send("use ");
                info_send.append(info);
                _ip = info.toStdString();
            }
            _try_connect = true;
        }
        else{
        }
    }
}

iio_thread::~iio_thread() {

}

void iio_thread::recv_discon_button() {
    if(_is_run_rx){
        _is_run_rx = false;
        _is_button_on = true;
        emit send_info("unconnect");
        _control_mode_available.clear();
        _rx_gain_range.clear();
        _rx_sampling_fre_range.clear();
        _rx_bandwidth_range.clear();
    }
//    else{
//    }
}

void iio_thread::time_send_fft() {
    if(_is_run_rx){
        run_get_stream();
        if(_scan_width == 1)
            emit send_fft_data(_send_all_data, _send_all_data.size(),
                           _rx_cfg.lo_hz, _rx_cfg.bw_hz);
        else
            emit send_fft_data(_send_all_data, _send_all_data.size(),
                               _lo_recv, MHZ(_scan_width));
        _send_all_data.clear();
    }
}

void iio_thread::recv_config_value(QString config) {
    _lo_recv = config.toLongLong();
    _lo_scan.clear();
}


void iio_thread::recv_rx_gain_mode(QString rx_mode) {
    if(_is_run_rx)
    {
        _iio_device->set_ad9361_rx_gain_mode(RX,rx_mode.toStdString().c_str(),0);
    }
}

void iio_thread::recv_rx_gain_value(QString gain_value) {
    if(_is_run_rx){
        _iio_device->set_ad9361_rx_gain_value(RX,gain_value.toLongLong(),0);
    }
}



void iio_thread::set_send_rwb() {
    QString rwb_string("RWB:");
    if(_rbw >= 1000){
        rwb_string.push_back(QString::number(_rbw / 1000,'f',2));
        rwb_string.push_back("KHz");
    }
    else{
        rwb_string.push_back(QString::number(_rbw,'f',2));
        rwb_string.push_back("Hz");
    }
    qDebug() << rwb_string;
    emit(send_RWB(rwb_string));
}

/**
 * get bandwidth div for recursive call chain
 * */
void iio_thread::get_bdwidth_div(float scan_width) {
    if(scan_width <= 5)
    {
        return ;
    }
    _div_cnt++;
    get_bdwidth_div(scan_width / 2.0f);
}


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

void iio_thread::recv_config_bd(QString bd_width) {
    _lo_scan.clear();
    _scan_width = bd_width.toFloat();
    if(_scan_width <= 1){
        _rx_cfg.fs_hz = MHZ(2.083334);
        _rx_cfg.bw_hz = MHZ(2.083334);
        FFT_N = 1024;
        _samples_count = FFT_N*2;
        _rbw = _rx_cfg.bw_hz / _samples_count;
        qDebug() << "rbw:" << _rbw;
        qDebug() << "_samples_count:" << _samples_count;
        _lo_scan.push_back(_lo_recv);
        _rx_cfg.lo_hz = _lo_scan.at(0);
        if(_is_run_rx){
            /* calculate RWB(Resolution Bandwidth) */
            _iio_device->set_ad9361_lo_hz(RX,0,_rx_cfg.lo_hz);
            _iio_device->set_ad9361_bd_hz(RX,0,_rx_cfg.bw_hz);
            _iio_device->set_ad9361_fs_hz(RX,0,_rx_cfg.fs_hz);
        }
    }
    else{
        if(_scan_width <= 5){
            _rx_cfg.bw_hz = MHZ(_scan_width);
            if(_rx_cfg.bw_hz == MHZ(2))
                _rx_cfg.fs_hz = MHZ(2.083334);
            else
                _rx_cfg.fs_hz = _rx_cfg.bw_hz;
            _fft_n_coefficient = 4;
            FFT_N = FFT_BASE*pow(2,_fft_n_coefficient);
            _rbw = _rx_cfg.bw_hz / FFT_N;
            _samples_count = FFT_N;
            fftw_free(_in);
            fftw_free(_out);
            _in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
            _out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
            _iio_device->malloc_iio_buffer(_samples_count);
            _lo_scan.push_back(_lo_recv);
            _rx_cfg.lo_hz = _lo_scan.at(0);
            if(_is_run_rx){
                /* calculate RWB(Resolution Bandwidth) */
                _iio_device->set_ad9361_lo_hz(RX,0,_rx_cfg.lo_hz);
                _iio_device->set_ad9361_bd_hz(RX,0,_rx_cfg.bw_hz);
                _iio_device->set_ad9361_fs_hz(RX,0,_rx_cfg.fs_hz);
            }
        }
        else{
            /* step */
            // calculate the config lo
            double _div_width = _scan_width / 2.0;
            _div_cnt = 0;
            get_bdwidth_div(_scan_width);
            _div_width = _scan_width / pow(2,_div_cnt);
            long long start_scan_lo = _lo_recv - (MHZ(_scan_width) / 2.0) + (MHZ(_div_width) / 2.0);
            for(int i = 0;i < (int)pow(2,_div_cnt);i++)
            {
                _lo_scan.push_back(start_scan_lo+ MHZ(_div_width)*i);
            }
            _rx_cfg.bw_hz = MHZ(_div_width);
            _rx_cfg.fs_hz = _rx_cfg.bw_hz;
            if(_is_run_rx){
                _iio_device->set_ad9361_lo_hz(RX,0,_rx_cfg.lo_hz);
                _iio_device->set_ad9361_bd_hz(RX,0,_rx_cfg.bw_hz);
                _iio_device->set_ad9361_fs_hz(RX,0,_rx_cfg.fs_hz);

            }
            _fft_n_coefficient = 4;
            FFT_N = FFT_BASE*pow(2,_fft_n_coefficient);
            _rbw = _rx_cfg.bw_hz / FFT_N;
            _samples_count = FFT_N;
            fftw_free(_in);
            fftw_free(_out);
            _in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
            _out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FFT_N);
            _iio_device->malloc_iio_buffer(_samples_count);
        }
    }
    set_send_rwb();
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

void iio_thread::run() {
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

void iio_thread::recv_RWB(bool is_add) {
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

void iio_thread::run_get_stream() {
    fftw_plan p;
    /* scan band width step is 1MHz */
    if(_lo_scan.size() == 1){
        _iio_device->get_iio_data(_in, FFT_N, _samples_count);
        p = fftw_plan_dft_1d(FFT_N,_in,_out,FFTW_FORWARD,FFTW_ESTIMATE);
        fftw_execute(p);
        _send_data.resize(FFT_N);
        for(int i = _send_data.size() / 2,j = 0;i<_send_data.size();i++,j++)
        {
            double M = sqrt((_out[i][0])*(_out[i][0]) + (_out[i][1])*(_out[i][1]));
            double A = 2 * M / FFT_N;
            _send_data[j] = (20*log10(A / 1e3));
        }
        for(int i = 0,j = _send_data.size() / 2;i<_send_data.size() / 2;i++,j++)
        {
            double M = sqrt((_out[i][0])*(_out[i][0]) + (_out[i][1])*(_out[i][1]));
            double A = 2 * M / FFT_N;
            _send_data[j] = (20*log10(A / 1e3));
        }
        _send_all_data.append(_send_data);
        if(_is_button_on){
            _is_button_on = false;
        }
    }
    else{
        for(int index = 0;index < (int)_lo_scan.size();index++){
            _rx_cfg.lo_hz = _lo_scan.at(index);
            _iio_device->set_ad9361_lo_hz(RX,0,_rx_cfg.lo_hz);
            _iio_device->get_iio_data(_in, FFT_N, _samples_count);
            p = fftw_plan_dft_1d(FFT_N,_in,_out,FFTW_FORWARD,FFTW_ESTIMATE);
            fftw_execute(p);
            _send_data.resize(FFT_N);
            for(int i = _send_data.size() / 2,j = 0;i<_send_data.size();i++,j++)
            {
                double M = sqrt((_out[i][0])*(_out[i][0]) + (_out[i][1])*(_out[i][1]));
                double A = 2 * M / FFT_N;
                _send_data[j] = (20*log10(A / 1e3));
            }
            for(int i = 0,j = _send_data.size() / 2;i<_send_data.size() / 2;i++,j++)
            {
                double M = sqrt((_out[i][0])*(_out[i][0]) + (_out[i][1])*(_out[i][1]));
                double A = 2 * M / FFT_N;
                _send_data[j] = (20*log10(A / 1e3));
            }
            _send_all_data.append(_send_data);
            if(_is_button_on){
                _is_button_on = false;
            }
        }
    }
}
