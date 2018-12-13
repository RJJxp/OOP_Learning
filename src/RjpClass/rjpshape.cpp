#include "include/RjpClass/rjpshape.h"

#include "QVector"
#include "QPaintDevice"

#include "include/shapelib/shapefil.h"

namespace rjpshapefile{
namespace drawpart{

RjpShape* RjpShape::clone(){
    RjpDatasetPtr tem_datasetptr(_datasetPtr);
    int tem_shapetype = tem_datasetptr.getValue()->_shp_header->nShapeType;
    switch (tem_shapetype){
    case 1:
    case 11:
    case 21:{
        return new RjpPoint(tem_datasetptr);
        break;
    }
    case 3:
    case 13:
    case 23:{
        return new RjpPolyline(tem_datasetptr);
        break;
    }
    case 5:
    case 15:
    case 25:{
        return new RjpPolygon(tem_datasetptr);
        break;
    }
    default:{
        return NULL;
        break;
    }

    }   // swtich
}   // function

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
        y = y - (pic_height / 2 - 1.1 * (displaybox[3] - displaybox[1]) / (2 * final_scale));
    }
    else{
        x = x + (pic_width / 2 - 1.1 * (displaybox[2] - displaybox[0]) / (2 * final_scale));
    }
    QVector<double> re;
    re.append(x);
    re.append(y);
    return re;
}


void RjpPoint::drawShape(QPainter* painter, QVector<double> databox) {
    if (_datasetPtr.getValue()->_is_show == false)
        return;
    // Build the display minbox and maxbox for the tree and drawing
    double display_minbox[4];
    double display_maxbox[4];
    display_minbox[0] = databox[0];
    display_minbox[1] = databox[1];
    display_minbox[2] = 0;
    display_minbox[3] = 0;
    display_maxbox[0] = databox[2];
    display_maxbox[1] = databox[3];
    display_maxbox[2] = 0;
    display_maxbox[3] = 0;
    // Use func in shapelib.h to search the obj in the displaybox
    int* record_hit_list = NULL;
    int record_hit_count;
    record_hit_list = SHPTreeFindLikelyShapes(_datasetPtr.getValue()->_shp_tree,
                                              display_minbox,
                                              display_maxbox,
                                              &record_hit_count);
    QPaintDevice* pic = painter->device();
    // define the variable outta the 'for' cycle
    // to make code more effcient
    SHPObject* shp_content = NULL;
    QVector<double> old_coor(2,0);
    double x,y; // TODO: run twice data2Screen, low effciency
    for (int i = 0; i < record_hit_count; i++){
        shp_content = SHPReadObject(_datasetPtr.getValue()->_shp_header,
                                    record_hit_list[i]);
        old_coor[0] = shp_content->padfX[0];
        old_coor[1] = shp_content->padfY[0];
        x = data2Screen(old_coor, pic, databox)[0];
        y = data2Screen(old_coor, pic, databox)[1];
        painter->drawLine(QPointF(x-2,y), QPointF(x+2,y));
        painter->drawLine(QPointF(x,y-2), QPointF(x,y+2));
    }
    // TODO: does 2 sentences really work?
    SHPDestroyObject(shp_content);
    shp_content = NULL;
}

