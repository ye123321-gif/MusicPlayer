#include "soundvolume.h"
#include "ui_soundvolume.h"

SoundVolume::SoundVolume(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundVolume)
{
    ui->setupUi(this);
    ui->verticalSlider_volume->setValue(50);
    connect(ui->verticalSlider_volume, &QSlider::valueChanged, this, &SoundVolume::emitVolumeChangedSignal);
}

SoundVolume::~SoundVolume()
{
    delete ui;
}

void SoundVolume::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->hide();
}

void SoundVolume::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->show();
}

void SoundVolume::emitVolumeChangedSignal(int volume)
{
    emit volumeChanged(volume);
}
