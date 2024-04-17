#ifndef COORDWORKER_H
#define COORDWORKER_H

#include <QPolygonF>

class CoordWorker
{
public:
    CoordWorker();
    static QPolygonF get_coords(double start, double end, double step);
};

#endif // COORDWORKER_H
