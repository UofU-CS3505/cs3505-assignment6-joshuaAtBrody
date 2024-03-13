
#include "Model.h"



Model::Model(QObject *parent) : QObject(parent){
    currentPlayerIndexInSequence = 0;
    currentComputerIndexInSequence = 0;
    flashDelay = 1000; // Starting delay, will lower as game increases
    waitDelay = 500;
    // Create starter sequence
    sequence.push_back(rand()%2);
}

// Slot
void Model::startGame(){
    // GAME START
    // Disable start button
    emit turnStartButton(false);



    // COMPUTER TURN
    timer.singleShot(500, this, &Model::pauseToComputerTurn);
    // Add a part to the sequence
    // Lower flash delay and respective timing variables (make game faster)
    // Disable buttons
    // For each part in the sequence:
        //signal the view to flash the respective button
    // Enable buttons
    // Goto player turn

    // PLAYER TURN
    // Get player's signals with slots (buttonClicked)
    // Compare player's button with respective part in sequence
        // If incorrect button is pushed, -> signal playerFailed
        // Else correct button, signal update progress, pause, then continue to computer turn

    // PLAYER FAILED
    // Reset sequence
    // Reset timing variables
    // Reset progress
    // Goto GAME START

}


void Model::computerTurn(){
    // COMPUTER TURN
    currentPlayerIndexInSequence = 0;
    currentComputerIndexInSequence = 0;
    // Add a part to the sequence
    sequence.push_back(rand()%2);
    // Lower flash delay and respective timing variables (make game faster)
    flashDelay -= 50;
    waitDelay -= 20;

    // Disable buttons
    emit switchAbilityOfColorButtons(false);

    // For each part in the sequence:
    flashButtonsInSequence(currentComputerIndexInSequence);

}


void Model::flashButtonsInSequence(int indexInSequence){
    if(sequence[indexInSequence] == 0){
        // Do red button
        timer.singleShot(0, this, &Model::flashRedButton);
        timer.singleShot(flashDelay, this, &Model::endFlashRedButton);
    } else {
        // Do blue button
        timer.singleShot(0, this, &Model::flashBlueButton);
        timer.singleShot(flashDelay, this, &Model::endFlashBlueButton);
    }
    timer.singleShot(flashDelay + waitDelay, this, &Model::pauseToFlashNextSequence);
}

//Slot
void Model::pauseToFlashNextSequence(){
    if(currentComputerIndexInSequence < sequence.size() - 1){
        currentComputerIndexInSequence += 1;
        flashButtonsInSequence(currentComputerIndexInSequence);
    } else {
        // Enable buttons
        emit switchAbilityOfColorButtons(true);
    }
}

//Slot
void Model::flashRedButton(){
    emit viewRedFlash(true);
}

//Slot
void Model::flashBlueButton(){
    emit viewBlueFlash(true);
}

//Slot
void Model::endFlashRedButton(){
    emit viewRedFlash(false);
}

//Slot
void Model::endFlashBlueButton(){
    emit viewBlueFlash(false);
}


// Slot
void Model::buttonRedClicked(){

    if(sequence[currentPlayerIndexInSequence] != 0){
        // If player failed
        emit playerFailed(true);
        reset();
        return;
    } else {
        currentPlayerIndexInSequence += 1;
        emit updateProgress((100*currentPlayerIndexInSequence)/sequence.size());

        if(currentPlayerIndexInSequence == sequence.size()){
            currentPlayerIndexInSequence = 0;
            timer.singleShot(700, this, &Model::pauseToLookAt100Percent);
        }
    }
}

// Slot
void Model::buttonBlueClicked(){
    if(sequence[currentPlayerIndexInSequence] != 1){
        // If player failed
        emit playerFailed(true);
        reset();
        return;
    } else {
        currentPlayerIndexInSequence += 1;
        emit updateProgress((100*currentPlayerIndexInSequence)/sequence.size());

        if(currentPlayerIndexInSequence == sequence.size()){
            currentPlayerIndexInSequence = 0;
            timer.singleShot(700, this, &Model::pauseToLookAt100Percent);
        }
    }
}
//Slot
void Model::pauseToLookAt100Percent(){
    emit updateProgress(0);
    timer.singleShot(500, this, &Model::pauseToComputerTurn);
}


//Slot
void Model::pauseToComputerTurn(){
    computerTurn();
}

void Model::reset(){
    emit switchAbilityOfColorButtons(false);
    sequence.clear();
    currentPlayerIndexInSequence = 0;
    flashDelay = 1000;
    waitDelay = 500;
    sequence.push_back(rand()%2);
    timer.singleShot(5000, this, &Model::restartGame);

}

void Model::restartGame(){
    emit playerFailed(false);
    emit updateProgress(0);
    startGame();
}




