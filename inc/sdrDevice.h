//
// Created by jcc on 22-11-14.
//

#ifndef SDR_SDRDEVICE_H
#define SDR_SDRDEVICE_H

#include "string"
#include "iostream"
#include <memory>

#define MHZ(x) ((long long)(x*1000000.0 + .5))
#define GHZ(x) ((long long)(x*1000000000.0 + .5))

#define IIO
#define UHD
namespace mp{

    using namespace std;

    typedef struct{
        int16_t *data;
        int length;
    } sdr_transfer;

    typedef void(*RX_data_callback)(sdr_transfer *transfer_info);

class sdrDevice{
    /* device string
     * d_string:pluto or uhd
     * */
public:
    typedef std::shared_ptr<sdrDevice> sdr_sptr;
    virtual ~sdrDevice(void) = 0;

    static sdr_sptr make_sdrDevice(const std::string& driver_type,
                                         const std::string& ip);

    virtual void sdr_open() = 0;
    virtual void sdr_close() = 0;
    virtual bool sdr_check(int channel) = 0;
    virtual void sdr_set_gain(double gain, int channel) = 0;
    virtual void sdr_set_samplerate(double sample_rate, int channel) = 0;
    virtual void sdr_set_bandwidth(double bandwidth, int channel) = 0;
    virtual void sdr_set_lo_frequency(double frequency) = 0;
    virtual void sdr_set_rx_samplecnt(uint32_t sample_cnt) = 0;
    virtual void sdr_set_reset_rx_samplecount(uint32_t sample_cnt) = 0;
    virtual void sdr_start_rx(RX_data_callback handler) = 0;
    virtual void sdr_stop_rx() = 0;
};

}

#endif //SDR_SDRDEVICE_H
