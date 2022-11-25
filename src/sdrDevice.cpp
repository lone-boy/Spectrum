//
// Created by jcc on 22-11-14.
//
#include "sdrDevice.h"
#include <utility>
#include "log.h"
#include "thread"
#include "functional"
#ifdef IIO
#include "iio.h"
#include "ad9361.h"
#endif
#ifdef UHD
#include "uhd/usrp/multi_usrp.hpp"
#endif
using namespace mp;

sdrDevice::~sdrDevice() {
    /* NOP */
}

#ifdef IIO
class iioDevice :public sdrDevice{
    enum iodev {RX,TX};
public:
    iioDevice(std::string  ip) :
    _device(std::move(ip)) ,_ctx(nullptr)
    ,_rx(nullptr),_resize_sample(0)
    ,_rx_buf(nullptr)
    ,_rx0_i(nullptr)
    ,_rx0_q(nullptr)
    ,_rx_thread(nullptr)
    ,_rx_handle(nullptr)
    ,_is_rx_running(false)
    ,_is_rx_buff_resize(false){
        _log.INFO("Create IIO device ...");
    }
    ~iioDevice() override{
        _log.INFO("Release IIO device ...");
        if(_rx0_i) iio_channel_disable(_rx0_i);
        if(_rx0_q) iio_channel_disable(_rx0_q);
        if(_rx_buf) iio_buffer_destroy(_rx_buf);
        if(_ctx) iio_context_destroy(_ctx);
    }
    void sdr_open() override{
        std::string info("Find device with ");
        info += _device;
        _log.INFO("iio device open ...");
        if (this->connect_device(_device)){
            info += string(" Succed ...");
            _log.INFO(info);
        }
        else{
            info += string(" Failed ...");
            _log.WARNING(info);
        }
    }
    void sdr_close() override{
        this->sdr_stop_rx();
        if(_ctx){
            iio_context_destroy(_ctx);
            _ctx = nullptr;
        }
    }
    void sdr_set_samplerate(double sample_rate, int channel) override{
        this->set_ad9361_fs_hz(RX,channel,(long long)sample_rate);
    }
    void sdr_set_bandwidth(double bandwidth, int channel) override{
        this->set_ad9361_bd_hz(RX,channel,(long long)bandwidth);
    }
    void sdr_set_lo_frequency(double frequency) override{
        this->set_ad9361_lo_hz(RX, (long long) frequency);
    }
    void sdr_set_gain(double gain, int channel) override{
        this->set_ad9361_rx_gain(RX,static_cast<int>(gain),channel);
    }
    bool sdr_check(int channel) override{
        if(_rx0_i) iio_channel_disable(_rx0_i);
        if(_rx0_q) iio_channel_disable(_rx0_q);
        set_ad9361_rx_gain_mode(RX,"manual",channel);
        this->sdr_set_bandwidth(2e6,channel);
        this->sdr_set_gain(70,channel);
        this->sdr_set_lo_frequency(100.1e6);
        this->sdr_set_samplerate(2e6 * 1.25f,channel);

        if(not get_ad9361_stream_dev(RX, &_rx))
            this->_log.ERROR("No stream dev ...");
        if(not get_ad9361_stream_ch(RX, _rx, 0, &_rx0_i)){
            this->_log.ERROR("No stream ch rx i");
        }
        if(not get_ad9361_stream_ch(RX, _rx, 1, &_rx0_q)){
            this->_log.ERROR("No stream ch rx q");
        }
        ad9361_set_bb_rate(_rx, 2e6 * 1.25f);
        this->enable_iio_channel();
        return true;
    }
    void sdr_set_rx_samplecnt(uint32_t sample_cnt) override{
        this->set_iio_rx_buffer(sample_cnt);
    }
    void sdr_set_reset_rx_samplecount(uint32_t sample_cnt) override{
        this->_is_rx_buff_resize = true;
        _resize_sample = sample_cnt;
    }
    void sdr_start_rx(RX_data_callback handler) override{
        _rx_handle = handler;
        if(!_is_rx_running && !_rx_thread){
            _is_rx_running = true;
            _rx_thread = new std::thread([this] { RXSync_thread(); });
        }
    }
    void sdr_stop_rx() override{
        _is_rx_running = false;
        if(_rx_thread && _rx_thread->joinable()){
            _rx_thread->join();
            delete(_rx_thread);
        }
        if(_rx_buf){
            iio_buffer_destroy(_rx_buf);
            _rx_buf = nullptr;
        }
        if(_rx0_i){
            iio_channel_disable(_rx0_i);
            _rx0_i = nullptr;
        }
        if(_rx0_q){
            iio_channel_disable(_rx0_q);
            _rx0_q = nullptr;
        }
    }

