#ifndef SOUNDVOLUME_H
#define SOUNDVOLUME_H

#include <QWidget>

namespace Ui {
class SoundVolume;
}

class SoundVolume : public QWidget
{
    Q_OBJECT

public:
    explicit SoundVolume(QWidget *parent = 0);
    ~SoundVolume();
protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
signals:
    void volumeChanged(int volume);
private slots:
    void emitVolumeChangedSignal(int volume);

private:
    Ui::SoundVolume *ui;
};

#endif // SOUNDVOLUME_H
