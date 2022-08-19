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
    virtual bool malloc_iio_buffer() = 0;
    virtual void get_iio_data(fftw_complex *in, int fft_n) = 0;
    virtual void set_ad9361_rx_gain_mode(iodev d, const char *mode, int chid) = 0;
    virtual void set_ad9361_rx_gain_value(iodev d,long long value,int chid) = 0;
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
    void set_ad9361_rx_gain_mode(iodev d, const char *mode, int chid) override{
        set_rx_gain_mode(d,mode,chid);
    }
    void set_ad9361_rx_gain_value(iodev d, long long value, int chid) override{
        set_rx_gain_manual_value(d,value,chid);
    }
    bool malloc_iio_buffer() override{
        LOG("* Create iio buffer *")
//        iio_device_set_kernel_buffers_count(_rx,1);
        _rx_buf = iio_device_create_buffer(_rx,1024*10, false);
        if(!_rx_buf)
        {
            LOG("* Could not create Rx buffer *");
            return false;
        }
        return true;
    }
    bool connect_device(const std::string &ip) override{
        LOG("* Find context %s *" ,ip.c_str())
        _ctx = iio_create_context_from_uri(ip.c_str());
        if(_ctx == nullptr)
        {
            return false;
        }
        return true;
    }
    bool set_ad9361_stream_dev(iodev d, stream_cfg_s cfg, int chid) override{
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
    void enable_iio_channel() override{
        iio_channel_enable(_rx0_i);
        iio_channel_enable(_rx0_q);
    }
    void get_iio_data(fftw_complex *in, int fft_n) override{
        ssize_t nbytes_rx;
        ptrdiff_t p_inc;
        void *_p_end;
        nbytes_rx = iio_buffer_refill(_rx_buf);
        if(nbytes_rx < 0) LOG(" *refill buff %d* ",(int)nbytes_rx)
        p_inc = iio_buffer_step(_rx_buf);
        _p_end = iio_buffer_end(_rx_buf);

        int number = 10240 / fft_n;
        int index = 0;
        for(_p_data = iio_buffer_first(_rx_buf,_rx0_i);_p_data < _p_end;_p_data = (uint8_t *)_p_data + p_inc * number)
        {
            in[index][0] = ((int16_t*)_p_data)[0];
            in[index][1] = ((int16_t*)_p_data)[1];
            index++;
        }
    }
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
    bool set_rx_gain_mode(enum iodev type, const char *mode, int chid);
    bool set_rx_gain_manual_value(enum iodev type, long long int gain_value, int chid);
};


#endif //SPECTRUM_IIO_DEVICE_SCAN_HPP
