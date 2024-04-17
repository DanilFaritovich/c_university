#include "coordworker.h"
#include <QWidget>

CoordWorker::CoordWorker() {}

QPolygonF CoordWorker::get_coords(double start, double end, double step)
{
    float y;
    QPolygonF list {};
    for (double x = start;x < end + step; x += step)
    {
        y = pow(x, 3) + 12 * x - 2;
        qInfo() << x << y;
        qInfo() << QPointF(((-round(x*100)/100) * 120), -y * 10);
        list.push_back(QPointF(((-round(x*100)/100) * 120), -y * 10));
    }
    return list;
}
