#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QLabel>



class Speedometer : public QLabel
{

public:
    Speedometer(QSize size, QString cfg_path, QWidget *parent = Q_NULLPTR);

    void setSpeed(int speed);
    void setSpeedLimit(int speedLimit);
    void setSpeedNextLimit(int speedNextLimit);


private:
    QImage img_;

    QVector<QPoint> speed_coordsOutScale;
    QVector<QPoint> speed_coordsInsideScale;

    int num_speed_;
    int num_speedLimit_;
    int cur_speed_limit;
    int num_speedNextLimit_;

    int old_num_speed_;
    int old_num_speedLimit_;
    int old_num_speedNextLimit_;


    void drawArc_(int num_speed, int num_speedLimit = -1, int num_speedNextLimit = -1);

    void loadScalePontsCoolrds_(QString txt_path, QVector<QPoint> &vec);


};

#endif // SPEEDOMETER_H