    /**
     * iio sdr
     * **/
    void RXSync_thread();

private:
    mp::log _log;
    string _device;
    /* iio */
    iio_context *_ctx;
    iio_channel *_rx0_i;
    iio_channel *_rx0_q;
    iio_buffer  *_rx_buf;
    iio_device  *_rx;
    uint32_t _resize_sample;
    char _tmp_str[64];
    std::thread *_rx_thread;
    bool _is_rx_running,_is_rx_buff_resize;
    RX_data_callback _rx_handle;

    bool connect_device(const std::string &ip);
    void errchk(int v,const char *what);
    void wr_ch_lli(struct iio_channel *chn,const char *what,long long val);
    void wr_ch_str(struct iio_channel *chn,const char *what,const char *str);
    char *get_ch_name(const char *type,int id);
    struct iio_device *get_ad9361_phy(struct iio_context *ctx);
    bool get_ad9361_stream_dev(iioDevice::iodev d, struct iio_device **dev);
    bool get_ad9361_stream_ch(iioDevice::iodev d, struct iio_device *dev, int chid, struct iio_channel **chn);
    bool get_phy_chan(iioDevice::iodev d, int chid, struct iio_channel **chn);
    bool get_lo_chan(iioDevice::iodev d, struct iio_channel **chn);
    void set_ad9361_lo_hz(iioDevice::iodev type, long long int lo_hz);
    void set_ad9361_bd_hz(enum iodev type,int chid,long long bd_hz);
    void set_ad9361_fs_hz(enum iodev type,int chid,long long fs);
    bool set_ad9361_rx_gain(iodev d, long long value, int chid);
    bool set_ad9361_rx_gain_mode(iodev d, const char *mode, int chid);
    bool set_iio_rx_buffer(uint32_t samples_count);
    void enable_iio_channel();
};

bool iioDevice::connect_device(const string &ip) {
    string info("Connect IIO device with ");
    info += ip;
    info += string(" ...");
    _log.INFO(info);
    _ctx = iio_create_context_from_uri(ip.c_str());
    if(_ctx == nullptr)
        return false;

    return true;
}

void iioDevice::errchk(int v, const char *what) {
    if (v < 0) {
        fprintf(stderr, "Error %d writing to channel \"%s\"\nvalue may not be supported.\n", v, what);
    }
}

void iioDevice::wr_ch_lli(struct iio_channel *chn, const char *what, long long int val) {
    errchk(iio_channel_attr_write_longlong(chn,what,val),what);
}

void iioDevice::wr_ch_str(struct iio_channel *chn, const char *what, const char *str) {
    errchk(static_cast<int>(iio_channel_attr_write(chn, what, str)), what);
}

char *iioDevice::get_ch_name(const char *type, int id) {
    snprintf(_tmp_str,sizeof(_tmp_str),"%s%d",type,id);
    return _tmp_str;
}

struct iio_device *iioDevice::get_ad9361_phy(struct iio_context *ctx) {
    struct iio_device *dev = iio_context_find_device(_ctx,"ad9361-phy");
    if(dev == nullptr)
        this->_log.ERROR("No ad9361-phy found ...");

    return dev;
}

bool iioDevice::get_ad9361_stream_dev(iioDevice::iodev d, struct iio_device **dev) {
    switch (d) {
        case TX: *dev = iio_context_find_device(_ctx,"cf-ad9361-dds-core-lpc"); return *dev != nullptr;
        case RX: *dev = iio_context_find_device(_ctx, "cf-ad9361-lpc");  return *dev != nullptr;
        default:
            this->_log.ERROR("No stream dev found ...");return false;
    }
}

bool iioDevice::get_ad9361_stream_ch(iioDevice::iodev d, struct iio_device *dev, int chid, struct iio_channel **chn) {
    *chn = iio_device_find_channel(dev, get_ch_name("voltage", chid), d == TX);
    if (!*chn)
        *chn = iio_device_find_channel(dev, get_ch_name("altvoltage", chid), d == TX);
    return *chn != nullptr;
}

bool iioDevice::get_phy_chan(iioDevice::iodev d, int chid, struct iio_channel **chn) {
    switch (d) {
        case RX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("voltage", chid), false);
            return *chn !=nullptr;
        case TX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("voltage", chid), true);
            return *chn != nullptr;
        default:
            this->_log.ERROR("No phy channel found ..."); return false;
    }
}

