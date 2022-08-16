#include <QApplication>
#include "device_config.h"

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    auto *device_window = new device_config();
    device_window->show();
    app.exec();
    return 0;
}
