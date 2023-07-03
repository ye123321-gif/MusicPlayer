#include "musicinfo.h"
#include "ui_musicinfo.h"

MusicInfo::MusicInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicInfo)
{
    ui->setupUi(this);
    QFont font;
    font.setPointSize(8);
    ui->label_SongAuthor->setFont(font);
}

void MusicInfo::setSongName(QString songName)
{
    ui->label_SongName->setText(songName);
}

void MusicInfo::setSongAuthor(QString songAuthor)
{
    ui->label_SongAuthor->setText(songAuthor);
}

void MusicInfo::setSongCD(QString url)
{
    QString str = "QPushButton{border-image:url("+url+");}"
                  "QPushButton:focus { outline: none; }";
    ui->pushButton_SongCD->setStyleSheet(str);
}

MusicInfo::~MusicInfo()
{
    delete ui;
}
