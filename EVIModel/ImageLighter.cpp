#include "ImageLighter.h"
#include "ui_ImageLighter.h"

#include <QDebug>

QPixmap ImageLighter::mask(const QPixmap &src)
{
    QImage tmp = src.toImage();
    for(int y = 0; y < tmp.height(); y++) {
        for(int x = 0; x < tmp.width(); x++) {
            auto color = tmp.pixelColor(x, y);
            if(color.red() > 200 && color.green() > 200 && color.blue() < 200) {
                color = Qt::transparent;
            }
            tmp.setPixelColor(x, y, color);
        }
    }
    return QPixmap::fromImage(tmp);
}

ImageLighter::ImageLighter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageLighter)
{
    ui->setupUi(this);
    qDebug() << "chargeStation" << source.load(":/charging-station.png");
    masked = mask(source);
    qDebug() << "chargeStation_nc" << source_nc.load(":/charging-station_nc.png");
    masked_nc = mask(source_nc);

    ui->labImage->setPixmap(masked_nc);
    ui->labImage->setScaledContents(true);
}

ImageLighter::~ImageLighter()
{
    delete ui;
}

void ImageLighter::SetOff(bool isOff)
{
    if(isOff) {
        ui->labImage->setPixmap(masked_nc);
    } else {
        ui->labImage->setPixmap(masked);
    }
}
