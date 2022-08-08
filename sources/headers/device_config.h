//
// Created by jcc on 22-8-6.
//

#ifndef SPECTRUM_DEVICE_CONFIG_H
#define SPECTRUM_DEVICE_CONFIG_H

#include <QWidget>
#include <QtWidgets/QVBoxLayout>
#include "qtabwidget.h"
#include <gnuradio/analog/noise_source.h>
#include <gnuradio/analog/sig_source.h>
#include <gnuradio/blocks/add_blk.h>
#include <gnuradio/blocks/throttle.h>
#include <gnuradio/fft/window.h>
#include <gnuradio/qtgui/freq_sink_f.h>
#include <gnuradio/qtgui/histogram_sink_f.h>
#include <gnuradio/qtgui/time_sink_f.h>
#include <gnuradio/qtgui/waterfall_sink_f.h>
#include <gnuradio/top_block.h>

QT_BEGIN_NAMESPACE
namespace Ui { class device_config; }
QT_END_NAMESPACE

using namespace gr;

class device_config : public QWidget {
Q_OBJECT

public:
    explicit device_config(QWidget *parent = nullptr);

    ~device_config() override;


public slots:
    void on_button_connect_clicked();
    void on_button_clear_clicked();
    void on_button_open_clicked();

public:
    void start();
    void quitting();

private:
    top_block_sptr _tb;
    QTabWidget* _tab0;
    QWidget* _qtgui_freq_sink_win;
    qtgui::freq_sink_f::sptr _fsnk;
    blocks::add_ff::sptr _src;
    blocks::throttle::sptr _thr;
    analog::sig_source_f::sptr _src0;


    Ui::device_config *ui;
};


#endif //SPECTRUM_DEVICE_CONFIG_H
