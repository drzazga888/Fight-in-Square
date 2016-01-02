#include "Controller.h"
#include <QDebug>
#include <QVector>
#include "config.h"
#include "../shared/Model/Player.h"


Controller::Controller(Data &data)
    :data(data)
{
    extendedBoard.resize(BOARD_ROWS);
    for (int i = 0; i < BOARD_ROWS; ++i){
        extendedBoard.operator[](i).resize(BOARD_COLS);
    }
    for(int i=0;i<extendedBoard.size();i++){
        for(int j=0;j<extendedBoard.operator[](i).size();j++){
            extendedBoard[i][j]=ObstacleBoardElement();
        }
    }


    QString fileName = QFileDialog::getOpenFileName(0,"Wczytaj mapę","../server/mapa1.map","Pliki map (*.map)");
    if(!fileName.isEmpty()){
        qDebug()<<"Plik otwarty";
        QFile file(fileName);
        if(file.open(QFile::ReadOnly | QFile::Text)){
            QTextStream in(&file);
            int i=0;
            int j=0;
            while(/*!linia.isEmpty() &&*/ i<10){
                QString linia=in.readLine();
  //              qDebug()<<"linia nr"<<linia;
                QString::iterator itc=linia.begin();
                j=0;
                for(QString::iterator itc=linia.begin();itc!=linia.end() && j<14;itc=itc+1){
                    if(!itc->isSpace()){
                        extendedBoard[i][j]=ObstacleBoardElement(itc->digitValue(),false,0);
                        if(extendedBoard[i][j].id==BOARD_FIELD_ID(WALL)){
                            extendedBoard[i][j].isDestructable=true;
                            extendedBoard[i][j].health=40;
                        }
      //                  qDebug()<<"j "<<j;
                        j++;
                    }
                }

                i++;
            }

        }
    }
    else{
        for(int i=0;i<extendedBoard.size();i++){
            for(int j=0;j<extendedBoard.operator[](i).size();j++){
                extendedBoard[i][j]=ObstacleBoardElement(0,false,0);
            }
        }
        extendedBoard[8][2]=ObstacleBoardElement(5,true,40);
    }

    playerInBoard.resize(5*BOARD_ROWS);
    for (int i = 0; i < 5*BOARD_ROWS; ++i){
        playerInBoard.operator[](i).resize(5*BOARD_COLS);
    }
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            playerInBoard[i][j]='0';
        }
    }

    shotInBoard.resize(5*BOARD_ROWS);
    for (int i = 0; i < 5*BOARD_ROWS; ++i){
        shotInBoard.operator[](i).resize(5*BOARD_COLS);
    }
    for(int i=0;i<shotInBoard.size();i++){
        for(int j=0;j<shotInBoard.operator[](i).size();j++){
            shotInBoard[i][j]=0;
        }
    }

    boardInBoard.resize(5*BOARD_ROWS);
    for (int i = 0; i < 5*BOARD_ROWS; ++i){
        boardInBoard.operator[](i).resize(5*BOARD_COLS);
    }
    for(int i=0;i<boardInBoard.size();i++){
        for(int j=0;j<boardInBoard.operator[](i).size();j++){
            boardInBoard[i][j]=0;
        }
    }
    for(int i=0;i<extendedBoard.size();i++){
        for(int j=0;j<extendedBoard.operator[](i).size();j++){
            data.model.board[i][j]=extendedBoard[i][j];
        }
    }
    // przyklad testowy
    // Swoja droga - ladowanie mapy NIE MOZE ODBYWAC SIE W KONTROLERZE!!!
    // Musi byc oddzielna klasa wywolywania, gdy serwer zacznie dzialac!
    // Obiekt tej nowej klasy MUSI sie znalezc jako pole w w obiekcie server.
    //data.model.board[1][2] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), true, 40);
   // data.model.board[7][9] = ObstacleBoardElement(BOARD_FIELD_ID(WALL), false, 0);
}

