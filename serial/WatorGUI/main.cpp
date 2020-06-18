#include "visualizer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);
    Visualizer w;
    w.setFixedSize(w.geometry().width(), w.geometry().height());
    w.show();

    return a.exec();
}
