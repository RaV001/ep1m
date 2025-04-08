#ifndef     SPEEDOMETER_H
#define     SPEEDOMETER_H

#include    <QLabel>

class Speedometer : public QLabel
{

public:

    Speedometer(QSize size, QString cfg_path, QWidget *parent = nullptr);
    ~Speedometer() = default;

    void setSpeed(int speed);
    void setSpeedLimits(int curSpeedLimit, int nextSpeedLimit);

    void clearSpeedLimits();

private:

    QLabel *speed_limits;

    QImage img_;
    QImage img_limits;

    QVector<QPoint> speed_coordsOutScale;
    QVector<QPoint> speed_coordsInsideScale;

    int num_speed_;

    int old_num_speed_;

    void drawArc_(int num_speed);
    void drawArcSpeedLimits(int num_speedLimit, int num_speedNextLimit = -1);

    void loadScalePontsCoolrds_(QString txt_path, QVector<QPoint> &vec);
};

#endif // SPEEDOMETER_H
