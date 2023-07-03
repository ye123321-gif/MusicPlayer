#include "mymain.h"
#include "ui_mymain.h"
#include <QGridLayout>

#include <sys/types.h>
#include <dirent.h>

#include <QRegularExpression>
#include <qdebug.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QBitmap>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <QStyledItemDelegate>
#define MUSIC_LIST 0
#define FAVORIATE_MUSIC_LIST 1

static int pipefd;
/* Semaphore used to modifying a parallel programming for getting the song max time
 * and playing the song.
 * It's used because we are getting the maximum song time from mplayer outputs
 */
static sem_t *sem1 = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
static sem_t *sem2 = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
static bool LikeStateControl = false; //true if we in Favouriate Music list

static vector<LrcText *> lyricContainer;//stores lyric lines
static int vectorpos = 0;

//Used to centralize text within a listwidget
class CenterAlignDelegate : public QStyledItemDelegate {
public:
    //this function is responsible for painting the item in the list widget.
    //In default, the delegate uses the base implementation of QStyledItemDelegatee::paint
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        QStyleOptionViewItem updatedOption = option;
        updatedOption.displayAlignment = Qt::AlignCenter;
        QStyledItemDelegate::paint(painter, updatedOption, index);
    }
};


static void *readMplayerMessage(void *arg){
    pipefd = open("mplayerMessage", O_RDONLY);
    char buffer[64] = "";
    while ((read(pipefd, buffer, sizeof(buffer))) > 0) {
        if(strncmp(buffer, "ANS_LENGTH",strlen("ANS_LENGTH")) == 0){
            sem_wait(sem2);
            sscanf(buffer, "ANS_LENGTH=%f", (float *)arg);
            sem_post(sem1);
        }

    }
    return NULL;
}
MyMain::MyMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMain)
{
    ui->setupUi(this);
    //Initialization
    currentSongMaxTime = 0;
    currentPlayingSong = "";
    musicInfo = new MusicInfo;
    soundVolume = new SoundVolume(this);
    timer = new QTimer(this);
    currentSongPos = 0;
    pauseButtonState = 0;
    lyricsHandle = new LyricsHandle;
    ui->listWidget_lyrics->setItemDelegate(new CenterAlignDelegate());
    connect(timer, &QTimer::timeout, this, &MyMain::setSongPos);
    connect(timer, &QTimer::timeout, this, &MyMain::lyricsControl);
    ui->tableWidget->setColumnCount(2);

    //event filter
    ui->pushButton_volume->installEventFilter(this);

    //Incompleted
    ui->pushButton_cloth->hide();
    //

    // Set header item size
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    //ui->tableWidget->horizontalHeader()->setFixedWidth(80); // Adjust the width as desired

    // Set header item transparency
    //ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: transparent; }");
    ui->tableWidget->setStyleSheet("background-color: transparent; border:none");
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QIcon(":/image/musicicon2.png"), ""));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QIcon(":/image/heart.png"),""));
    ui->horizontalSlider_music->setStyleSheet("QSlider::handle:Horizontal#horizontalSlider_music{width:10px;"
                                              "border-image: url(image/slider.png);margin:-4 px -4px;}");
    ui->pushButton_lyrics->setStyleSheet("QPushButton#pushButton_lyrics { border-image: url(image/lyrics.png); }"
                                        "QPushButton { background-color: transparent; border: none;}"
                                        "QPushButton:focus { outline: none; }");

    ui->pushButton_album1->setStyleSheet("QPushButton#pushButton_album1 { border-image: url(image/Diamonds.png); }");
    ui->pushButton_album2->setStyleSheet("QPushButton#pushButton_album2 { border-image: url(image/StopLove.png); }");
    ui->pushButton_album3->setStyleSheet("QPushButton#pushButton_album3 { border-image: url(image/简单爱.png); }");
    ui->pushButton_album4->setStyleSheet("QPushButton#pushButton_album4 { border-image: url(image/后来的我们.png); }");

    QHeaderView *header = ui->tableWidget->horizontalHeader();
    connect(header, SIGNAL(sectionClicked(int)), this, SLOT(showMusicList(int)));

    connect(ui->listWidget_musiclist, SIGNAL(currentTextChanged(QString)), this, SLOT(playSong(QString)));
    connect(ui->horizontalSlider_music, &QSlider::sliderReleased, this, &MyMain::changeSongTimePos);
    connect(ui->pushButton_pause, SIGNAL(clicked(bool)), this, SLOT(pausePlayMusic()));
    connect(ui->pushButton_next,SIGNAL(clicked(bool)), this, SLOT(nextSong()));
    connect(ui->pushButton_prev,SIGNAL(clicked(bool)), this, SLOT(prevSong()));
    connect(ui->pushButton_lyrics, SIGNAL(clicked(bool)), this, SLOT(changeStackWidgetIndex()));
    connect(ui->pushButton_album1, &QPushButton::clicked, this, &MyMain::albumClicked);
    connect(ui->pushButton_album2, &QPushButton::clicked, this, &MyMain::albumClicked);
    connect(ui->pushButton_album3, &QPushButton::clicked, this, &MyMain::albumClicked);
    connect(ui->pushButton_album4, &QPushButton::clicked, this, &MyMain::albumClicked);

    //volume change signal receiver
    connect(soundVolume,&SoundVolume::volumeChanged, this, &MyMain::volumeChangeReceiver);

    setStateLikeButton();
    setCloseButton();
    setMinimizeButton();
    setNextPrevButton();
    setVolume();
    setPauseButton(pauseButtonState);
    setLyricsCharacteristics();
    setPictureSlideShow();
    favouriateList = new FavouriteMusicDataBase;
    favouriateList->initializeDatabase();
    //favouriateList->AddToDataBase((char *)"bob1", 0);
    //favouriateList->AddToDataBase((char *)"bob2", 0);
    //favouriateList->AddToDataBase((char *)"bob3", 0);
    //favouriateList->RemoveFromDataBase((char *)"Diamonds");
    //favouriateList->RemoveFromDataBase((char *)"bob1");
    //favouriateList->RemoveFromDataBase((char *)"bob3");
    //favouriateList->showTableData();
    //favouriateList->closeDataBase();
    setMusicList();

    mkfifo("myfifo",0664);
    mkfifo("mplayerMessage", 0664);

    pid_t pid = fork();
    if(pid == 0){//Child process
        int pipefd = open("mplayerMessage", O_WRONLY);
        dup2(pipefd, STDOUT_FILENO);
        ::close(pipefd);
        execlp("mplayer", "mplayer", "-slave", "-quiet", "-idle", "-input", "file=./myfifo",NULL);
    }

    waitpid(-1, NULL, WNOHANG);
    sem_init(sem2, 0, 1);
    sem_init(sem1, 0, 0);
    pthread_t tid;
    pthread_create(&tid, NULL, readMplayerMessage, (void *)&currentSongMaxTime);
    pthread_detach(tid);
}


