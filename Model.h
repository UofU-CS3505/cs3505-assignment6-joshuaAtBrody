#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QTimer>

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void addPercentage();

signals:
    void playerFailed();
    void updateView(int progress);

private:
    QVector<int> sequence;
    QTimer timer;
    int currentIndex;
    int delay;
    int progress;
};


#endif // MODEL_H
