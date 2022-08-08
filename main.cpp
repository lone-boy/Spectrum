#include <QApplication>
#include "display.h"
#include "device_config.h"

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    device_config *device_window = new device_config();
    device_window->show();
    return app.exec();
}