Player &Controller::addPlayer(int id, QByteArray name)
{
    QPoint freePosition = assignFreePosition();
    data.model.players.insert(id, Player(id, assignGroup(), freePosition.x(), freePosition.y(), assignDirection(), name));
    data.playerActions.insert(id, PlayerAction(id));
    return data.model.players[id];
}

void Controller::removePlayer(int id)
{
    data.model.players.remove(id);
    data.playerActions.remove(id);
}

void Controller::nextModelStatus()
{
    RefreshPlayerInBoard(data.model.players, playerInBoard);
    refreshShotInBoard(data.model.shots, shotInBoard);
    QMutableMapIterator<int,Player> it(data.model.players);
    while(it.hasNext()){
        it.next();
        movePlayer(it.value());
    }
    it.toFront();
    while(it.hasNext()){
        it.next();
        SolveFieldsWallAndPlayerConflict(it.value());
        if(!it.hasNext())   break;
        QMutableMapIterator<int,Player> it2(data.model.players);
        while(it2.hasNext()){
            it2.next();
            SolvePlayerConflict(it.value(),it2.value());
        }
    }
    it.toFront();
    //teraz pociski !!!
    it.toFront();
    while(it.hasNext()){
        it.next();
        if(IS_SHOT(it.value().id)==true && it.value().is_alive){
            data.model.shots.append(Shot(it.value().id,it.value().x,it.value().y,it.value().direction,0,it.value().power));
        }
    }
    it.toFront();
    for(QVector<Shot>::iterator i=data.model.shots.begin();i!=data.model.shots.end();/*i++*/){
        // przesuwamy je !!
        i->flight_periods++;
        int howMuchShoted=0;
        while(it.hasNext()){
            it.next();
            //czy zestrzelilisny gracza ; siebie samego zestrzelic nie mozemy
            if(it.value().is_alive && it.value().id!=i->player_id && isShotInPlayer(getActualShotPosition(*i),QPoint(it.value().x,it.value().y))){
                howMuchShoted++;
                data.model.players.value(i->player_id).points;
                if((it.value().health-howMuchHurt(i->power))<=0)    {
                    it.value().health=0;
                    it.value().is_alive=false;
                    it.value().death_time=0;
                    data.model.players[i->player_id].points++;
                    data.model.players[i->player_id].power++;
                }
                else{
                    it.value().health-=howMuchHurt(i->power);
                }
            }
        }
        it.toFront();
        if(howMuchShoted>0){
            i=data.model.shots.erase(i);
        }
        //wyszedł za plansze?
        else if(!isShotInBoard(QPoint(getActualShotPosition(*i)))){
            i=data.model.shots.erase(i);
        }
        else if(isFieldsWallAndShotConflict(*i)){
            i=data.model.shots.erase(i);
        }
        else{
            i++;
        }
    }
    //teraz zajmujemy się trupami
    it.toFront();
    while(it.hasNext()){
        it.next();
        if(it.value().is_alive==false){
            if(it.value().death_time<REGENERATION_TIME){
                it.value().death_time++;
            }
            else{
                QPoint freePosition = assignFreePosition();
                it.value().is_alive=true;
                it.value().death_time=0;
                it.value().health=MAX_HEALTH;
                it.value().direction=assignDirection();
                it.value().x=freePosition.x();
                it.value().y=freePosition.y();
             }
        }
    }
    //"zerujemy"
    it.toFront();
    while(it.hasNext()){
        it.next();
        DIRECT(it.value().id)=NONE;
        IS_SHOT(it.value().id)=false;
    }
    //przenosimy extendBoard do wysyłki
    for(int i=0;i<extendedBoard.size();i++){
        for(int j=0;j<extendedBoard.operator[](i).size();j++){
            data.model.board[i][j]=extendedBoard[i][j];
        }
    }


    RefreshPlayerInBoard(data.model.players, playerInBoard);
    refreshShotInBoard(data.model.shots, shotInBoard);
    refreshBoardInBoard(boardInBoard);
    debugDrawInBoard(playerInBoard,shotInBoard,boardInBoard);
}

