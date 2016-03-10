#include <QApplication>
#include "MainWindow.h"
#include "Quoridor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto model = G36631::Quoridor();
    MainWindow *widget = new MainWindow(model);
    widget->show();
    return app.exec();
}
