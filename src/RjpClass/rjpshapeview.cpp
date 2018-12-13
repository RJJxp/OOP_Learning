#include "include/RjpClass/rjpshapeview.h"

#include "QPaintDevice"

#include "include/RjpClass/rjpshapes.h"

namespace drawp = rjpshapefile::drawpart;

RjpShapeView::RjpShapeView(QWidget *parent) : QWidget(parent){

}

void RjpShapeView::paintEvent(QPaintEvent* event){
    QPainter* painter = new QPainter(this);
    painter->begin(this);
    drawp::SingletonShapes::getGlobalData()->drawAllShapes(painter);
    painter->end();
}
