#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow *window = new MainWindow();
    window->setup();

    if (window->isSetupCanceled()) {
        delete window;
        return 0;
    }

    window->show();
    return app.exec();
}