void RjpPolyline::drawShape(QPainter *painter, QVector<double> databox) {
    if (_datasetPtr.getValue()->_is_show == false)
        return;
    // Build the display minbox and maxbox for the tree and drawing
    double display_minbox[4];
    double display_maxbox[4];
    display_minbox[0] = databox[0];
    display_minbox[1] = databox[1];
    display_minbox[2] = 0;
    display_minbox[3] = 0;
    display_maxbox[0] = databox[2];
    display_maxbox[1] = databox[3];
    display_maxbox[2] = 0;
    display_maxbox[3] = 0;
    // Use func in shapelib.h to search the obj in the displaybox
    int* record_hit_list = NULL;
    int record_hit_count;
    record_hit_list = SHPTreeFindLikelyShapes(_datasetPtr.getValue()->_shp_tree,
                                              display_minbox,
                                              display_maxbox,
                                              &record_hit_count);
    QPaintDevice* pic = painter->device();
    // define the variable outta the 'for' cycle
    // to make code more effcient
    SHPObject* shp_content = NULL;
    QVector<double> old_coor(2,0);
    double x,y;
    for (int i = 0; i < record_hit_count; i++){
        shp_content = SHPReadObject(_datasetPtr.getValue()->_shp_header,
                                    record_hit_list[i]);
        // Build the part array
        QVector<int> new_parts;
        for (int j = 0; j < shp_content->nParts; j++)
            new_parts.append(shp_content->panPartStart[j]);
        new_parts.append(shp_content->nVertices);
        // Start to draw
        for (int j = 0; j < new_parts.size() - 1; j++){
            int point_count = new_parts[j+1] - new_parts[j];
            QPointF* point_pair = new QPointF[point_count];
            for (int k = new_parts[j]; k < new_parts[j+1]; k++){
                old_coor[0] = shp_content->padfX[k];
                old_coor[1] = shp_content->padfY[k];
                x = data2Screen(old_coor, pic, databox)[0];
                y = data2Screen(old_coor, pic, databox)[1];
                point_pair[k - new_parts[j]].setX(x);
                point_pair[k - new_parts[j]].setY(y);
            }   // for loop k
            painter->drawLines(point_pair, point_count/2 - 1);
            delete point_pair;
            point_pair = NULL;
        }   // for loop j
        SHPDestroyObject(shp_content);
        shp_content = NULL;
    }   // for loop i
}

// The only difference between drawing polyline and polygon
// is the draw function, only one sentence is different
void RjpPolygon::drawShape(QPainter *painter, QVector<double> databox) {
    if (_datasetPtr.getValue()->_is_show == false)
        return;
    // Build the display minbox and maxbox for the tree and drawing
    double display_minbox[4];
    double display_maxbox[4];
    display_minbox[0] = databox[0];
    display_minbox[1] = databox[1];
    display_minbox[2] = 0;
    display_minbox[3] = 0;
    display_maxbox[0] = databox[2];
    display_maxbox[1] = databox[3];
    display_maxbox[2] = 0;
    display_maxbox[3] = 0;
    // Use func in shapelib.h to search the obj in the displaybox
    int* record_hit_list = NULL;
    int record_hit_count;
    record_hit_list = SHPTreeFindLikelyShapes(_datasetPtr.getValue()->_shp_tree,
                                              display_minbox,
                                              display_maxbox,
                                              &record_hit_count);
    QPaintDevice* pic = painter->device();
    // define the variable outta the 'for' cycle
    // to make code more effcient
    SHPObject* shp_content = NULL;
    QVector<double> old_coor(2,0);
    double x,y;
    for (int i = 0; i < record_hit_count; i++){
        shp_content = SHPReadObject(_datasetPtr.getValue()->_shp_header,
                                    record_hit_list[i]);
        // Build the part array
        QVector<int> new_parts;
        for (int j = 0; j < shp_content->nParts; j++)
            new_parts.append(shp_content->panPartStart[j]);
        new_parts.append(shp_content->nVertices);
        // Start to draw
        for (int j = 0; j < new_parts.size() - 1; j++){
            int point_count = new_parts[j+1] - new_parts[j];
            QPointF* point_pair = new QPointF[point_count];
            for (int k = new_parts[j]; k < new_parts[j+1]; k++){
                old_coor[0] = shp_content->padfX[k];
                old_coor[1] = shp_content->padfY[k];
                x = data2Screen(old_coor, pic, databox)[0];
                y = data2Screen(old_coor, pic, databox)[1];
                point_pair[k - new_parts[j]].setX(x);
                point_pair[k - new_parts[j]].setY(y);
            }   // for loop k
            painter->drawPolygon(point_pair,point_count);
            delete point_pair;
            point_pair = NULL;
        }   // for loop j
        SHPDestroyObject(shp_content);
        shp_content = NULL;
    }   // for loop i
}

}   // namespace drawpart
}   // rjpshapefile

