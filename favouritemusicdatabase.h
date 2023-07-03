#ifndef FAVOURITEMUSICDATABASE_H
#define FAVOURITEMUSICDATABASE_H
#include <mysql/mysql.h>
#include <QList>
#include <QStringList>
class FavouriteMusicDataBase
{
public:
    FavouriteMusicDataBase();
    void initializeDatabase();
    void AddToDataBase(char *songName, int durationSec);
    void RemoveFromDataBase(char *songName);
    void closeDataBase();
    void showTableData();
    QList<char *> retrieveSongName();
    QStringList retrieveSongName1();
    bool isInDataBase(char *songName);
    //GetFavouriteMusicList();
private:
    MYSQL *mysql;
    MYSQL *sock;
};

#endif // FAVOURITEMUSICDATABASE_H