void MyMain::setMusicList()
{
    //get directory handle
    DIR *dir = opendir("./song");
    struct dirent *ret;
    QRegularExpression pattern(".+\\.mp3");

    while(ret = readdir(dir)){
        if(((ret->d_type & DT_REG) == DT_REG)
                && pattern.match((QString)ret->d_name).hasMatch()){
            QListWidgetItem *song = new QListWidgetItem(ui->listWidget_musiclist);
            song->setText(QString(ret->d_name).section(".",0,0));
        }
    }
    closedir(dir);
}

void MyMain::setFavouriteMusicList()
{
    QStringList list = favouriateList->retrieveSongName1();
    for(QStringList::iterator it = list.begin(); it != list.end(); it++){
        QListWidgetItem *song = new QListWidgetItem(ui->listWidget_musiclist);
        song->setText(*it);
    }
}

void MyMain::setStateLikeButton()
{
    LikeButtonState = 0;
    QIcon iconUnclicked(":/image/likeUnclicked.png");
    ui->pushButton_like->setStyleSheet("QPushButton { border: none; padding: 0; }"
                                       "QPushButton:pressed { background-color: transparent; }"
                                       "QPushButton:focus { outline: none; }");
    ui->pushButton_like->setIcon(QIcon(iconUnclicked));
    connect(ui->pushButton_like, &QPushButton::clicked, this, &MyMain::changeLikeButtonState);

}

