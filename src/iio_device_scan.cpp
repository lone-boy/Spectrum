//
// Created by jcc on 22-8-10.
//
#include "iio/iio_device_scan.hpp"

iio::~iio()
{
    /* NOP */
}
void iio_impl::get_control_mode_available(iodev d, int chid, char control_mode_available[]) {
    size_t read_length;
    struct iio_channel *chn = nullptr;
    if (!get_phy_chan(_ctx, d, chid, &chn)) {	return ; }
    read_length = iio_channel_attr_read(chn,"gain_control_mode_available",
                                        control_mode_available,50);
    if(read_length <= 0)
    {
        LOG("* get gain control mode available failed *")
    }
}

/***
 * set rx_gain mode
 * ***/
bool iio_impl::set_ad9361_rx_gain_mode(iodev d, const char *mode, int chid) {
    struct iio_channel *chn = nullptr;
    LOG("* Set rx gain mode *")
    if(!get_phy_chan(_ctx,d,chid,&chn)) { return false;}
    wr_ch_str(chn,"gain_control_mode",mode);
    LOG("* rx gain mode %s *",mode);
    return true;
}

void iio_impl::get_rx_gain_value(int chid, char rx_gain_available[]) {
    size_t read_length;
    struct iio_channel *chn = nullptr;
    LOG("* Get rx gain value *")
    if(!get_phy_chan(_ctx,RX,chid,&chn)) {return;}
    read_length = iio_channel_attr_read(chn,"hardwaregain_available",rx_gain_available,50);
    if(read_length <= 0)
    {
        LOG("* get get_rx_gain_value failed *")
    }
}

bool iio_impl::set_ad9361_rx_gain_value(iodev d, long long value, int chid){
    struct iio_channel *chn = nullptr;
    LOG("* Set rx gain value *");
    if(!get_phy_chan(_ctx,d,chid,&chn)) { return false;}
    wr_ch_lli(chn,"hardwaregain",value);
    return true;
}

void iio_impl::get_sampling_frequency_available(iodev d, int chid, char frequency_available[]) {
    size_t read_length;
    struct iio_channel *chn = nullptr;
    LOG("* Get frequency available *")
    if(!get_phy_chan(_ctx,d,chid,&chn)) {return;}
    read_length = iio_channel_attr_read(chn,"sampling_frequency_available",frequency_available,50);
    if(read_length <= 0)
    {
        LOG("* get sampling_frequency_available failed *")
    }
}

void iio_impl::get_bandwidth_available(iodev d, int chid, char *bandwidth) {
    size_t read_length;
    struct iio_channel *chn = nullptr;
    LOG("* Get bandwidth available *")
    if(!get_phy_chan(_ctx,d,chid,&chn)) {return;}
    read_length = iio_channel_attr_read(chn,"rf_bandwidth_available",bandwidth,50);
    if(read_length <= 0)
    {
        LOG("* get rf_bandwidth_available failed *")
    }
}

bool iio_impl::malloc_iio_buffer(uint32_t samples_count) {
    LOG("* Create iio buffer *")

    if(_rx_buf){
        LOG("* destroy iio buffer *")
        iio_buffer_destroy(_rx_buf);
    }
    if(_rx){
        iio_device_set_kernel_buffers_count(_rx,1);
        _rx_buf = iio_device_create_buffer(_rx,samples_count, false);
    }
    if(!_rx_buf)
    {
        LOG("* Could not create Rx buffer *");
        return false;
    }
    return true;
}

bool iio_impl::connect_device(const std::string &ip) {
    LOG("* Find context %s *" ,ip.c_str())
    _ctx = iio_create_context_from_uri(ip.c_str());
    if(_ctx == nullptr)
    {
        return false;
    }
    return true;
}

bool iio_impl::set_ad9361_stream_dev(iodev d, stream_cfg_s cfg, int chid) {
    if(_rx0_i) iio_channel_disable(_rx0_i);
    if(_rx0_q) iio_channel_disable(_rx0_q);

    if(not get_ad9361_stream_dev(_ctx,d,&_rx)){
        return false;
    }

    assert(get_ad9361_stream_dev(_ctx,d,&_rx) && "No _rx found");
    assert(cfg_ad9361_stream_ch(_ctx, &cfg, d, chid) && "RX port 0 not found");
    assert(get_ad9361_stream_ch(_ctx, RX, _rx, 0, &_rx0_i) && "RX chan i not found");
    assert(get_ad9361_stream_ch(_ctx, RX, _rx, 1, &_rx0_q) && "RX chan q not found");

    enable_iio_channel();
    return true;
}

void iio_impl::enable_iio_channel() {
    iio_channel_enable(_rx0_i);
    iio_channel_enable(_rx0_q);
}

