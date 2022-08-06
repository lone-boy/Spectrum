//
// Created by jcc on 22-8-6.
//
#include "display.h"

mywindow::mywindow() : QWidget()
{
    // We'll use a horizontal layout of two QTabWidgets
    layout = new QHBoxLayout();

    // Create the tab widgets
    tab0 = new QTabWidget();
    tab1 = new QTabWidget();

    // Add the tab widgets to the layou
    layout->addWidget(tab0);
    layout->addWidget(tab1);

    // Set the layout as the main widget's layou
    setLayout(layout);

    // Simple resizing of the app
    resize(2000, 800);

    // sample rate
    int rate = 48000;

    // Create the GNU Radio top block
    tb = make_top_block("display_qt");

    // Source will be sine wave in noise
    src0 = analog::sig_source_f::make(rate, analog::GR_SIN_WAVE, 1500, 1);
    src1 = analog::noise_source_f::make(analog::GR_GAUSSIAN, 0.1);

    // Combine signal and noise; add throttle
    src = blocks::add_ff::make();
    thr = blocks::throttle::make(sizeof(float), rate);

    // Create the QTGUI sinks
    // Time, Freq, Waterfall, and Histogram sinks
    tsnk = qtgui::time_sink_f::make(1024, rate, "", 1);
    fsnk = qtgui::freq_sink_f::make(1024, fft::window::WIN_HANN, 0, rate, "", 1);
    wsnk = qtgui::waterfall_sink_f::make(1024, fft::window::WIN_HANN, 0, rate, "", 1);
    hsnk = qtgui::histogram_sink_f::make(1024, 100, -2, 2, "", 1);

    // Turn off the legend on these plots
    tsnk->disable_legend();
    fsnk->disable_legend();
    hsnk->disable_legend();

    // Connect the graph
    tb->connect(src0, 0, src, 0);
    tb->connect(src1, 0, src, 1);
    tb->connect(src, 0, thr, 0);
    tb->connect(thr, 0, tsnk, 0);
    tb->connect(thr, 0, fsnk, 0);
    tb->connect(thr, 0, wsnk, 0);
    tb->connect(thr, 0, hsnk, 0);

    // Get the raw QWidget objects from the GNU Radio blocks
    qtgui_time_sink_win = tsnk->qwidget();
    qtgui_freq_sink_win = fsnk->qwidget();
    qtgui_waterfall_sink_win = wsnk->qwidget();
    qtgui_histogram_sink_win = hsnk->qwidget();

    // Plug the widgets into the tabs
    tab0->addTab(qtgui_time_sink_win, "Time");
    tab0->addTab(qtgui_histogram_sink_win, "Hist");
    tab1->addTab(qtgui_freq_sink_win, "Freq");
    tab1->addTab(qtgui_waterfall_sink_win, "Waterfall");
}

mywindow::~mywindow() {}

void mywindow::start() { tb->start(); }

void mywindow::quitting()
{
    tb->stop();
    tb->wait();
}

//int main(int argc, char** argv)
//{
//    // The global QT application
//    QApplication app(argc, argv);
//
//    mywindow* w = new mywindow();
//
//    QObject::connect(&app, SIGNAL(aboutToQuit()), w, SLOT(quitting()));
//
//    w->start(); // Start the flowgraph
//    w->show();  // show the window
//    app.exec(); // run the QT executor loop
//
//    return 0;
//}
