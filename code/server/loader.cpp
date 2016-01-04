#include "loader.h"
#include"config.h"
Loader::Loader():filePathName(QString())
{
    idBoard.resize(BOARD_ROWS);
    for (int i = 0; i < BOARD_ROWS; ++i){
        idBoard.operator[](i).resize(BOARD_COLS);
    }
    for(int i=0;i<idBoard.size();i++){
        for(int j=0;j<idBoard.operator[](i).size();j++){
            idBoard[i][j]=0;
        }
    }
}

Loader::Loader(QString fileName){
    if(QFileInfo(fileName).completeSuffix()=="map" && QFileInfo(fileName).exists()){
        filePathName=fileName;
    }
    else{
        filePathName=QString();
    }

    idBoard.resize(BOARD_ROWS);
    for (int i = 0; i < BOARD_ROWS; ++i){
        idBoard.operator[](i).resize(BOARD_COLS);
    }
    for(int i=0;i<idBoard.size();i++){
        for(int j=0;j<idBoard.operator[](i).size();j++){
            idBoard[i][j]=0;
        }
    }
}

bool Loader::loadIDMapFromFile(){
    /*for(int i=0;i<idBoard.size();i++){
        for(int j=0;j<idBoard.operator[](i).size();j++){
            idBoard[i][j]=0;
        }
    }*/
    if(!filePathName.isEmpty()){
        qDebug()<<"Plik otwarty";
        QFile file(filePathName);
        if(file.open(QFile::ReadOnly | QFile::Text)){
            QTextStream in(&file);
            int i=0;
            int j=0;
            while( i<10){
                QString linia=in.readLine();
  //              qDebug()<<"linia nr"<<linia;
                j=0;
                for(QString::iterator itc=linia.begin();itc!=linia.end() && j<14;itc=itc+1){
                    if(!itc->isSpace()){
                        idBoard[i][j]=itc->digitValue();
      //                  qDebug()<<"j "<<j;
                        j++;
                    }
                }
                i++;
            }

        }
        return true;
    }
    return false;
}

bool Loader::SetFilePathName(QString name){
    if(QFileInfo(name).completeSuffix()=="map" && QFileInfo(name).exists()){
        filePathName=name;
        return true;
    }
    else{
        filePathName=QString();
        return false;
    }

}
Loader & Loader::SetFilePathName(){
    QString str=QFileDialog::getOpenFileName(0,"Wczytaj mapę","../server/mapa1.map","Pliki map (*.map)");
    if(!str.isEmpty()) filePathName=str;
    return (*this);
}

const QVector<QVector<int> > & Loader::getIdBoard(){
    return idBoard;
}
