//
// Created by jcc on 22-8-10.
//
#include "iio/iio_device_scan.hpp"


iio::~iio()
{
    /* NOP */
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
        case RX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("voltage", chid), false); return *chn != NULL;
        case TX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("voltage", chid), true);  return *chn != NULL;
        default: assert(0); return false;
    }
}

bool iio_impl::get_lo_chan(struct iio_context *ctx, enum iodev d, struct iio_channel **chn) {
    switch (d) {
        // LO chan is always output, i.e. true
        case RX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("altvoltage", 0), true); return *chn != NULL;
        case TX: *chn = iio_device_find_channel(get_ad9361_phy(_ctx), get_ch_name("altvoltage", 1), true); return *chn != NULL;
        default: assert(0); return false;
    }
}

bool iio_impl::cfg_ad9361_stream_ch(struct iio_context *ctx, struct stream_cfg *cfg, enum iodev type, int chid) {
    struct iio_channel *chn = nullptr;

    // Configure phy and lo channels
    LOG("* Acquiring AD9361 phy channel %d", chid);
    if (!get_phy_chan(_ctx, type, chid, &chn)) {	return false; }
    wr_ch_str(chn, "rf_port_select",     cfg->rfport);
    wr_ch_lli(chn, "rf_bandwidth",       cfg->bw_hz);
    wr_ch_lli(chn, "sampling_frequency", cfg->fs_hz);

    // Configure LO channel
    LOG("* Acquiring AD9361 %s lo channel", type == TX ? "TX" : "RX");
    if (!get_lo_chan(_ctx, type, &chn)) { return false; }
    wr_ch_lli(chn, "frequency", cfg->lo_hz);
    return true;
}



iio::sptr iio::make_iio()
{
    return sptr(new iio_impl());
}




