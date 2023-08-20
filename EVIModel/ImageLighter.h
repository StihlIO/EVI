#ifndef IMAGELIGHTER_H
#define IMAGELIGHTER_H

#include <QWidget>

namespace Ui
{
class ImageLighter;
}

class ImageLighter : public QWidget
{
    Q_OBJECT

    QPixmap source_nc;
    QPixmap masked_nc;
    QPixmap source;
    QPixmap masked;

    QPixmap mask(const QPixmap &src);

public:
    explicit ImageLighter(QWidget *parent = nullptr);
    ~ImageLighter();

    void SetOff(bool isOff);

private:
    Ui::ImageLighter *ui;
};

#endif // IMAGELIGHTER_H
