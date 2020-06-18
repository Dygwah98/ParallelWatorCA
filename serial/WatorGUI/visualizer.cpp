#include "visualizer.h"
#include "ui_visualizer.h"

Visualizer::Visualizer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Visualizer), dim(25)
{
    ui->setupUi(this);

    allocateMatrices(&mat, &tam, dim);
}

Visualizer::~Visualizer()
{
    freeMatrices(&mat, &tam, dim);
    delete ui;
}

void Visualizer::runAC() {

    runWator(&mat, &tam, dim);
}
