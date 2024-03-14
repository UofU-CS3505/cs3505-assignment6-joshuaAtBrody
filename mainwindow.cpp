#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QImage>
#include <QDebug>

#include "Model.h"

MainWindow::MainWindow(Model& model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap bkgnd("/pics/RedBlueSimonBackground.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    this->centralWidget()->setStyleSheet("background-image:url(\"RedBlueSimonBackground.png\"); background-position: center;");

    // Do everything after this line

    // Set regular color of the red button to be red + pressed
    ui->RedButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);} QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->BlueButton->setStyleSheet( QString("QPushButton {background-color: rgb(50,50,200);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->loserText->setVisible(false);
    ui->RedButton->setEnabled(false);
    ui->BlueButton->setEnabled(false);

    connect(&model, &Model::updateProgress,
            ui->RoundProgressBar, &QProgressBar::setValue);

    // Start Game button has been clicked! Start the game! (Will disable StartGameButton)
    connect(ui->StartGameButton, &QAbstractButton::clicked,
            &model, &Model::startGame);

    connect(&model, &Model::turnStartButton,
            ui->StartGameButton, &QPushButton::setEnabled);

    connect(ui->RedButton, &QAbstractButton::clicked, &model, &Model::buttonRedClicked);
    connect(ui->BlueButton, &QAbstractButton::clicked, &model, &Model::buttonBlueClicked);


    connect(&model, &Model::switchAbilityOfColorButtons, ui->RedButton, &QPushButton::setEnabled);
    connect(&model, &Model::switchAbilityOfColorButtons, ui->BlueButton, &QPushButton::setEnabled);

    connect(&model, &Model::viewRedFlash, this, &MainWindow::flashRedButton);
    connect(&model, &Model::viewBlueFlash, this, &MainWindow::flashBlueButton);

    connect(&model, &Model::playerFailed, ui->loserText, &QLabel::setVisible);



}

void MainWindow::flashRedButton(bool flashing){
    if(flashing){
        ui->RedButton->setStyleSheet("background-color: rgb(255, 0, 0);");
    } else {
        ui->RedButton->setStyleSheet("background-color: rgb(200,50,50);");
    }
}

void MainWindow::flashBlueButton(bool flashing){
    if(flashing){
        ui->BlueButton->setStyleSheet("background-color: rgb(0, 0, 255);");
    } else {
        ui->BlueButton->setStyleSheet("background-color: rgb(50, 50, 200);");
    }
}





// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
