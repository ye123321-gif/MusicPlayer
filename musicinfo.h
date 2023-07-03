#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QWidget>

namespace Ui {
class MusicInfo;
}

class MusicInfo : public QWidget
{
    Q_OBJECT

public:
    explicit MusicInfo(QWidget *parent = 0);
    void setSongName(QString songName);
    void setSongAuthor(QString songAuthor);
    void setSongCD(QString url);
    ~MusicInfo();

private:
    Ui::MusicInfo *ui;
};

#endif // MUSICINFO_H