Player::GROUP Controller::assignGroup()
{
    int reds = 0, blues = 0;
    QMapIterator<int, Player> i(data.model.players);
    while (i.hasNext())
    {
        i.next();
        switch (i.value().group)
        {
        case Player::RED_GROUP:
            ++reds;
            break;
        case Player::BLUE_GROUP:
            ++blues;
            break;
        }
    }
    if (reds < blues)
        return Player::RED_GROUP;
    else if (reds > blues)
        return Player::BLUE_GROUP;
    else
        return (Player::GROUP)(rand() % 2);
}

DIRECTION Controller::assignDirection()
{
    return (DIRECTION)(rand() % 4 + 1);
}

QPoint Controller::assignFreePosition(){
    int x=0;int y=0;
    do{
    y=rand() % (BOARD_ROWS);
    x=rand() % (BOARD_COLS);
    QMutableMapIterator<int,Player> it(data.model.players);
    while(it.hasNext() && data.model.players.size()>0){
        it.next();
                if(!isPlayerInFieldWall(QPoint(it.value().x,it.value().y),QPoint(y,x)) && extendedBoard[y][x].isDestructable==false){
                    return QPoint(5*x+2, 5*y+2);
                }
    }

    }while(data.model.players.size()>0 && extendedBoard[y][x].isDestructable==true);
    return QPoint(5*x+2, 5*y+2);
    //return QPoint(2,45);
}

void Controller::movePlayer(Player & player){
    if(!player.is_alive)    return;
    //if(player.direction!=DIRECT(player.id)) player.direction=DIRECT(player.id); //nawet, jeśli nie uda się przesunąc, to kierunek czołgu zmieniamy!
    /*else*/// if(DIRECT(player.id)!=NONE)    player.direction=DIRECT(player.id);
    switch(DIRECT(player.id)){
    case UP:
        if(player.direction==UP){
            if(player.y==2)    DIRECT(player.id)=NONE;
            else    (player.y)--;
        }
        player.direction=DIRECT(player.id);
        break;
    case DOWN:
        if(player.direction==DOWN){
            if(player.y==(5*BOARD_ROWS-1-2))    DIRECT(player.id)=NONE;
            else    (player.y)++;
        }
        player.direction=DIRECT(player.id);
        break;
    case LEFT:
        if(player.direction==LEFT){
            if(player.x==2)    DIRECT(player.id)=NONE;
            else    (player.x)--;
        }
        player.direction=DIRECT(player.id);
        break;
    case RIGHT:
        if(player.direction==RIGHT){
            if(player.x==(5*BOARD_COLS-1-2))    DIRECT(player.id)=NONE;
            else    (player.x)++;
        }
        player.direction=DIRECT(player.id);
        break;
    }
}
void Controller::backmovePlayer(Player & player){
    if(!player.is_alive)    return;
    switch(DIRECT(player.id)){
    case UP:
                (player.y)++;
        DIRECT(player.id)=NONE;
        break;
    case DOWN:
                (player.y)--;
        DIRECT(player.id)=NONE;
        break;
    case LEFT:
                (player.x)++;
        DIRECT(player.id)=NONE;
        break;
    case RIGHT:
                (player.x)--;
        DIRECT(player.id)=NONE;
        break;
    }
}

