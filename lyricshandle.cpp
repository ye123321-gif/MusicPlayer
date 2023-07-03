#include "lyricshandle.h"
#include <stdio.h>
#include <stdexcept>
#include <string.h>

#include <QDebug>
#define MAXOCCURANCEOFSONG 5
char *getLrcInfo(char *buf){
    char *p = buf + 4;
    char *msg = new char[LRC_LENGTH];
    int i = 0;
    while(*p != ']'){
        msg[i] = *p;
        p++;
        i++;
    }
    msg[i] = '\0';

    return msg;
}

LyricsHandle::LyricsHandle()
{
    memset(title, 0, 128);
    memset(artist, 0, 128);
    memset(album, 0, 128);
}

QString LyricsHandle::getArtist() const
{
    return QString(artist);
}
QString LyricsHandle::getTitle() const
{
    return QString(title);
}

QString LyricsHandle::getAlbum() const
{
    return QString(album);
}

void LyricsHandle::getLrcText(vector<LrcText *> &lyricContainer)
{
    FILE *fd = fopen(LrcFileName, "rb");
    //qDebug() << LrcFileName << endl;
    char temp[LRC_LENGTH] = "";
    char *songPos = NULL;
    int min = 0;
    int second = 0;
    int time[MAXOCCURANCEOFSONG] = {0};
    int occurance = 0;
    while(fgets(temp, LRC_LENGTH, fd) != NULL){
        songPos = temp;
        occurance = 0;
        while(songPos[0] == '[' && songPos[1] >= '0' && songPos[1] <= '9' ){
            sscanf(songPos,"[%d:%d", &min, &second);
            time[occurance] = min * 60 + second;

            occurance++;
            songPos += 10;
        }
        if(*songPos == '\0' || *songPos == '\n')
        {
            continue;
        }

        //qDebug() << occurance << endl;
        for(int i = 0; i < occurance;i++){
            LrcText *tempLrc = new LrcText;
            tempLrc->time = time[i];
            strcpy(tempLrc->lyric, songPos);
            lyricContainer.push_back(tempLrc);
        }
    }
    fclose(fd);
}
void LyricsHandle::setLrcFileName(const char* LrcFileName)
{
    FILE *fp;

    if((fp = fopen(LrcFileName, "rb")) == NULL){
        throw std::logic_error(std::string(LrcFileName) + "doesn't exist");
    }
    char temp[LRC_LENGTH] = "";
    for(int i = 0; i < 3; i++){
        fgets(temp, LRC_LENGTH, fp);
        if(!strncmp(temp, "[ti:", 4)){
            strcpy(title, getLrcInfo(temp));
        }
        else if(!strncmp(temp, "[ar:", 4)){
            strcpy(artist, getLrcInfo(temp));
        }
        else if(!strncmp(temp, "[al:", 4)){
            strcpy(album, getLrcInfo(temp));
        }
    }
    strcpy(this->LrcFileName, LrcFileName);
    //qDebug() << title << endl;
    fclose(fp);
}

void LyricsHandle::clearLyricContainer(vector<LrcText *> &LyricsContainer)
{
    for(vector<LrcText *>::iterator it = LyricsContainer.begin(); it != LyricsContainer.end(); it++){
        delete *it;
    }
    LyricsContainer.clear();
}