bool iioDevice::get_lo_chan(iioDevice::iodev d, struct iio_channel **chn) {
    switch (d) {
        // LO chan is always output, i.e. true
        case RX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("altvoltage", 0), true); return *chn != NULL;
        case TX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("altvoltage", 1), true); return *chn != NULL;
        default: this->_log.ERROR("No lo channel found ...");return false;
    }
}

void iioDevice::set_ad9361_lo_hz(iioDevice::iodev type, long long int lo_hz) {
    struct iio_channel *chn = nullptr;
    if (!get_lo_chan(type, &chn)) { return; }
    wr_ch_lli(chn, "frequency", lo_hz);
}

void iioDevice::set_ad9361_bd_hz(iioDevice::iodev type, int chid, long long int bd_hz) {
    struct iio_channel *chn = nullptr;
    if (!get_phy_chan(type, chid, &chn)) {	return; }
    wr_ch_lli(chn, "rf_bandwidth",       bd_hz);
}

void iioDevice::set_ad9361_fs_hz(iioDevice::iodev type, int chid, long long int fs) {
    struct iio_channel *chn = nullptr;
    if (!get_phy_chan(type, chid, &chn)) {	return; }
    string info("Sampling frequency ");
    info += to_string(fs);
    this->_log.DEBUG(info);
    wr_ch_lli(chn, "sampling_frequency",       fs);
}

bool iioDevice::set_ad9361_rx_gain(iioDevice::iodev d, long long value, int chid) {
    struct iio_channel *chn = nullptr;
    if(!get_phy_chan(d, chid, &chn)) { return false;}
    wr_ch_lli(chn,"hardwaregain",value);
    return true;
}

bool iioDevice::set_ad9361_rx_gain_mode(iioDevice::iodev d, const char *mode, int chid) {
    struct iio_channel *chn = nullptr;
    if(!get_phy_chan(d, chid, &chn)) { return false;}
    wr_ch_str(chn,"gain_control_mode",mode);
    return true;
}

void iioDevice::enable_iio_channel() {
    iio_channel_enable(_rx0_i);
    iio_channel_enable(_rx0_q);
}

bool iioDevice::set_iio_rx_buffer(uint32_t samples_count) {
    if(_rx_buf){
        this->_log.INFO("Destroy iio buffer ...");
        iio_buffer_destroy(_rx_buf);
    }
    if(_rx){
        this->_log.INFO("Set kernel Rx buffer ...");
        iio_device_set_kernel_buffers_count(_rx,2);
        _rx_buf = iio_device_create_buffer(_rx,samples_count, false);
    }
    if(!_rx_buf)
    {
        this->_log.INFO("Could not create Rx buffer ...");
        return false;
    }
    return true;
}
/* start a new thread */
void iioDevice::RXSync_thread() {
    _is_rx_buff_resize = false;
    sdr_transfer trans;
    while(_is_rx_running){
        if(_is_rx_buff_resize){
            if(_rx_buf){
                iio_buffer_destroy(_rx_buf);
                _rx_buf = nullptr;
            }
            _rx_buf = iio_device_create_buffer(_rx,_resize_sample, false);
            _is_rx_buff_resize = false;
        }
        size_t iio_read_size = iio_buffer_refill(_rx_buf);
        if(iio_read_size > 0){
            trans.data = (int16_t *) iio_buffer_start(_rx_buf);
            trans.length = (int)iio_read_size / 4;
            _rx_handle(&trans);
        }
        else{
            break;
        }
    }
    _is_rx_running  = false;
}
#endif

/**
 * -----------------------------------------------------------------------------------------------------------------
 * UHD INTERFACE
 * -----------------------------------------------------------------------------------------------------------------
 * */
