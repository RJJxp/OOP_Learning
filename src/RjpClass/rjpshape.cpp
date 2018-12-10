#include "include/RjpClass/rjpshape.h"

#include "QVector"

#include "include/shapelib/shapefil.h"

namespace rjpshapefile{
namespace drawpart{

// the details about how to realize this
// before this transform
// assume you have already know the relation between the 2 coordinate systems
QVector<double> RjpShape::data2Screen(QVector<double> coor,
                                      QPaintDevice *pic,
                                      QVector<double> displaybox){
    double pic_width = pic->width();
    double pic_height = pic->height();
    double x_scale = 1.1 * (displaybox[2] - displaybox[0]) / pic_width;
    double y_scale = 1.1 * (displaybox[3] - displaybox[1]) / pic_height;
    // To make sure every shape is on the pic
    // Pick up the larger one from x_scale and y_scale
    double final_scale = x_scale>y_scale?x_scale:y_scale;
    // translate the origin to the left&top corner
    // then translate more 0.05 of the displaybox
    // because we scale it by parameter 1.1
    double x = coor[0]; double y =coor[1];
    x = x - displaybox[0] + (displaybox[2] - displaybox[0]) * 0.05;
    y = y - displaybox[1] + (displaybox[3] - displaybox[1]) * 0.05;
    // scale them
    x = x / final_scale;
    y = y / final_scale;
    // reverse in y according to the coor systems relation
    y = pic_height - y;
    // translate according to x_scale and y_scale
    if (x_scale > y_scale){
        y = y - (pic_height / 2 - 1.1 * (displaybox[2] - displaybox[0]) / (2 * final_scale));
    }
    else{
        x = x + (pic_width / 2 - 1.1 * (displaybox[3] - displaybox[1]) / (2 * final_scale));
    }
}


void RjpPoint::drawShape(QPainter *painter, QVector<double> databox) const{

}

RjpShape* RjpPoint::clone(){

}

}   // namespace drawpart
}   // rjpshapefile

