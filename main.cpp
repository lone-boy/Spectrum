#include <QApplication>
#include "display.h"
#include "device_config.h"

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    device_config *device_window = new device_config();
    device_window->show();
    return app.exec();
//    QApplication app(argc,argv);
//    mywindow *w = new mywindow();
//    QObject::connect(&app, SIGNAL(aboutToQuit()), w, SLOT(quitting()));
//    w->start(); // Start the flowgraph
//    w->show();  // show the window
//    app.exec(); // run the QT executor loop
//    return 0;
}
