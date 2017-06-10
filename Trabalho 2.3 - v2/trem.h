#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include "semaforo.h"

using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int, int);
    ~Trem();
    void start();
    void run();
    int entrandoEmRC();
    bool saindoDeRc(int);
    void setVelocidade(int);
    void setEnable(bool);

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
   //vector<Semaforo*> semVector;
   Semaforo *sem1;
   Semaforo *sem2;
   Semaforo *sem3;
   Semaforo *sem4;
   Semaforo *sem5;
   Semaforo *sem6;
   Semaforo *sem7;
   Semaforo *sem8;
   Semaforo *sem9;
   Semaforo *sem10;
};

#endif // TREM_H



