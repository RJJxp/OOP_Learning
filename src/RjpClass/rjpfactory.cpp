#include "include/RjpClass/rjpfactory.h"

#include "QVector"
#include "QString"

#include "include/RjpClass/rjpshape.h"

namespace rjpshapefile{
namespace drawpart{

// initialize the static variable
RjpFactory* RjpFactory::_instance = NULL;

RjpFactory* RjpFactory::getInstance(){
    if (_instance == NULL)
        _instance = new ESRIFactory();
    return _instance;
}

RjpShape* ESRIFactory::createShape(QString filepath){
    return StaticFactory::createShape(filepath);
}

RjpShape* StaticFactory::createShape(QString filepath){
    RjpDatasetPtr datasetptr(filepath);
    int shape_type = datasetptr.getValue()->_shp_header->nShapeType;
    switch (shape_type){
    case 1:
    case 11:
    case 21:{
        return new RjpPoint(datasetptr);
        break;
    }   // case 1,11,21
    case 3:
    case 13:
    case 23:{
        return new RjpPolyline(datasetptr);
        break;
    }   // case 3,13,23
    case 5:
    case 15:
    case 25:{
        return new RjpPolygon(datasetptr);
        break;
    }   // case 5,15,25
    }   // switch
}

}   // namespace rjpshapefile
}   // namespace drawpart
