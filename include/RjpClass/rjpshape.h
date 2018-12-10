#ifndef RJPSHAPE_H
#define RJPSHAPE_H

#include "QPainter"
#include "QVector"

#include "include/RjpClass/rjpdataset.h"

namespace rjpshapefile{
namespace drawpart{

class RjpShape
{
public:
    virtual ~RjpShape(){}
    virtual void drawShape(QPainter* painter, QVector<double> databox) const = 0;
    RjpShape* clone();
    RjpDatasetPtr getDatasetPtr() const {return _datasetPtr;}
protected:
    RjpDatasetPtr _datasetPtr;
    // input old coor, return new coor
    // according to paintdevice and displaybox
    QVector<double> data2Screen(QVector<double> coor,
                                QPaintDevice* pic,
                                QVector<double> displaybox);
    RjpShape(RjpDatasetPtr databasePtr):_datasetPtr(databasePtr){}
};

class RjpPoint : public RjpShape{
public:
    RjpPoint(RjpDatasetPtr datasetptr):RjpShape(datasetptr){}
    virtual ~RjpPoint(){}
    virtual void drawShape(QPainter* painter, QVector<double> databox) const;
};



}   // namespace drawpart
}   // namespace rjpshapefile
#endif // RJPSHAPE_H
