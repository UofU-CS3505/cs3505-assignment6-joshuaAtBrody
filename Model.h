#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <random>

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

public slots:
    ///
    /// \brief startGame    when the start button is clicked, start the game.
    ///
    void startGame();

    ///
    /// \brief buttonRedClicked    When button is clicked, compare with sequence if player hit correct button in order.
    ///
    void buttonRedClicked();

    void buttonBlueClicked();

    void flashRedButton();
    void flashBlueButton();

    void endFlashRedButton();
    void endFlashBlueButton();

    void pauseToLookAt100Percent();
    void pauseToComputerTurn();
    void pauseToFlashNextSequence();

    void restartGame();


signals:
    ///
    /// \brief flashButton  flash the given button in the view.
    /// \param button   which button to flash
    ///
    void flashButton(int button);

    ///
    /// \brief playerFailed game end view, reset sequence and variables.
    ///
    void playerFailed(bool failed);

    ///
    /// \brief updateProgress   calculate the progress the player has made and display it in view.
    /// \param progress the new progress value
    ///
    void updateProgress(double progress);

    ///
    /// \brief turnStartButton  disable start button once start button has been clicked
    /// \param abled    enable/disable true/false
    ///
    void turnStartButton(bool abled);



    ///
    /// \brief switchAblityOfColorButtons   turn off or on the buttons when it is the computers turn teehee
    /// \param abled    enable/disable true/false
    ///
    void switchAbilityOfColorButtons(bool abled);

    void viewRedFlash(bool flashing);
    void viewBlueFlash(bool flashing);


private:
    std::vector<int> sequence;
    QTimer timer;
    int currentPlayerIndexInSequence;
    int currentComputerIndexInSequence;
    int flashDelay;
    int waitDelay;

    void computerTurn();
    void reset();

    void flashButtonsInSequence(int index);


};


#endif // MODEL_H
