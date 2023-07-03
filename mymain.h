#ifndef MYMAIN_H
#define MYMAIN_H

#include <QWidget>
#include <QListWidgetItem>
#include "favouritemusicdatabase.h"
#include <unistd.h>
#include "musicinfo.h"
#include "soundvolume.h"
#include <QTimer>
#include <lyricshandle.h>
#include "pictureslideshow.h"
namespace Ui {
class MyMain;
}

class MyMain : public QWidget
{
    Q_OBJECT

public:
    explicit MyMain(QWidget *parent = 0);
    void setMusicList();
    void setFavouriteMusicList();
    void setStateLikeButton();
    void setCloseButton();
    void setMinimizeButton();
    void setPauseButton(int pauseButtonState);
    void setNextPrevButton();
    void setMusicInfo(QString songName, QString Author = "", QString IconUrl = "image/defaultCD.png");
    void setVolume();
    void setLyricsCharacteristics();
    void setPictureSlideShow();
    ~MyMain();
signals:
    //void getMaxSongTime();
private slots:
    void showMusicList(int columnHeaderIndex);
    //void playSong(QListWidgetItem* song);
    void playSong(QString song);
    void changeLikeButtonState();
    void closeWidget();
    void changeSongTimePos();
    void pausePlayMusic();
    void nextSong();
    void prevSong();
    void volumeChangeReceiver(int volume);
    void setSongPos();
    void lyricsControl();
    void changeStackWidgetIndex();
    void albumClicked();
    //void setMaxSongTime();
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::MyMain *ui;
    int LikeButtonState; //1 clicked, 0 unclicked
    int pauseButtonState; //1 play, 0 pause
    FavouriteMusicDataBase *favouriateList;
    QString currentPlayingSong;
    float currentSongMaxTime;
    MusicInfo *musicInfo;
    SoundVolume *soundVolume;
    //timer
    int currentSongPos;
    QTimer *timer;
    PictureSlideShow *slideShow;
    LyricsHandle *lyricsHandle;
};

#endif // MYMAIN_H
