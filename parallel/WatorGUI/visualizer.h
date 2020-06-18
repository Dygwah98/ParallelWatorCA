#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QWidget>
#include "AC.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Visualizer; }
QT_END_NAMESPACE

class Visualizer : public QWidget
{
    Q_OBJECT

public:
    Visualizer(QWidget *parent = nullptr);
    ~Visualizer();

    void runAC();

private:
    Ui::Visualizer *ui;
    Cell ** mat;
    Cell ** tam;
    int dim;
};
#endif // VISUALIZER_H