void MyMain::setCloseButton()
{
    QIcon iconClose(":/image/btn_close.png");
    ui->pushButton_close->setStyleSheet("QPushButton { background-color: transparent; border: none;}"
                                        "QPushButton:hover { background-color: red;}");
    ui->pushButton_close->setIcon(QIcon(iconClose));
    connect(ui->pushButton_close, &QPushButton::clicked, this, &MyMain::closeWidget);
}

void MyMain::setMinimizeButton()
{
    QIcon iconMin(":/image/btn_min.png");
    ui->pushButton_min->setStyleSheet("QPushButton { background-color: transparent; border: none;}"
                                        "QPushButton:hover { background-color: red;}");
    ui->pushButton_min->setIcon(QIcon(iconMin));
    ui->pushButton_min->setFocusPolicy(Qt::NoFocus);
    connect(ui->pushButton_min, &QPushButton::clicked, this, &MyMain::showMinimized);
}

void MyMain::setPauseButton(int pauseButtonState)
{

    if (!pauseButtonState) {
        timer->stop();
        ui->pushButton_pause->setStyleSheet("QPushButton#pushButton_pause { border-image: url(image/pause.png); }"
                                            "QPushButton { background-color: transparent; border: none;}"
                                            "QPushButton:focus { outline: none; }");
    } else {
        timer->start();
        ui->pushButton_pause->setStyleSheet("QPushButton#pushButton_pause { border-image: url(image/play.png); }"
                                            "QPushButton { background-color: transparent; border: none;}"
                                            "QPushButton:focus { outline: none; }");
    }
}

void MyMain::setNextPrevButton()
{
    ui->pushButton_next->setStyleSheet("QPushButton#pushButton_next { border-image: url(image/next.png); }"
                                       "QPushButton { background-color: transparent; border: none; }"
                                       "QPushButton:focus { outline: none; }"
                                       "QPushButton::pressed#pushButton_next{border-image:url(image/next_h.png);}");
    ui->pushButton_prev->setStyleSheet("QPushButton#pushButton_prev { border-image: url(image/prev.png); }"
                                        "QPushButton { background-color: transparent; border: none;}"
                                        "QPushButton:focus { outline: none; }"
                                       "QPushButton::pressed#pushButton_prev{border-image:url(image/prev_h.png);}");
}

void MyMain::setMusicInfo(QString songName, QString Author, QString IconUrl)
{
    musicInfo->setSongName(songName);
    musicInfo->setSongAuthor(Author);
    musicInfo->setSongCD(IconUrl);
    ui->verticalLayout->addWidget(musicInfo);
}

void MyMain::setVolume()
{
    /* setting Icon and remove background in the icon for volume pushbutton
     */
    QIcon iconVolume(":/image/volume.png");
    ui->pushButton_volume->setStyleSheet("QPushButton { background-color: transparent; border: none;}");
    //Remove white background from icon
    QPixmap pixmap = iconVolume.pixmap(iconVolume.actualSize(QSize(48, 48)));
    pixmap.setMask(pixmap.createMaskFromColor(Qt::white));
    ui->pushButton_volume->setIcon(QIcon(pixmap));

    soundVolume->setGeometry(675,380,50,110);
    soundVolume->raise();
    soundVolume->hide();
}

void MyMain::setLyricsCharacteristics()
{
    ui->listWidget_lyrics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_lyrics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setting default text color and font for lyrics (Optional)
    QColor textColor(0, 0, 0); // Black color
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Text, textColor);
    ui->listWidget_lyrics->setPalette(palette);
    // Set the default font
    QFont font("Arial", 12); // Font name: Arial, Font size: 12
    ui->listWidget_lyrics->setFont(font);
}

void MyMain::setPictureSlideShow()
{
    slideShow = new PictureSlideShow;
    ui->verticalLayout_2->addWidget(slideShow);
}

