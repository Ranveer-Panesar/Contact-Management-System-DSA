#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setApplicationName("Contact Management System");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("DSA Project");

    MainWindow window;
    window.show();

    return app.exec();
}