#ifdef UHD
class uhdDevice : public sdrDevice{
public:
    uhdDevice(std::string  ip) :_device(std::move(ip))
    ,_rx_stream(nullptr)
    , _stream_args("sc16")
    ,_buff(0)
    ,_rx_handle(nullptr)
    ,_rx_thread(nullptr)
    ,_is_rx_running(false)
    {

    }
    ~uhdDevice(){
        _rx_stream->issue_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS);
    }
    void sdr_open() override{
        this->_log.INFO("Create UHD device ...");
        _uhd_device = uhd::usrp::multi_usrp::make(_device);

    }
    void sdr_close() override{
        _rx_stream->issue_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS);
    }
    void sdr_set_samplerate(double sample_rate, int channel) override{
        _uhd_device->set_rx_rate(sample_rate,channel);
    }
    void sdr_set_gain(double gain, int channel) override{
        _uhd_device->set_rx_gain(gain,channel);
    }
    void sdr_set_bandwidth(double bandwidth, int channel) override{
        _uhd_device->set_rx_bandwidth(bandwidth,channel);
    }
    void sdr_set_lo_frequency(double frequency) override{
//        this->_log.DEBUG("Sdr set lo frequency ...");
        uhd::tune_result_t actual = _uhd_device->set_rx_freq(frequency);
        string log("Sdr actual get ");
        log += to_string(actual.actual_rf_freq);
//        this->_log.DEBUG(log);
    }
    bool sdr_check(int channel) override{
        this->_log.DEBUG("Sdr check ...");
        std::vector<string> sensor_names;
        std::string ref;
        sensor_names = _uhd_device->get_rx_sensor_names(channel);
        if (std::find(sensor_names.begin(), sensor_names.end(), "lo_locked")
            != sensor_names.end()) {
            uhd::sensor_value_t lo_locked = _uhd_device->get_rx_sensor("lo_locked", 0);
            std::cout << boost::format("Checking RX: %s ...") % lo_locked.to_pp_string()
                      << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());
        }
        sensor_names = _uhd_device->get_mboard_sensor_names(0);
        if ((ref == "mimo")
            and (std::find(sensor_names.begin(), sensor_names.end(), "mimo_locked")
                 != sensor_names.end())) {
            uhd::sensor_value_t mimo_locked = _uhd_device->get_mboard_sensor("mimo_locked", 0);
            std::cout << boost::format("Checking RX: %s ...") % mimo_locked.to_pp_string()
                      << std::endl;
            UHD_ASSERT_THROW(mimo_locked.to_bool());
        }
        if ((ref == "external")
            and (std::find(sensor_names.begin(), sensor_names.end(), "ref_locked")
                 != sensor_names.end())) {
            uhd::sensor_value_t ref_locked = _uhd_device->get_mboard_sensor("ref_locked", 0);
            std::cout << boost::format("Checking RX: %s ...") % ref_locked.to_pp_string()
                      << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());
        }
        _uhd_device->set_rx_agc(false,0);
        return true;
    }
    void sdr_set_rx_samplecnt(uint32_t sample_cnt) override{
        _sample_size = sample_cnt;
        if(not _is_rx_running)
            _buff.resize(_sample_size*2);
        else
            _is_rx_buff_resize = true;
    }
    void sdr_start_rx(RX_data_callback handler) override{
        _rx_handle = handler;

        _rx_stream = _uhd_device->get_rx_stream(_stream_args);
        _rx_stream->issue_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
        if(!_is_rx_running && ! _rx_thread){
            _is_rx_running = true;
            _rx_thread = new std::thread([this] { RXSync_thread(); });
        }

    }
    void sdr_set_reset_rx_samplecount(uint32_t sample_cnt) override{
        _sample_size = sample_cnt;
        _is_rx_buff_resize = true;
    }
    void sdr_stop_rx() override{
        _rx_stream->issue_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS);
        if(_rx_thread && _rx_thread->joinable()){
            _rx_thread->join();
            delete(_rx_thread);
        }
        _is_rx_running = false;
    }

    void RXSync_thread();
private:
    string _device;
    mp::log _log;

    uhd::usrp::multi_usrp::sptr _uhd_device;
    uhd::stream_args_t _stream_args;
    uhd::rx_streamer::sptr _rx_stream;
    std::vector<int16_t> _buff;

    uint32_t _sample_size;
    RX_data_callback _rx_handle;
    thread *_rx_thread;
    bool _is_rx_running,_is_rx_buff_resize;

};

void uhdDevice::RXSync_thread() {
    _is_rx_buff_resize = false;
    sdr_transfer trans;
    uhd::rx_metadata_t md;
    trans.data = &_buff.front();
    try {
        while(_is_rx_running){
            if(_is_rx_buff_resize){
                _buff.resize(_sample_size * 2);
            }
            int num_rx_samps = _rx_stream->recv(&_buff.front(),_sample_size,md,0.0, false);
            if(num_rx_samps == _sample_size){
                trans.length = num_rx_samps;
            }
            _rx_handle(&trans);
        }
        _rx_stream->issue_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS);
    }
    catch (std::exception& ex){
        string log(ex.what());
        this->_log.ERROR(log);
    }
}

#endif

sdrDevice::sdr_sptr sdrDevice::make_sdrDevice(const std::string& driver_type,const std::string& ip) {
#ifdef UHD
    if(driver_type == "uhd"){
        return sdr_sptr(new uhdDevice(ip));
    }
#endif
#ifdef IIO
    if(driver_type == "iio"){
        return sdr_sptr (new iioDevice(ip));
    }
#endif
    return nullptr;
}