MyMain::~MyMain()
{
    delete ui;
    delete favouriateList;
    delete musicInfo;
    delete slideShow;
    delete lyricsHandle;
}

void MyMain::showMusicList(int columnHeaderIndex)
{
    if(columnHeaderIndex == MUSIC_LIST){
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QIcon(":/image/musicicon2.png"), ""));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QIcon(":/image/heart.png"),""));\
        ui->listWidget_musiclist->clear();
        setMusicList();
        LikeStateControl = false;
    }
    else if(columnHeaderIndex == FAVORIATE_MUSIC_LIST){
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QIcon(":/image/heart2.png"),""));
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QIcon(":/image/musicicon.png"), ""));
        ui->listWidget_musiclist->clear();
        setFavouriteMusicList();
        LikeStateControl = true;
    }

    //To make sure the song is still selected when switching between Lists,
    if(ui->listWidget_musiclist->findItems(currentPlayingSong,Qt::MatchExactly).count()){
        ui->listWidget_musiclist->blockSignals(true); //blocking signals, so no double play
        ui->listWidget_musiclist->setCurrentItem(ui->listWidget_musiclist->findItems(currentPlayingSong,Qt::MatchExactly).first(),
                                             QItemSelectionModel::Select);
        ui->listWidget_musiclist->blockSignals(false);//unblock signals
    }
}
#if 0
void MyMain::playSong(QListWidgetItem *song)
{
    QByteArray songName = song->text().toLatin1();
    char *sn = songName.data();
    sn[strlen(sn)] = '\n';
    write(STDIN_FILENO, "loadfile ", strlen(sn));
}
#endif
void MyMain::playSong(QString song)
{
    if(song != NULL){
        int cur_song = open("myfifo", O_WRONLY);
        char buf[64] = "";
        sprintf(buf, "loadfile ./song/%s.mp3\n",song.toUtf8().data());
        //set start time to 0, in case if user changes song during the runtime of previous song
        if(currentPlayingSong != song){
            currentSongPos = 0;
        }
        currentPlayingSong = song;
        qDebug() << "cursong: " << currentPlayingSong << endl;
        write(cur_song, buf, strlen(buf));
        setPauseButton(pauseButtonState = 1);

        //setting up authors
        sprintf(buf, "./lyrics/%s.lrc",song.toUtf8().data());
        lyricsHandle->clearLyricContainer(lyricContainer);
        ui->listWidget_lyrics->clear();
        try{
            lyricsHandle->setLrcFileName(buf);
            //setting up lyrics
            lyricsHandle->getLrcText(lyricContainer);
            for(vector<LrcText *>::iterator it = lyricContainer.begin(); it != lyricContainer.end(); it++){
                ui->listWidget_lyrics->addItem(QString((*it)->lyric));
            }
            vectorpos = 0;
        }
        catch(exception &e){
            qDebug() << e.what() << endl;
        }
        sprintf(buf, "image/%s.png",song.toUtf8().data());
        setMusicInfo(song,lyricsHandle->getArtist(),buf);

        //modifying a save so that when switching between songs, the LikeButtonState
        //for each song is not lost
        LikeButtonState = 0;
        if(!LikeStateControl && !favouriateList->isInDataBase(song.toUtf8().data())){
            LikeButtonState = 1;
        }

        changeLikeButtonState();
        write(cur_song,"get_time_length\n", strlen("get_time_length\n"));
        qDebug() << "here" << endl;
        sem_wait(sem1);
        //timer
        timer->start(1000);
        //
        int totalSeconds = static_cast<int>(currentSongMaxTime);
        qDebug() << totalSeconds << endl;
        int seconds = totalSeconds % 60;
        int minutes = totalSeconds / 60;
        ui->label_endtime->setText(QString("%1:%2")
                                   .arg(minutes, 2, 10, QLatin1Char('0'))
                                   .arg(seconds, 2, 10, QLatin1Char('0')));
        sem_post(sem2);
    }
}

