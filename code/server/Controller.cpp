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
}

Player &Controller::addPlayer(int id, QByteArray name)
{
    QPoint freePosition = assignFreePosition();


  /*  if(name=="Luki") {
        data.model.players.insert(id, Player(id, assignGroup(), 5, 10, RIGHT, name));
            data.playerActions.insert(id, PlayerAction(false,NONE,id));
    }
    else if(name=="Marko") {
        data.model.players.insert(id, Player(id, assignGroup(), 40, 10, LEFT, name));
            data.playerActions.insert(id, PlayerAction(false,NONE,id));
    }
    else if(name=="Tomcio"){
            data.model.players.insert(id, Player(id, assignGroup(), 40, 20, LEFT, name));
           data.playerActions.insert(id, PlayerAction(false,NONE,id));
    }
    else if(name=="Kamcio"){
            data.model.players.insert(id, Player(id, assignGroup(), 19, 40, LEFT, name));
           data.playerActions.insert(id, PlayerAction(false,NONE,id));
    }
*/
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
/*    QMap<int,PlayerAction>::iterator i=
    data.playerActions.begin();
    while(i!=data.playerActions.end()){
        if(data.model.players[i.key()].name=="Luki"){
            if(testVariable%50==0)
                i.value().moving_direction=NONE;
            else   {
                i.value().player_shooted=true;

            }
            i.value().player_shooted=true;
        testVariable++;
        }
        if(i!=data.playerActions.end() && data.model.players[i.key()].name=="Marko"){
            i.value().moving_direction=NONE;
            i.value().player_shooted=true;
        }
        if(i!=data.playerActions.end() && data.model.players[i.key()].name=="Tomcio"){
            i.value().moving_direction=NONE;
            i.value().player_shooted=true;
        }
        if(i!=data.playerActions.end() && data.model.players[i.key()].name=="Kamcio"){
            i.value().moving_direction=NONE;
            i.value().player_shooted=true;
        }
        i++;
    }
*/
    RefreshPlayerInBoard(data.model.players, playerInBoard);
    refreshShotInBoard(data.model.shots, shotInBoard);
    QMutableMapIterator<int,Player> it(data.model.players);
    while(it.hasNext()){
        it.next();
     //   qDebug()<<"Kierunek :"<<DIRECT(it.value().id)<<"Czy strzelił"<<IS_SHOT(it.value().id);
        if(IS_SHOT(it.value().id)==true){
             QString str;
        }
    }
    it.toFront();
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
        if(IS_SHOT(it.value().id)==true && it.value().is_alive ){
            bool flaga=false;
            for(QMap<int,Shot>::iterator i=oldshots.begin();i!=oldshots.end();i++){
                if(i.value()==Shot(0,it.value().id,it.value().x,it.value().y,it.value().direction,0,it.value().power))   {
                    flaga=true;
                }
            }
            if(flaga!=true) {
                //data.model.shots.append(Shot(it.value().id,it.value().x,it.value().y,it.value().direction,0,it.value().power));
                data.model.shots.insert(Controller::getNewShotID,Shot(Controller::getNewShotID++,it.value().id,it.value().x,it.value().y,it.value().direction,0,it.value().power));
                if(getNewShotID>127)    getNewShotID=0;
            }
        }
    }
    for(QMap<int,Shot>::iterator i=data.model.shots.begin();i!=data.model.shots.end();/*i++*/){
        int flaga=0;
        if((i+1)!=data.model.shots.end()){

            for(QMap<int,Shot>::iterator j=i+1;j!=data.model.shots.end();/*j++*/){
                if(i.value()%=j.value())  {
                    j=data.model.shots.erase(j);
                    flaga++;
                }
                else{
                    j++;
                }
            }
        }
        if(flaga==0){
            i++;
        }
        else{
            i=data.model.shots.erase(i);
        }
    }
    it.toFront();
    for(QMap<int,Shot>::iterator i=data.model.shots.begin();i!=data.model.shots.end();/*i++*/){
        // przesuwamy je !!
        i.value().flight_periods+=SPEEDSHOT;
       // if(!isShotInBoard(QPoint(getActualShotPosition(*i))) || isFieldsWallAndShotConflict(*i)){
       //     i->flight_periods-=1;
       // }
        int howMuchShoted=0;
        while(it.hasNext()){
            it.next();
            //czy zestrzelilisny gracza ; siebie samego zestrzelic nie mozemy
            if(it.value().is_alive && it.value().id!=i.value().player_id && isShotInPlayer(getActualShotPosition(i.value()),QPoint(it.value().x,it.value().y))){
                howMuchShoted++;
                //data.model.players.value(i.value().player_id).points;
                //if((it.value().health-howMuchHurt(i->power))<=0)    {
                if((it.value().health-i->power)<=0)    {
                    it.value().health=0;
                    it.value().is_alive=false;
                    it.value().death_time=0;
                    //czy zestrzeli kogos ze swoich
                    if(data.model.players[i.value().player_id].group==it.value().group){
                        data.model.players[i.value().player_id].points=
                                fetchVariablePointsToRange(data.model.players[i.value().player_id].points - 5);

                    }
                    //jeśli zestrzelil kogos z druzyny przeciwnej
                    else{
                        data.model.players[i.value().player_id].points=
                                fetchVariablePointsToRange(data.model.players[i.value().player_id].points + 2);
                        givePointsTeam(data.model.players,data.model.players[i.value().player_id].group,1);
                    }

                    //data.model.players[i->player_id].power++;
                }
                else{
                    //it.value().health-=howMuchHurt(i->power);
                    it.value().health-=i.value().power;
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

    oldshots=data.model.shots;
    RefreshPlayerInBoard(data.model.players, playerInBoard);
    refreshShotInBoard(data.model.shots, shotInBoard);
    refreshBoardInBoard(boardInBoard);
  //  debugDrawInBoard(playerInBoard,shotInBoard,boardInBoard);
    it.toFront();
    /*while(it.hasNext()){
        it.next();
       // qDebug()<<"Kierunek :"<<it.value().direction<<"Czy strzelił "<<it.value().name;
    }
        qDebug()<<"Kierunek :"<<it.value().direction<<"Czy strzelił "<<it.value().name;
    }*/

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
    //if(data.model.players.empty())    return QPoint(7,40);
    QMutableMapIterator<int,Player> it(data.model.players);
    while(!data.model.players.empty()){
        y=rand() % (BOARD_ROWS);
        x=rand() % (BOARD_COLS);
        while(it.hasNext()){
            it.next();
                    if(!isConflictTwoPlayers(QPoint(it.value().x,it.value().y),QPoint(x,y)) &&
                            !(extendedBoard[y][x].id==BOARD_FIELD_ID(WALL)) &&
                            !(extendedBoard[y][x].id==BOARD_FIELD_ID(THICK_WALL)) &&
                            !(extendedBoard[y][x].id==BOARD_FIELD_ID(WATER))){
                        qDebug()<<"Czy jest konflikt? "<<isConflictTwoPlayers(QPoint(it.value().x,it.value().y),QPoint(x,y))<<"\n";
                        qDebug()<<"Czy jest konflikt wall? "<<isPlayerInFieldWall(QPoint(it.value().x,it.value().y),QPoint(x,y))<<"\n";
                        qDebug()<<"Czy jest konflikt thick? "<<isPlayerInFieldWall(QPoint(it.value().x,it.value().y),QPoint(x,y))<<"\n";
                        qDebug()<<"Czy jest konflikt water? "<<isPlayerInFieldWall(QPoint(it.value().x,it.value().y),QPoint(x,y))<<"\n";
                        return QPoint(5*x+2, 5*y+2);
                    }

        }
        it.toFront();

    }
    while(true){
        y=rand() % (BOARD_ROWS);
        x=rand() % (BOARD_COLS);
        if(!(extendedBoard[y][x].id==BOARD_FIELD_ID(WALL)) &&
                !(extendedBoard[y][x].id==BOARD_FIELD_ID(THICK_WALL)) &&
                !(extendedBoard[y][x].id==BOARD_FIELD_ID(WATER))){
            return QPoint(5*x+2, 5*y+2);
        }
    }
    //return QPoint(5*x+2, 5*y+2);
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
            else    {
                (player.y)--;
                player.direction=DIRECT(player.id);
            }
        }
        else{
            player.direction=DIRECT(player.id);
            DIRECT(player.id)=NONE;
        }
        break;
    case DOWN:
        if(player.direction==DOWN){
            if(player.y==(5*BOARD_ROWS-1-2))    DIRECT(player.id)=NONE;
            else    {
                (player.y)++;
                player.direction=DIRECT(player.id);
            }
        }
        else{
            player.direction=DIRECT(player.id);
            DIRECT(player.id)=NONE;
        }
        break;
    case LEFT:
        if(player.direction==LEFT){
            if(player.x==2)    DIRECT(player.id)=NONE;
            else    {
                (player.x)--;
                player.direction=DIRECT(player.id);
            }
        }
        else{
            player.direction=DIRECT(player.id);
            DIRECT(player.id)=NONE;
        }
        break;
    case RIGHT:
        if(player.direction==RIGHT){
            if(player.x==(5*BOARD_COLS-1-2))    DIRECT(player.id)=NONE;
            else    {
                (player.x)++;
                player.direction=DIRECT(player.id);
            }
        }
        else{
            player.direction=DIRECT(player.id);
            DIRECT(player.id)=NONE;
        }
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
    //qDebug() <<"koniec tablicy";
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
void Controller::refreshShotInBoard(const QMap<int, Shot> &futuredShots, QVector<QVector<char> > &shotInBoard){
    for(int i=0;i<shotInBoard.size();i++){
        for(int j=0;j<shotInBoard.operator[](i).size();j++){
            shotInBoard[i][j]='0';
        }
    }
    int x, y;
    QMapIterator<int, Shot> i(futuredShots);
    while(i.hasNext()){
        i.next();
        y=getActualShotPosition(i.value()).y();
        x=getActualShotPosition(i.value()).x();
        shotInBoard[y][x]='S';
    }
}


void Controller::SolvePlayerConflict(Player & player1,Player & player2){
    if(!player1.is_alive)    return;
    if(!player2.is_alive)    return;
    int odl_x=abs(player1.x-player2.x);
    int odl_y=abs(player1.y-player2.y);
    if(odl_x>4 || odl_y>4){
        return;
    }
   /* if(DIRECT(player1.id)!=NONE){
        backmovePlayer(player1);
    }
    if(DIRECT(player2.id)!=NONE){
        backmovePlayer(player2);
    }*/
    if(DIRECT(player1.id)==NONE){
        if(odl_x>4 || odl_y>4)  return;
        else{
            backmovePlayer(player2);
        }
    }
    else if(DIRECT(player2.id)==NONE){
        if(odl_x>4 || odl_y>4)  return;
        else{
            backmovePlayer(player1);
        }
    }
    else if(DIRECT(player1.id)==LEFT){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player2.id)==RIGHT){
            backmovePlayer(player1);
            backmovePlayer(player2);
        }
        else if(DIRECT(player2.id)==DOWN || DIRECT(player2.id)==UP){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player1);
            }
            else{
                backmovePlayer(player2);
            }
        }
    }
    else if(DIRECT(player2.id)==LEFT){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player1.id)==RIGHT){
            backmovePlayer(player2);
            backmovePlayer(player1);
        }
        else if(DIRECT(player1.id)==DOWN || DIRECT(player1.id)==UP){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player2);
            }
            else{
                backmovePlayer(player1);
            }
        }
    }
    else if(DIRECT(player1.id)==RIGHT){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player2.id)==LEFT){
            backmovePlayer(player1);
            backmovePlayer(player2);
        }
        else if(DIRECT(player2.id)==DOWN || DIRECT(player2.id)==UP){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player1);
            }
            else{
                backmovePlayer(player2);
            }
        }
    }
    else if(DIRECT(player2.id)==RIGHT){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player1.id)==LEFT){
            backmovePlayer(player2);
            backmovePlayer(player1);
        }
        else if(DIRECT(player1.id)==DOWN || DIRECT(player1.id)==UP){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player2);
            }
            else{
                backmovePlayer(player1);
            }
        }
    }
    else if(DIRECT(player1.id)==UP){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player2.id)==DOWN){
            backmovePlayer(player1);
            backmovePlayer(player2);
        }
        else if(DIRECT(player2.id)==LEFT || DIRECT(player2.id)==RIGHT){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player1);
            }
            else{
                backmovePlayer(player2);
            }
        }
    }
    else if(DIRECT(player1.id)==DOWN){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player2.id)==UP){
            backmovePlayer(player1);
            backmovePlayer(player2);
        }
        else if(DIRECT(player2.id)==LEFT || DIRECT(player2.id)==RIGHT){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player1);
            }
            else{
                backmovePlayer(player2);
            }
        }
    }

    else if(DIRECT(player2.id)==UP){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player1.id)==DOWN){
            backmovePlayer(player2);
            backmovePlayer(player1);
        }
        else if(DIRECT(player1.id)==LEFT || DIRECT(player1.id)==RIGHT){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player2);
            }
            else{
                backmovePlayer(player1);
            }
        }
    }
    else if(DIRECT(player2.id)==DOWN){
        if(odl_x>4 || odl_y>4)  return;
        else if(DIRECT(player1.id)==UP){
            backmovePlayer(player2);
            backmovePlayer(player1);
        }
        else if(DIRECT(player1.id)==LEFT || DIRECT(player1.id)==RIGHT){
            //int a = (c>8)?2:-2;
            if(odl_x>=odl_y){
                backmovePlayer(player2);
            }
            else{
                backmovePlayer(player1);
            }
        }
    }



    /*
    if(DIRECT(player1.id)==NONE || DIRECT(player2.id)==NONE){
        if(odl_x<=4 && odl_y<=4 && DIRECT(player1.id)==NONE)   backmovePlayer(player2);
        else if(odl_x<=4 && odl_y<=4 && DIRECT(player2.id)==NONE)  backmovePlayer(player1);

    }
    if(((DIRECT(player1.id)==LEFT && DIRECT(player2.id)==RIGHT) || (DIRECT(player1.id)==RIGHT && DIRECT(player2.id)==LEFT))||((DIRECT(player1.id)==UP && DIRECT(player2.id)==DOWN) || (DIRECT(player1.id)==DOWN && DIRECT(player2.id)==UP))){

        if(((odl_x!=4 && odl_x<=3 && odl_y<=4) ||(odl_y!=4 &&odl_y<=3 && odl_x<=4)) ){
            backmovePlayer(player1);
            backmovePlayer(player2);
        }
        else if(((odl_x==4 && odl_y==4) ||(odl_y==4 && odl_x==4)) ){
            backmovePlayer(player1);
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
    }*/
}

