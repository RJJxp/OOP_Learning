#ifndef RJPSHAPES_H
#define RJPSHAPES_H

#include "QVector"
#include "QString"
#include "QPaintDevice"

#include "include/RjpClass/rjpshape.h"
#include "include/RjpClass/rjpshapescommand.hpp"

namespace ob = rjpshapefile::obpart;    // use namespace obpart

namespace rjpshapefile{
namespace drawpart{

class RjpShapes
{
public:
    ~RjpShapes();
    RjpShapes();    // 3 constructor
    RjpShapes(ob::ShapesObCommand* obc);
    RjpShapes(RjpShapes* shapes);
    RjpShape* at(int i) const ;// at
    void setOb(ob::ShapesObCommand* ob);
    void addShapes(QStringList filepathlist);
    void drawAllShapes(QPainter* painter) const;
    void notify();
    void getDatabox(QVector<double>& databox) const;
    int getLayersSize() const;

private:
    ob::ShapesObCommand* _ob;
    QVector<RjpShape* > _mylayers;
    QVector<double> _databox;
    QStringList _pathlist;
};

}   // namespace drawpart
}   // namespace rjpshapefile



#endif // RJPSHAPES_H
