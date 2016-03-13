#include <QApplication>
#include "MainWindow.h"
#include "Quoridor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto model = G36631::Quoridor();
    G36631::MainWindow *widget = new G36631::MainWindow(model);
    widget->show();
    int ret = app.exec();
    delete widget;
    return ret;
}
