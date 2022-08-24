//
// Created by jcc on 22-8-9.
//

#ifndef SPECTRUM_IIO_DEVICE_SCAN_HPP
#define SPECTRUM_IIO_DEVICE_SCAN_HPP

#include "iio.h"
#include "string"
#include "cassert"
#include "iostream"
#include "QSharedPointer"
#include "cmath"
#include "fft/fftw3.h"
#include "QVector"
#include "ad9361.h"

#define LOG(format,args...) { \
               qDebug(format,##args); \
               fflush(stdout); \
}
#define MHZ(x) ((long long)(x*1000000.0 + .5))
#define GHZ(x) ((long long)(x*1000000000.0 + .5))
#define MANUAL "manual"
#define FAST    "fast_attack"
#define SLOW    "slow_attack"
#define HYB     "hybrid"

typedef struct stream_cfg
{
    long long bw_hz; // Analog banwidth in Hz
    long long fs_hz; // Baseband sample rate in Hz
    long long lo_hz; // Local oscillator frequency in Hz
    const char* rfport; // Port name
} stream_cfg_s;

enum iodev { RX, TX };

class iio{
public:
    virtual ~iio() = 0;
    typedef QSharedPointer<iio> sptr;
    static sptr make_iio();
    virtual bool connect_device(const std::string &ip) = 0;
    virtual bool set_ad9361_stream_dev(iodev d, stream_cfg_s cfg, int chid)  = 0;
    virtual void enable_iio_channel()  = 0;
    virtual bool malloc_iio_buffer(uint32_t samples_count) = 0;
    virtual void get_iio_data(fftw_complex (*in), int fft_n, uint32_t samp_cnt) = 0;
    virtual bool set_ad9361_rx_gain_mode(iodev d, const char *mode, int chid) = 0;
    virtual bool set_ad9361_rx_gain_value(iodev d, long long value, int chid) = 0;
    virtual void get_control_mode_available(iodev d, int chid, char control_mode_available[]) = 0;
    virtual void get_rx_gain_value(int chid, char rx_gain_available[]) = 0;
    virtual void get_sampling_frequency_available(iodev d, int chid, char frequency_available[]) = 0;
    virtual void get_bandwidth_available(iodev d,int chid,char bandwidth[]) = 0;
    virtual void set_ad9361_lo_hz(enum iodev type,int chid,long long lo_hz) = 0;
};

class iio_impl : public iio{
public:
    iio_impl(){
        _rx0_i = nullptr;
        _rx0_q = nullptr;
        _rx_buf = nullptr;
        _rx = nullptr;
    }
    ~iio_impl(){
        LOG("* IIO impl release *")
        if(_rx0_i) iio_channel_disable(_rx0_i);
        if(_rx0_q) iio_channel_disable(_rx0_q);
        if(_rx_buf) iio_buffer_destroy(_rx_buf);
        if(_ctx) iio_context_destroy(_ctx);

    }
    bool set_ad9361_rx_gain_mode(iodev d, const char *mode, int chid) override;
    bool set_ad9361_rx_gain_value(iodev d, long long value, int chid) override;
    bool malloc_iio_buffer(uint32_t samples_count) override;
    bool connect_device(const std::string &ip) override;
    bool set_ad9361_stream_dev(iodev d, stream_cfg_s cfg, int chid) override;
    void enable_iio_channel() override;
    void get_iio_data(fftw_complex (*in), int fft_n, uint32_t samp_cnt) override;
    void get_control_mode_available(iodev d, int chid, char control_mode_available[]) override;
    void get_rx_gain_value(int chid, char rx_gain_available[]) override;
    void get_sampling_frequency_available(iodev d, int chid, char frequency_available[]) override;
    void get_bandwidth_available(iodev d,int chid,char bandwidth[]) override;
    void set_ad9361_lo_hz(enum iodev type,int chid,long long lo_hz) override;

private:
    iio_context *_ctx;
    iio_channel *_rx0_i;
    iio_channel *_rx0_q;
    iio_buffer  *_rx_buf;
    iio_device  *_rx;
    void *_p_data;

    char _tmp_str[64];

    void errchk(int v,const char* what);
    void wr_ch_lli(struct iio_channel *chn,const char *what,long long val);
    void wr_ch_str(struct iio_channel *chn,const char *what,const char *str);
    char *get_ch_name(const char *type,int id);
    struct iio_device *get_ad9361_phy(struct iio_context *ctx);
    bool get_ad9361_stream_dev(struct iio_context *ctx,enum iodev d,struct iio_device **dev);
    bool get_ad9361_stream_ch(struct iio_context *ctx,enum iodev d,struct iio_device *dev,
                              int chid,struct iio_channel **chn);
    bool get_phy_chan(struct iio_context *ctx,enum iodev d,int chid,struct iio_channel **chn);
    bool get_lo_chan(struct iio_context *ctx,enum iodev d,struct iio_channel **chn);
    bool cfg_ad9361_stream_ch(struct iio_context *ctx,struct stream_cfg *cfg,enum iodev type,int chid);
};


#endif //SPECTRUM_IIO_DEVICE_SCAN_HPP
