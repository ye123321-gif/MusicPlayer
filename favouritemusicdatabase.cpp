#include "favouritemusicdatabase.h"
#include <QDebug>
#include <stdio.h>
#define MYSQLSERVERIP "192.168.0.43"
#define MYSQLSERVERPWD "1314520"
#define MYSQLPORT 3306
FavouriteMusicDataBase::FavouriteMusicDataBase()
{
    mysql = NULL;
    sock = NULL;
}

void FavouriteMusicDataBase::initializeDatabase()
{
    mysql = new MYSQL;
    mysql_init(mysql);
    //Make sure to change second parameters and fourth parameters
    sock = mysql_real_connect(mysql, MYSQLSERVERIP, "root", MYSQLSERVERPWD, NULL, MYSQLPORT, NULL, 0);
    if (sock == NULL)
    {
        qDebug() << "Connection Failed" << endl;
        return;
    }
    qDebug() << "Connected Successfully" << endl;
    const char *sql_str = "CREATE DATABASE IF NOT EXISTS FavouriteMusic";
    int database = mysql_real_query(mysql, sql_str, strlen(sql_str));
    if(database != 0){
        qDebug() << "Failed to create database:" <<mysql_error(mysql) << endl;
        return;
    }
    int selectResult = mysql_select_db(mysql, "FavouriteMusic");
    //int selectResult = mysql_select_db(mysql, "person");
    if (selectResult != 0) {
        qDebug() << "Failed to select database:" << mysql_error(mysql) << endl;
        return;
    }

    const char *createTable = "CREATE TABLE IF NOT EXISTS MusicList(songName TEXT, duration_s INT)";
    int table = mysql_real_query(mysql, createTable, strlen(createTable));
    if(table != 0){
        qDebug() << "Failed to create table:" <<mysql_error(mysql) << endl;
        return;
    }
}

void FavouriteMusicDataBase::AddToDataBase(char *songName, int durationSec)
{

    char sql_str[256] = "";
    sprintf(sql_str, "select count(*) from MusicList where songName = '%s'", songName);
    mysql_real_query(mysql, sql_str, strlen(sql_str));
    MYSQL_RES *res = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    //qDebug() << row[0];
    if(!atoi(row[0])){

        sprintf(sql_str, "INSERT INTO MusicList (songName,duration_s) VALUES ('%s',%d)", songName,durationSec);
        int ret =  mysql_real_query(mysql, sql_str, strlen(sql_str));
        if(ret != 0){
            qDebug() << "Insert Failed" << mysql_error(mysql) << endl;
        }
    }
    mysql_free_result(res);
    return;
    qDebug() << "Song: " << songName << "exist already in the database" << endl;
}

void FavouriteMusicDataBase::RemoveFromDataBase(char *songName)
{
    char sql_str[256] = "";
    sprintf(sql_str, "select count(*) from MusicList where songName = '%s'", songName);
    mysql_real_query(mysql, sql_str, strlen(sql_str));
    MYSQL_RES *res = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    if(atoi(row[0])){
        sprintf(sql_str, "DELETE from MusicList where songName = '%s'", songName);
        mysql_real_query(mysql, sql_str, strlen(sql_str));
    }
    mysql_free_result(res);
}

void FavouriteMusicDataBase::closeDataBase()
{
    mysql_close(mysql);
    mysql_close(sock);
}

void FavouriteMusicDataBase::showTableData()
{
    const char *sql_str = "select * from MusicList"; //this one does
    int ret = mysql_real_query(mysql, sql_str, strlen(sql_str));
    if(ret != 0){
        qDebug() << "Mysql" << endl;
        return;
    }

    MYSQL_RES *res = mysql_store_result(mysql);
    //since we don't know how many columns and rows the result is
    if(res){
        int column = mysql_num_fields(res);
        int row = mysql_num_rows(res);
        qDebug() << "row=" << row  << "column=" <<column << endl;

        if(column > 0){ //this means there does exist some data
            MYSQL_FIELD *field;
            while((field = mysql_fetch_field(res))){ //mysql_fetch_field gets the column names one at a time
                printf("%s ", field->name);
            }
            printf("\n");
            MYSQL_ROW nextRow;
            while(nextRow = mysql_fetch_row(res)){ //mysql_fetch_row gets datas in row one at a time
                int j = 0;
                for(j = 0; j < column; j++){
                    printf("%s ", nextRow[j]);
                }
                printf("\n");
            }
        }
    }

    mysql_free_result(res);
    //mysql_close(sock);
}
#if 1
QList<char *> FavouriteMusicDataBase::retrieveSongName()
{
    QList<char *> songNameList;
    const char *sql_str = "select songName from MusicList";
    int ret = mysql_real_query(mysql, sql_str, strlen(sql_str));
    if(ret != 0){
        qDebug() << "Mysql" << endl;
        return songNameList;
    }
    MYSQL_RES *res = mysql_store_result(mysql);
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        songNameList.append(row[0]);
    }
    mysql_free_result(res);
    return songNameList;
}
#endif
#if 1
QStringList FavouriteMusicDataBase::retrieveSongName1()
{
    QStringList songNameList;
    const char *sql_str = "SELECT songName FROM MusicList";
    int ret = mysql_real_query(mysql, sql_str, strlen(sql_str));
    if (ret != 0) {
        qDebug() << "MySQL error" << endl;
        return songNameList;
    }
    MYSQL_RES *res = mysql_store_result(mysql);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        songNameList.append(QString::fromUtf8(row[0]));
    }
    mysql_free_result(res);
    return songNameList;
}
#endif
bool FavouriteMusicDataBase::isInDataBase(char *songName)
{
    //qDebug() << "because here?" << endl;
    char sql_str[128] = "";
    sprintf(sql_str, "select count(*) from MusicList where songName = '%s'", songName);
    mysql_real_query(mysql, sql_str, strlen(sql_str));
    MYSQL_RES* res = mysql_store_result(mysql);
    MYSQL_ROW row = mysql_fetch_row(res);
    int count = row ? atoi(row[0]) : 0;
    mysql_free_result(res);
    return count > 0;
}