bool Controller::isShotInPlayer(QPoint shot,QPoint player){
    int odl_x=abs(shot.x()-player.x());
    int odl_y=abs(shot.y()-player.y());
    if(odl_x<=2 && odl_y<=2)  return true;
    else return false;
}

QPoint Controller::getActualShotPosition(const Shot & shot) const{
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
    if(odl_x<=4 && odl_y<=4 &&
            (extendedBoard[field.y()][field.x()].id==BOARD_FIELD_ID(WALL)
             ||extendedBoard[field.y()][field.x()].id==BOARD_FIELD_ID(WATER)
             ||extendedBoard[field.y()][field.x()].id==BOARD_FIELD_ID(THICK_WALL)))  return true;
    else return false;
}

bool Controller::isConflictTwoPlayers(QPoint player,QPoint player2){
    int odl_x=abs(player.x()-5*player2.x()-2);
    int odl_y=abs(player.y()-5*player2.y()-2);
    if(odl_x<=4 && odl_y<=4)  return true;
    else return false;
}


bool Controller::isFieldsWallAndShotConflict(Shot & shot){
    int d_x=qFloor((getActualShotPosition(shot).x()-2)/5.);
    int d_y=qFloor((getActualShotPosition(shot).y()-2)/5.);
    for(int i=0;i<2 && d_x+i<BOARD_COLS;i++){
        for(int j=0;j<2 && d_y+j<BOARD_ROWS;j++){
            if(  isShotInFieldWall(QPoint(getActualShotPosition(shot).x(),getActualShotPosition(shot).y()),QPoint(d_x+i,d_y+j))){
                //if((extendedBoard[d_y+j][d_x+i].health-howMuchHurt(shot.power))<=0)    {
                if(extendedBoard[d_y+j][d_x+i].id==BOARD_FIELD_ID(WALL)){
                    if((extendedBoard[d_y+j][d_x+i].health-shot.power)<=0  )    {
                        extendedBoard[d_y+j][d_x+i]=ObstacleBoardElement(1,false,0);
                    }
                    else{
                        extendedBoard[d_y+j][d_x+i].health-=shot.power;
                    }

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
    if(odl_x<=2 && odl_y<=2 && (extendedBoard[field.y()][field.x()].id==BOARD_FIELD_ID(WALL)
                                ||extendedBoard[field.y()][field.x()].id==BOARD_FIELD_ID(THICK_WALL) ))  return true;
    else return false;
}
void Controller::loadExtendedBoard(QVector<QVector<int> > idBoard){
    for(int i=0;i<extendedBoard.size();i++){
        for(int j=0;j<extendedBoard.operator[](i).size();j++){
            extendedBoard[i][j]=ObstacleBoardElement(idBoard[i][j],false,0);
            if(extendedBoard[i][j].id==BOARD_FIELD_ID(WALL)){
                extendedBoard[i][j].isDestructable=true;
                extendedBoard[i][j].health=40;
            }
        }
    }
}

void Controller::clearModelFromDataObject(){
    data.model=Model();
}


//zmienna statyczna;
int Controller::getNewShotID=0;
int Controller::testVariable=0;

void Controller::givePointsTeam(QMap<int, Player> &players, Player::GROUP grupa, int howPoints){
         QMutableMapIterator<int,Player> it(players);
    while(it.hasNext()){
        it.next();
        if(it.value().group==grupa){
            it.value().points=fetchVariablePointsToRange(it.value().points+howPoints);
        }
    }
}
int Controller::fetchVariablePointsToRange(int i){
    if(i<0) return 0;
    else if(i>255)  return 255;
    else    return i;
}