void MyMain::changeLikeButtonState()
{
    LikeButtonState ^= 0x01;
    switch(LikeButtonState){
    case 0:{
        QIcon iconUnclicked(":/image/likeUnclicked.png");
        ui->pushButton_like->setIcon(QIcon(iconUnclicked));
        favouriateList->RemoveFromDataBase((char *)currentPlayingSong.toUtf8().data());
        //favouriateList->showTableData();
        if(LikeStateControl){
            showMusicList(FAVORIATE_MUSIC_LIST);
        }
        break;
    }
    case 1:{
         QIcon iconClicked(":/image/likeClicked.png");
         //Remove white background from icon
         QPixmap pixmap = iconClicked.pixmap(iconClicked.actualSize(QSize(24, 24)));
         pixmap.setMask(pixmap.createMaskFromColor(Qt::white));
         ui->pushButton_like->setIcon(QIcon(pixmap));
         favouriateList->AddToDataBase((char *)currentPlayingSong.toUtf8().data(),0);
         //favouriateList->showTableData();
         break;
    }
    default:
        break;
    }
}

void MyMain::closeWidget()
{
    int mplayer_close = open("myfifo", O_WRONLY);
    write(mplayer_close, "quit\n", strlen("quit\n"));
    favouriateList->closeDataBase();
    ::close(mplayer_close);
    ::close(pipefd);
    sem_destroy(sem1);
    sem_destroy(sem2);
    this->close();
}

void MyMain::changeSongTimePos()
{
    int value = ui->horizontalSlider_music->sliderPosition();
    int pos = (value * currentSongMaxTime / 100) - currentSongPos;
    currentSongPos = value * currentSongMaxTime / 100;
    char buf[64] = "";
    sprintf(buf,"seek %d\n", pos);
    int mplayer_pos = open("myfifo", O_WRONLY);
    write(mplayer_pos, buf,strlen(buf));
    if(pauseButtonState == 0){
        write(mplayer_pos, "pause\n", strlen("pause\n"));
    }
    if(vectorpos > 0){
        ui->listWidget_lyrics->item(vectorpos - 1)->setTextColor(QColor(0,0,0,255));
        ui->listWidget_lyrics->item(vectorpos - 1)->setFont(QFont("Arial", 12));
    }
#if 0
    int lyricSize = lyricContainer.size() - 1;
    if(currentSongPos == 0){
        vectorpos = 0;
    }
    else if (currentSongPos > lyricContainer[vectorpos]->time){
        while(1){
            vectorpos++;
            qDebug() << "size: "<< lyricContainer.size() << "pos:" << vectorpos << endl;
            if(vectorpos == lyricSize){
                vectorpos = 0;
                break;
            }
            else if(currentSongPos <= lyricContainer[vectorpos]->time){
                //qDebug() << lyricContainer[vectorpos]->time << "here1" << vectorpos << " and " << currentSongPos << endl;
                break;
            }
        }
    }
    else if(currentSongPos < lyricContainer[vectorpos]->time){
        while(1){
            vectorpos--;
            if(currentSongPos >= lyricContainer[vectorpos]->time){
                vectorpos += 1; //best case is ==, but since timer is running, it's unlickly to have ==
                                //hence we need to add 1 to the lyric line, so that timer can catch up
                //qDebug() << "here111" << endl;
                //qDebug() << lyricContainer[vectorpos]->time << "here2" << vectorpos << " and " << currentSongPos << endl;
                break;
            }
        }
    }
#endif
    //finding relative lyric line position for song slider
    int lyricSize = lyricContainer.size() - 1;
    int start = 0;
    int end = lyricSize;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (vectorpos == lyricSize || currentSongPos == 0){
            vectorpos = 0;
            break;
        }
        else if (currentSongPos == lyricContainer[mid]->time) {
            vectorpos = mid;
            break;
        } else if (currentSongPos < lyricContainer[mid]->time) {
            end = mid - 1;
        } else {
            vectorpos = mid + 1;
            start = mid + 1;
        }
    }
}

void MyMain::pausePlayMusic()
{
    int mplayer_pause = open("myfifo", O_WRONLY);
    pauseButtonState ^= 0x01;
    setPauseButton(pauseButtonState);
    write(mplayer_pause, "pause\n",strlen("pause\n"));
    if(currentSongPos == 0 && pauseButtonState){
        playSong(currentPlayingSong);
    }
}

