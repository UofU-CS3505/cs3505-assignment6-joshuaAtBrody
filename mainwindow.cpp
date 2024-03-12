#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QImage>
#include <QDebug>

#include "Model.h"

MainWindow::MainWindow(Model& model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    image1("../RedBlueSimonBackground.png")
{
    qDebug() << image1;
    ui->setupUi(this);

    // Do everything after this line

    ui->imageLabel->setPixmap(QPixmap::fromImage(image1));

    connect(ui->RedButton, &QAbstractButton::clicked,   // Signal
            &model, &Model::addPercentage);          // Slot (custom)

    connect(&model, &Model::updateView,
            ui->RoundProgressBar, &QProgressBar::setValue);
}






// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