void Controller::debugDrawInBoard(QVector<QVector<char> > & playerInBoard, QVector<QVector<char> >& shotInBoard,QVector<QVector<int> > boardInBoard){
    QString output="";
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            if(shotInBoard[i][j]=='0' && playerInBoard[i][j]=='P') output+="P ";
            else if(shotInBoard[i][j]=='0' && playerInBoard[i][j]=='W')   output+="W ";
            else if(shotInBoard[i][j]=='S'){
                QString str(shotInBoard[i][j]);
                output=output+str+' ';
            }
            else{
                output=output+QString::number(boardInBoard[i][j])+' ';
            }
        }
        qDebug() <<output;
        //qDebug() <<"--------"<<i<<"-------";
        output="";
    }
    //qDebug() << output;
    qDebug() <<"koniec tablicy";
}
void Controller::refreshBoardInBoard(QVector<QVector<int> > & boardInBoard){
    for(int i=0;i<boardInBoard.size();i++){
        for(int j=0;j<boardInBoard.operator[](i).size();j++){
            boardInBoard[i][j]=0;
        }
    }
    for(int i=0;i<extendedBoard.size();i++){
        for(int j=0;j<extendedBoard[i].size();j++){
            int gi=5*i+2;
            int gj=5*j+2;
            for(int gii=gi-2;gii<=gi+2;gii++) {

                for(int gjj=gj-2;gjj<=gj+2;gjj++){
                    boardInBoard[gii][gjj]=extendedBoard[i][j].id;
                }
            }
        }
    }
}

void Controller::RefreshPlayerInBoard(QMap<int, Player> futuredPlayers,QVector<QVector<char> > & playerInBoard){
    for(int i=0;i<playerInBoard.size();i++){
        for(int j=0;j<playerInBoard.operator[](i).size();j++){
            playerInBoard[i][j]='0';
        }
    }
    QMutableMapIterator<int,Player> it(futuredPlayers);
    while(it.hasNext()){
        it.next();
        if(it.value().is_alive){
            for(int i=it.value().y-2;i<=it.value().y+2;i++) {

                for(int j=it.value().x-2;j<=it.value().x+2;j++){
                    playerInBoard[i][j]='P';
                }
            }
            playerInBoard[it.value().y][it.value().x]='W';
        }
    }
}
void Controller::refreshShotInBoard(QVector<Shot> futuredShots, QVector<QVector<char> > &shotInBoard){
    for(int i=0;i<shotInBoard.size();i++){
        for(int j=0;j<shotInBoard.operator[](i).size();j++){
            shotInBoard[i][j]='0';
        }
    }
    for(int i=0;i<futuredShots.size();i++){
        shotInBoard[getActualShotPosition(futuredShots[i]).y()][getActualShotPosition(futuredShots[i]).x()]='S';
    }
}


void Controller::SolvePlayerConflict(Player & player1,Player & player2){
    if(!player1.is_alive)    return;
    if(!player2.is_alive)    return;
    int odl_x=abs(player1.x-player2.x);
    int odl_y=abs(player1.y-player2.y);
    if(DIRECT(player1.id)==NONE || DIRECT(player2.id)==NONE){
        if(odl_x<=4 && odl_y<=4 && DIRECT(player1.id)==NONE)   backmovePlayer(player2);
        else if(odl_x<=4 && odl_y<=4 && DIRECT(player2.id)==NONE)  backmovePlayer(player1);

    }
    if(((DIRECT(player1.id)==LEFT && DIRECT(player2.id)==RIGHT) || (DIRECT(player1.id)==RIGHT && DIRECT(player2.id)==LEFT))||((DIRECT(player1.id)==UP && DIRECT(player2.id)==DOWN) || (DIRECT(player1.id)==DOWN && DIRECT(player2.id)==UP))){
        if(((odl_x==4 && odl_y==4) ||(odl_y==4 && odl_x==4)) ){
            backmovePlayer(player1);
        }
        else if(((odl_x==3 && odl_y<=4) ||(odl_y==3 && odl_x<=4)) ){
            backmovePlayer(player1);
            backmovePlayer(player2);
        }
    }
    else if(odl_x==4 && odl_y==4){
        backmovePlayer(player1);
    }
    else if(odl_x<=3 && odl_y==4){
        if(DIRECT(player1.id)==UP || DIRECT(player1.id)==DOWN){
            backmovePlayer(player1);
        }
        else{
            backmovePlayer(player2);
        }
    }
    else if(odl_y<=3 && odl_x==4){
        if(DIRECT(player1.id)==LEFT || DIRECT(player1.id)==RIGHT){
            backmovePlayer(player1);
        }
        else{
            backmovePlayer(player2);
        }
    }
    else if(odl_y==3 && odl_x==3){
        backmovePlayer(player1);
        backmovePlayer(player2);
    }
}