void MyMain::nextSong()
{
    int curRow = ui->listWidget_musiclist->currentRow();
    if(curRow != ui->listWidget_musiclist->count() - 1){
        ++curRow;
    }
    else{
        curRow = 0;
    }
    ui->listWidget_musiclist->setCurrentRow(curRow,QItemSelectionModel::ClearAndSelect);
}

void MyMain::prevSong()
{
    int curRow = ui->listWidget_musiclist->currentRow();
    if(curRow != 0){
        --curRow;
    }
    else{
        curRow = ui->listWidget_musiclist->count() - 1;
    }
    ui->listWidget_musiclist->setCurrentRow(curRow,QItemSelectionModel::ClearAndSelect);
}

void MyMain::volumeChangeReceiver(int volume)
{
    int mplayer_volume = open("myfifo", O_WRONLY);
    char buf[64] = "";
    sprintf(buf,"volume %d 1\n", volume);
    write(mplayer_volume, buf,strlen(buf));
}

void MyMain::setSongPos()
{
    ++currentSongPos;
    int seconds = currentSongPos % 60;
    int minutes = currentSongPos / 60;
    ui->label_starttime->setText(QString("%1:%2")
                               .arg(minutes, 2, 10, QLatin1Char('0'))
                               .arg(seconds, 2, 10, QLatin1Char('0')));
    if(ui->horizontalSlider_music->isSliderDown() == false)
        ui->horizontalSlider_music->setValue(currentSongPos / currentSongMaxTime * 100);
    //ui->label_starttime->setText(QString::number(++currentSongPos));
    if(currentSongPos == currentSongMaxTime){
        timer->stop();
        pauseButtonState = 0;
        setPauseButton(pauseButtonState);
        currentSongPos = 0;
    }
}

void MyMain::lyricsControl()
{
    //qDebug () << lyricContainer[vectorpos]->time << "new " << vectorpos << "current " << currentSongPos << endl;
    if(!lyricContainer.empty()){
        if(lyricContainer[vectorpos]->time == currentSongPos || currentSongPos == 0 || lyricContainer[vectorpos]->time == 0){
            qDebug() << vectorpos << endl;
            ui->listWidget_lyrics->item(vectorpos)->setTextColor((QColor(255,0,0,255)));
            ui->listWidget_lyrics->item(vectorpos)->setFont(QFont("Arial", 18));
            if(vectorpos > 0){
                ui->listWidget_lyrics->item(vectorpos - 1)->setTextColor(QColor(0,0,0,255));
                ui->listWidget_lyrics->item(vectorpos - 1)->setFont(QFont("Arial", 12));
            }
            ui->listWidget_lyrics->scrollToItem(ui->listWidget_lyrics->item(vectorpos),
                                                QAbstractItemView::PositionAtCenter);
            vectorpos++;
            if(vectorpos == lyricContainer.size()){
                vectorpos = 0;
            }
        }
    }

}

void MyMain::changeStackWidgetIndex()
{
    int curIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(curIndex ^ 0x01);
}

void MyMain::albumClicked()
{
     QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
     if (senderButton == ui->pushButton_album1) {
         playSong("Diamonds");
     } else if (senderButton == ui->pushButton_album2) {
         playSong("StopLove");
     } else if (senderButton == ui->pushButton_album3) {
         playSong("简单爱");
     } else if (senderButton == ui->pushButton_album4) {
        playSong("后来的我们");
     }
}



//volume button
bool MyMain::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->pushButton_volume && event->type() == QEvent::Enter)
    {
        soundVolume->show();
        return true;
    }
    else if(watched == ui->pushButton_volume && event->type() == QEvent::Leave)
    {
        //checks if the mouse cursor is not currently inside the 'soundVolume' widget
        if(!soundVolume->underMouse()){
            soundVolume->hide();
        }

        return true;
    }
    // Call base class eventFilter for other events

    return QWidget::eventFilter(watched, event);

}
