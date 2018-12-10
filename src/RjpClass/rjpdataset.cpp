#include "include/RjpClass/rjpdataset.h"

#include "QVector"
#include "QString"
#include "QFileInfo"

#include "include/shapelib/shapefil.h"

namespace rjpshapefile {
namespace drawpart{

// Use function in shapefil.h
RjpDataset::RjpDataset(QString filepath){
    // Set the smart pointer reference count
    _refcount = 0;
    // Set header and tree
    _shp_header = SHPOpen(filepath.toStdString().c_str(),"rb+");
    _shp_tree = SHPCreateTree(_shp_header,2,10,NULL,NULL);
    SHPTreeTrimExtraNodes(_shp_tree);
    // Set name
    QFileInfo fi(filepath);
    _filename = fi.baseName();
    // Set databox
    _databox.push_back(_shp_header->adBoundsMin[0]);
    _databox.push_back(_shp_header->adBoundsMin[1]);
    _databox.push_back(_shp_header->adBoundsMax[0]);
    _databox.push_back(_shp_header->adBoundsMax[1]);
    _is_show = true;    // Show and color
    _paintcolor.setRgb(qrand()%255,qrand()%255,qrand()%255);
}

RjpDataset::~RjpDataset(){
    delete _shp_header;
    delete _shp_tree;
}

RjpDataset* RjpDatasetPtr::getValue() const{
    return _value;
}

// 3 constructor
RjpDatasetPtr::RjpDatasetPtr(QString filepath){
    _value = new RjpDataset(filepath);
    _value->_refcount++;
}

RjpDatasetPtr::RjpDatasetPtr(RjpDataset* value){
    _value = value;
    _value->_refcount++;
}

RjpDatasetPtr::RjpDatasetPtr(const RjpDatasetPtr &rhs){
    this->_value = rhs.getValue();
    _value->_refcount++;
}

// Here we can see, the reference '&' actually is a address
// 'this' is left hand side, rhs means right hand side
// 'this' is a object, so what we return is a '*this'
RjpDatasetPtr& RjpDatasetPtr::operator = (const RjpDatasetPtr& rhs){
    if (this == &rhs){
        return *this;
    }
    if (--_value->_refcount == 0){
        delete _value;
    }
    _value = rhs.getValue();
    _value->_refcount++;

    return *this;
}

}   // namespace drawpart
}   // namespace rjpshapefile

