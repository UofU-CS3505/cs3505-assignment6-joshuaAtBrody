
#include "Model.h"



Model::Model(QObject *parent) : QObject(parent){
    currentIndex = 0;
    delay = 1000; // Starting delay, will lower as game increases
    progress = 0;
}




void Model::addPercentage(){
    progress += 1;
    emit updateView(progress);
}