void iio_impl::get_iio_data(fftw_complex (*in), int fft_n, uint32_t samp_cnt) {
    ssize_t nbytes_rx;
    ptrdiff_t p_inc;
    void *_p_end;
    nbytes_rx = iio_buffer_refill(_rx_buf);
    if(nbytes_rx < 0) LOG(" *refill buff %d* ",(int)nbytes_rx)
    p_inc = iio_buffer_step(_rx_buf);
    _p_end = iio_buffer_end(_rx_buf);

    int number = 0;
    int index = 0;
    int start = 0;
    if(samp_cnt / fft_n == 2)
        start = fft_n / 2;
    for(_p_data = iio_buffer_first(_rx_buf,_rx0_i);_p_data < _p_end;_p_data = (uint8_t *)_p_data + p_inc)
    {
        if(number >= start && index <  fft_n)
        {
            in[index][0] = ((int16_t*)_p_data)[0];
            in[index][1] = ((int16_t*)_p_data)[1];
            index++;
        }
        number++;
    }
}

void iio_impl::errchk(int v, const char *what) {
    if (v < 0) {
        fprintf(stderr, "Error %d writing to channel \"%s\"\nvalue may not be supported.\n", v, what);
    }
}

void iio_impl::wr_ch_lli(struct iio_channel *chn, const char *what, long long int val) {
    errchk(iio_channel_attr_write_longlong(chn,what,val),what);
}

void iio_impl::wr_ch_str(struct iio_channel *chn, const char *what, const char *str) {
    errchk(static_cast<int>(iio_channel_attr_write(chn, what, str)), what);
}

char *iio_impl::get_ch_name(const char *type, int id) {
    snprintf(_tmp_str,sizeof(_tmp_str),"%s%d",type,id);
    return _tmp_str;
}

struct iio_device *iio_impl::get_ad9361_phy(struct iio_context *ctx) {
    struct iio_device *dev = iio_context_find_device(_ctx,"ad9361-phy");
    assert(dev && "No ad9361-phy found");
    return dev;
}

bool iio_impl::get_ad9361_stream_dev(struct iio_context *ctx, enum iodev d, struct iio_device **dev) {
    switch (d) {
        case TX: *dev = iio_context_find_device(_ctx,"cf-ad9361-dds-core-lpc"); return *dev != nullptr;
        case RX: *dev = iio_context_find_device(_ctx, "cf-ad9361-lpc");  return *dev != nullptr;
        default:
            assert(0);return false;
    }

}

bool iio_impl::get_ad9361_stream_ch(struct iio_context *ctx, enum iodev d, struct iio_device *dev, int chid,
                                    struct iio_channel **chn) {
    *chn = iio_device_find_channel(dev, get_ch_name("voltage", chid), d == TX);
    if (!*chn)
        *chn = iio_device_find_channel(dev, get_ch_name("altvoltage", chid), d == TX);
    return *chn != nullptr;
}

bool iio_impl::get_phy_chan(struct iio_context *ctx, enum iodev d, int chid, struct iio_channel **chn) {
    switch (d) {
        case RX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("voltage", chid), false);
            return *chn !=nullptr;
        case TX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("voltage", chid), true);
            return *chn != nullptr;
        default: assert(0); return false;
    }
}

bool iio_impl::get_lo_chan(struct iio_context *ctx, enum iodev d, struct iio_channel **chn) {
    switch (d) {
        // LO chan is always output, i.e. true
        case RX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("altvoltage", 0), true); return *chn != NULL;
        case TX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("altvoltage", 1), true); return *chn != NULL;
        default: assert(0);
    }
}

bool iio_impl::cfg_ad9361_stream_ch(struct iio_context *ctx, struct stream_cfg *cfg, enum iodev type, int chid) {
    struct iio_channel *chn = nullptr;

    // Configure phy and lo channels
    if (!get_phy_chan(_ctx, type, chid, &chn)) {	return false; }
    wr_ch_str(chn, "rf_port_select",     cfg->rfport);
    wr_ch_lli(chn, "rf_bandwidth",       cfg->bw_hz);
    wr_ch_lli(chn, "sampling_frequency", cfg->fs_hz);

    // Configure LO channel
    if (!get_lo_chan(_ctx, type, &chn)) { return false; }
    wr_ch_lli(chn, "frequency", cfg->lo_hz);
    return true;
}

void iio_impl::set_ad9361_lo_hz(enum iodev type, int chid, long long int lo_hz) {
    struct iio_channel *chn = nullptr;
    if (!get_lo_chan(_ctx, type, &chn)) { return; }
    wr_ch_lli(chn, "frequency", lo_hz);
}


iio::sptr iio::make_iio()
{
    return sptr(new iio_impl());
}






