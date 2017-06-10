#include "trem.h"
#include "semaforo.cpp"


Trem::Trem(int id, int x, int y, int vel)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = vel;
    enable = true;
    //Semaforo *test;
    /*for (int i = 0; i < 10; i++){
        test = new Semaforo(1234 + i, 1, IPC_CREAT|0600);
        semVector.push_back(test);
    }*/
    sem1  = new Semaforo(1234, 1, IPC_CREAT|0600);
    sem2  = new Semaforo(1235, 1, IPC_CREAT|0600);
    sem3  = new Semaforo(1236, 1, IPC_CREAT|0600);
    sem4  = new Semaforo(1237, 1, IPC_CREAT|0600);
    sem5  = new Semaforo(1238, 1, IPC_CREAT|0600);
    sem6  = new Semaforo(1239, 1, IPC_CREAT|0600);
    sem7  = new Semaforo(1240, 1, IPC_CREAT|0600);
    sem8  = new Semaforo(1241, 1, IPC_CREAT|0600);
    sem9  = new Semaforo(1242, 1, IPC_CREAT|0600);
    sem10 = new Semaforo(1243, 1, IPC_CREAT|0600);
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

bool Trem::saindoDeRc(int sem){
    switch(id){
        case 1:
            if(sem == 1){
                if( x == 120 && y == 140){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if (sem == 8){
                if( x == 90 && y == 310){
                    return false;
                }
                else{
                    return true;
                }
            }
        case 2:
            if(sem == 1){
                if( x == 150 && y == 10){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if (sem == 2){
                if( x == 230 && y == 110){
                    return false;
                }
                else{
                    return true;
                }
            }
        case 3:
            if(sem == 2){
                if( x == 290 && y == 10){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if (sem == 3){
                if( x == 370 && y == 110){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(sem == 5){
                if (x == 260 && y == 80){
                    return false;
                }
                else{
                    return true;
                }
            }
        case 4:
            if(sem == 3){
                if( x == 430 && y == 10){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if (sem == 10){
                if( x == 400 && y == 180){
                    return false;
                }
                else{
                    return true;
                }
            }
        case 5:
            if(sem == 7){
                if( x == 360 && y == 210){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if (sem == 9){
                if( x == 290 && y == 210){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(sem == 10){
                if (x == 370 && y == 310){
                    return false;
                }
                else{
                    return true;
                }
            }
        case 6:
            if(sem == 6){
                if( x == 260 && y == 210){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if (sem == 8){
                if( x == 150 && y == 210){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(sem == 9){
                if (x == 230 && y == 310){
                    return false;
                }
                else{
                    return true;
                }
            }
        case 7:
            if(sem == 4){
                if( x == 290 && y == 110){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if (sem == 5){
                if( x == 330 && y == 140){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(sem == 6){
                if (x == 190 && y == 180){
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(sem == 7){
                if (x == 230 && y == 210){
                    return false;
                }
                else{
                    return true;
                }
            }
    }
}


int Trem::entrandoEmRC(){
    switch(id){
         case 1:
            if (x == 90 && y == 10){
                return 1;
            }
            else if( x == 120 && y == 180 ){
                return 8;
            }
            break;
        case 2:
             if ( x == 150 && y == 110){
                return 1;
            }
            else if( x == 230 && y == 10 ){
                return 2;
            }
            break;
        case 3:
             if (x == 290 && y == 110){
                return 2;
            }
            else if( x == 370 && y == 10 ){
                return 3;
            }
            else if( x == 360 && y == 110 ){
                return 5;
            }
            break;
        case 4:
            if (x == 400 && y == 140){
                return 3;
            }
            else if( x == 430 && y == 310 ){
                return 10;
            }
            break;
        case 5:
            if (x == 260 && y == 240){
                return 7;
            }
            else if( x == 290 && y == 310 ){
                return 9;
            }
            else if( x == 370 && y == 210 ){
                return 10;
            }
            break;
        case 6:
            if (x == 160 && y == 210){
                return 6;
            }
            else if( x == 150 && y == 310 ){
                return 8;
            }
            else if( x == 230 && y == 210 ){
                return 9;
            }
            break;
        case 7:
            if (x == 190 && y == 140){
                return 4;
            }
            else if( x == 230 && y == 110 ){
                return 5;
            }
            else if( x == 290 && y == 210 ){
                return 6;
            }
            else if( x == 330 && y == 180){
                return 7;
            }
            break;
        default:
            break;
    }
    return 0;

}


void Trem::run()
{
    int z;
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                emit updateGUI(id,x,y);
                z = this->entrandoEmRC();
                if( z == 1){
                    sem1->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 120)
                            x+=10;
                        else if (x == 120 && y < 310)
                            y+=10;
                        else if (x > 10 && y == 310)
                            x-=10;
                        else
                            y-=10;
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem1->V();
                    break;
                }
                else if( z == 8){
                    sem8->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 120){
                            x+=10;
                        }
                        else if (x == 120 && y < 310){
                            y+=10;
                        }
                        else if (x > 10 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem8->V();
                    break;
                }
                if (y == 10 && x < 120)
                    x+=10;
                else if (x == 120 && y < 310)
                    y+=10;
                else if (x > 10 && y == 310)
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 2:
            if (enable)
            {
                emit updateGUI(id, x, y);
                z = this->entrandoEmRC();
                if( z == 1 ){
                    sem1->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 260){
                            x+=10;
                        }
                        else if (x == 260 && y < 110){
                            y+=10;
                        }
                        else if(x > 120 && y == 110){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem1->V();
                    break;
                }
                else if (z == 2){
                    sem2->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 260){
                            x+=10;
                        }
                        else if (x == 260 && y < 110){
                            y+=10;
                        }
                        else if(x > 120 && y == 110){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem2->V();
                    break;
                }
                if (y == 10 && x < 260){
                    x+=10;
                }
                else if (x == 260 && y < 110){
                    y+=10;
                }
                else if(x > 120 && y == 110){
                    x-=10;
                }
                else{
                    y-=10;
                }
            }
            break;
        case 3:
            if (enable)
            {
                emit updateGUI(id, x, y);
                z = this->entrandoEmRC();
                if (z == 2){
                    sem2->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 400){
                            x+=10;
                        }
                        else if (x == 400 && y < 110){
                            y+=10;
                        }
                        else if(x > 260 && y == 110){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem2->V();
                    break;
                }
                else if(z == 3){
                    sem3->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 400){
                            x+=10;
                        }
                        else if (x == 400 && y < 110){
                            y+=10;
                        }
                        else if(x > 260 && y == 110){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem3->V();
                    break;
                }
                else if(z == 5){
                    sem5->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 400){
                            x+=10;
                        }
                        else if (x == 400 && y < 110){
                            y+=10;
                        }
                        else if(x > 260 && y == 110){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem5->V();
                    break;
                }
                if (y == 10 && x < 400){
                    x+=10;
                }
                else if (x == 400 && y < 110){
                    y+=10;
                }
                else if(x > 260 && y == 110){
                    x-=10;
                }
                else{
                    y-=10;
                }
            }
            break;
        case 4:
            if (enable)
            {
                emit updateGUI(id, x, y);
                z = this->entrandoEmRC();
                if (z == 3){
                    sem3->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 510){
                            x+=10;
                        }
                        else if (x == 510 && y < 310){
                            y+=10;
                        }
                        else if(x > 400 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem3->V();
                    break;
                }
                else if (z == 10){
                    sem10->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 10 && x < 510){
                            x+=10;
                        }
                        else if (x == 510 && y < 310){
                            y+=10;
                        }
                        else if(x > 400 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem10->V();
                    break;
                }
                if (y == 10 && x < 510){
                    x+=10;
                }
                else if (x == 510 && y < 310){
                    y+=10;
                }
                else if(x > 400 && y == 310){
                    x-=10;
                }
                else{
                    y-=10;
                }
            }
            break;
        case 5:
            if (enable)
            {
                emit updateGUI(id, x, y);
                z = this->entrandoEmRC();
                if (z == 7){
                    sem7->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 210 && x < 400){
                            x+=10;
                        }
                        else if (x == 400 && y < 310){
                            y+=10;
                        }
                        else if(x > 260 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem7->V();
                    break;
                }
                else if (z == 9){
                    sem9->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 210 && x < 400){
                            x+=10;
                        }
                        else if (x == 400 && y < 310){
                            y+=10;
                        }
                        else if(x > 260 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem9->V();
                    break;
                }
                else if (z == 10){
                    sem10->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 210 && x < 400){
                            x+=10;
                        }
                        else if (x == 400 && y < 310){
                            y+=10;
                        }
                        else if(x > 260 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem10->V();
                    break;
                }
                if (y == 210 && x < 400){
                    x+=10;
                }
                else if (x == 400 && y < 310){
                    y+=10;
                }
                else if(x > 260 && y == 310){
                    x-=10;
                }
                else{
                    y-=10;
                }
            }
            break;
        case 6:
            if (enable)
            {
                emit updateGUI(id, x, y);
                z = this->entrandoEmRC();
                if( z == 6){
                    sem6->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 210 && x < 260){
                            x+=10;
                        }
                        else if (x == 260 && y < 310){
                            y+=10;
                        }
                        else if(x > 120 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem6->V();
                    break;

                }
                else if( z == 9){
                    sem9->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 210 && x < 260){
                            x+=10;
                        }
                        else if (x == 260 && y < 310){
                            y+=10;
                        }
                        else if(x > 120 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem9->V();
                    break;

                }
                else if( z == 8){
                    sem8->P();
                    while(this->saindoDeRc(z)){
                        emit updateGUI(id, x, y);
                        if (y == 210 && x < 260){
                            x+=10;
                        }
                        else if (x == 260 && y < 310){
                            y+=10;
                        }
                        else if(x > 120 && y == 310){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem8->V();
                    break;

                }
                if (y == 210 && x < 260){
                    x+=10;
                }
                else if (x == 260 && y < 310){
                    y+=10;
                }
                else if(x > 120 && y == 310){
                    x-=10;
                }
                else{
                    y-=10;
                }
            }
            break;
        case 7:
            if (enable)
            {
                emit updateGUI(id, x, y);
                z = this->entrandoEmRC();
                if( z == 7){
                    sem7->P();
                    sem6->P();
                    printf("2:%d\n", z);
                    while(this->saindoDeRc(6)){
                        emit updateGUI(id, x, y);
                        if (y == 110 && x < 330){
                            x+=10;
                        }
                        else if (x == 330 && y < 210){
                            y+=10;
                        }
                        else if(x > 190 && y == 210){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem7->V();
                    sem6->V();
                    break;

                }
                if( z == 4){
                    sem4->P();
                    sem5->P();
                    while(this->saindoDeRc(5)){
                        emit updateGUI(id, x, y);
                        if (y == 110 && x < 330){
                            x+=10;
                        }
                        else if (x == 330 && y < 210){
                            y+=10;
                        }
                        else if(x > 190 && y == 210){
                            x-=10;
                        }
                        else{
                            y-=10;
                        }
                        this_thread::sleep_for(chrono::milliseconds(velocidade));
                    }
                    sem4->V();
                    sem5->V();
                    break;

                }
                if (y == 110 && x < 330){
                    x+=10;
                }
                else if (x == 330 && y < 210){
                    y+=10;
                }
                else if(x > 190 && y == 210){
                    x-=10;
                }
                else{
                    y-=10;
                }
                //z->V();
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

