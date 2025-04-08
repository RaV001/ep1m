#include    "speedometer.h"
#include    <QPainter>
#include    <QVector>
#include    <QFile>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Speedometer::Speedometer(QSize size, QString cfg_path, QWidget *parent)
    : QLabel(parent)
    , num_speed_(0)
    , old_num_speed_(0)
{
    this->resize(size);
   // this->setStyleSheet("border: 1px solid red;");

    speed_limits = new QLabel(this);
    speed_limits->resize(size);

    img_ = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    img_limits = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

    loadScalePontsCoolrds_(cfg_path + "speed-coordinatesOutScale.txt", speed_coordsOutScale);
    loadScalePontsCoolrds_(cfg_path + "speed-coordinatesInsideScale.txt", speed_coordsInsideScale);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Speedometer::setSpeed(int speed)
{
    num_speed_ = speed / 5;

    if(num_speed_ == old_num_speed_)
        return;

    drawArc_(num_speed_);

    old_num_speed_ = num_speed_;
}

void Speedometer::setSpeedLimits(int curSpeedLimit, int nextSpeedLimit)
{
    int num_speedLimit_ = curSpeedLimit / 5;
    int num_speedNextLimit_ = nextSpeedLimit / 5;

    if(nextSpeedLimit > curSpeedLimit)
        drawArcSpeedLimits(num_speedLimit_);
    else
        drawArcSpeedLimits(num_speedLimit_, num_speedNextLimit_);
}

void Speedometer::clearSpeedLimits()
{
    speed_limits->clear();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Speedometer::drawArc_(int num_speed)
{
    img_.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    // скорость
    paint.setPen(QPen(QColor(Qt::green), 9, Qt::SolidLine, Qt::RoundCap));
    for (int i = 0, n = num_speed + 1; i < n; ++i)
    {
        paint.drawPoint(speed_coordsInsideScale[i]);
    }

    paint.end();
    this->setPixmap(pix);
}

void Speedometer::drawArcSpeedLimits(int num_speedLimit, int num_speedNextLimit)
{
    img_limits.fill(Qt::transparent);
    QPixmap pix = QPixmap::fromImage(img_limits);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing, true);

    if(num_speedLimit >= 0)
    {
        // ограничение скорости
        paint.setPen(QPen(QColor(Qt::red), 9, Qt::SolidLine, Qt::RoundCap));
        paint.drawPoint(speed_coordsOutScale[num_speedLimit]);
    }

    if(num_speedNextLimit >= 0)
    {
        // следующее ограничение скорости
        paint.setPen(QPen(QColor(Qt::yellow), 9, Qt::SolidLine, Qt::RoundCap));
        paint.drawPoint(speed_coordsOutScale[num_speedNextLimit]);
    }

    paint.end();
    speed_limits->setPixmap(pix);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Speedometer::loadScalePontsCoolrds_(QString txt_path, QVector<QPoint> &vec)
{
    QFile fileTxt(txt_path);

    if (!QFile::exists(fileTxt.fileName()))
        return;

    if (fileTxt.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!fileTxt.atEnd())
        {
            QString str = fileTxt.readLine();
            QStringList strList = str.split(" ");
            int x = strList[0].toInt();
            int y = strList[1].toInt();
            vec.append(QPoint(x, y));
        }
        fileTxt.close();
    }
}