bool Controller::isShotInPlayer(QPoint shot,QPoint player){
    int odl_x=abs(shot.x()-player.x());
    int odl_y=abs(shot.y()-player.y());
    if(odl_x<=2 && odl_y<=2)  return true;
    else return false;
}

QPoint Controller::getActualShotPosition(const Shot & shot){
    switch(shot.direction){
    case UP:
        return QPoint(shot.x_start,shot.y_start-shot.flight_periods);
        break;
    case DOWN:
        return QPoint(shot.x_start,shot.y_start+shot.flight_periods);
        break;
    case LEFT:
        return QPoint(shot.x_start-shot.flight_periods,shot.y_start);
        break;
    case RIGHT:
        return QPoint(shot.x_start+shot.flight_periods,shot.y_start);
        break;
    default:
        return QPoint(-1,-1);
    }
}

bool Controller::isShotInBoard(const QPoint &shot){
    if(shot.x()>=0 && shot.x()<=(5*BOARD_COLS-1) && shot.y()>=0 && shot.y()<=(5*BOARD_ROWS-1))  return true;
    else return false;
}

int Controller::howMuchHurt(int power){
    if(power>100)   return 10;
    else if(power<0)    return 1;
    int hurt=(power-1)/10 +1;
    return hurt;
}

void Controller::SolveFieldsWallAndPlayerConflict(Player & player){
    int d_x=qFloor((player.x-2)/5.);
    int d_y=qFloor((player.y-2)/5.);
    for(int i=0;i<2 && d_x+i<BOARD_COLS;i++){
        for(int j=0;j<2 && d_y+j<BOARD_ROWS;j++){
            if(isPlayerInFieldWall(QPoint(player.x,player.y),QPoint(d_x+i,d_y+j))){
                backmovePlayer(player);
                return;
            }
        }
    }
}

bool Controller::isPlayerInFieldWall(QPoint player,QPoint field){
    int odl_x=abs(player.x()-5*field.x()-2);
    int odl_y=abs(player.y()-5*field.y()-2);
    if(odl_x<=4 && odl_y<=4 && extendedBoard[field.y()][field.x()].isDestructable==true)  return true;
    else return false;
}

bool Controller::isFieldsWallAndShotConflict(Shot & shot){
    int d_x=qFloor((getActualShotPosition(shot).x()-2)/5.);
    int d_y=qFloor((getActualShotPosition(shot).y()-2)/5.);
    for(int i=0;i<2 && d_x+i<BOARD_COLS;i++){
        for(int j=0;j<2 && d_y+j<BOARD_ROWS;j++){
            if(isShotInFieldWall(QPoint(getActualShotPosition(shot).x(),getActualShotPosition(shot).y()),QPoint(d_x+i,d_y+j))){
                if((extendedBoard[d_y+j][d_x+i].health-howMuchHurt(shot.power))<=0)    {
                    extendedBoard[d_y+j][d_x+i]=ObstacleBoardElement(1,false,0);
                }
                else{
                    extendedBoard[d_y+j][d_x+i].health--;
                }
                return true;
            }
        }
    }
    return false;
}

bool Controller::isShotInFieldWall(QPoint shot,QPoint field){
    int odl_x=abs(shot.x()-5*field.x()-2);
    int odl_y=abs(shot.y()-5*field.y()-2);
    if(odl_x<=2 && odl_y<=2 && extendedBoard[field.y()][field.x()].isDestructable==true)  return true;
    else return false;
}
