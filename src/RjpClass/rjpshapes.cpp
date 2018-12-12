#include "include/RjpClass/rjpshapes.h"

#include "QVector"
#include "QString"
#include "QPainter"


namespace rjpshapefile{
namespace drawpart{

RjpShapes::~RjpShapes(){
    delete _ob;
    _mylayers.clear();
    _databox.clear();
}

RjpShapes::RjpShapes(){
    _databox.clear();
}

RjpShapes::RjpShapes(obpart::ShapesObCommand* obc){
    _databox.clear();
    _ob = obc;
}

RjpShapes::RjpShapes(RjpShapes* shapes){
    _databox.clear();
    QVector<double> databox;
    shapes->getDatabox(databox);
    _databox.push_back(shapes->);
}

void RjpShapes::getDatabox(QVector<double> &databox) const{
    databox = _databox;
}

}   // namespace drawpart
}   // namespace rjpshapefile



