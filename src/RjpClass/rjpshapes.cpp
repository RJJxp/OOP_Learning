#include "include/RjpClass/rjpshapes.h"

#include "QVector"
#include "QString"
#include "QPainter"
#include "QFileInfo"

#include "include/RjpClass/rjpshape.h"
#include "include/RjpClass/rjpfactory.h"

namespace rjpshapefile{
namespace drawpart{

RjpShapes::~RjpShapes(){
    delete _ob;
    _mylayers.clear();
    _shps_databox.clear();
}

RjpShapes::RjpShapes(){
    _shps_databox.clear();
}

RjpShapes::RjpShapes(obpart::ShapesObCommand* obc){
    _shps_databox.clear();
    _ob = obc;
}

RjpShapes::RjpShapes(RjpShapes* shapes){
    // databox
    this->_shps_databox.clear();
    QVector<double> databox;
    shapes->getDatabox(databox);
    this->_shps_databox.push_back(databox[0]);
    this->_shps_databox.push_back(databox[1]);
    this->_shps_databox.push_back(databox[2]);
    this->_shps_databox.push_back(databox[3]);
    // mylayer
    this->_mylayers.clear();
    for (int i = 0; i < shapes->getLayersSize(); i++){
        // Attention: here we need DEEP COPY
        this->_mylayers.push_back(shapes->at(i)->clone());
    }
    // path list
    this->_pathlist = shapes->getPathList();
    // ob
    this->_ob = shapes->getOb();
}

void RjpShapes::setOb(obpart::ShapesObCommand *ob){
    _ob = ob;
}

void RjpShapes::addShapes(QStringList filepathlist){
    // _pathlist and _mylayers(shapes)
    int old_path_length = _pathlist.size();
    _pathlist.append(filepathlist);
    int new_path_length = _pathlist.size();
    for (int i = old_path_length; i < new_path_length; i++){
        QFileInfo fi(_pathlist[i]);
        if (!fi.isFile())
            continue;
        QString filepath = _pathlist[i];
        _mylayers.push_back(ESRIFactory::getInstance()->createShape(filepath));
    }
    // _databox
    _shps_databox.clear();
    for (int i = 0; i < new_path_length; i++){
        if (i == 0){
            this->_shps_databox.push_back(
                        _mylayers[i]->getDatasetPtr().getValue()->_databox[0]);
            this->_shps_databox.push_back(
                        _mylayers[i]->getDatasetPtr().getValue()->_databox[1]);
            this->_shps_databox.push_back(
                        _mylayers[i]->getDatasetPtr().getValue()->_databox[2]);
            this->_shps_databox.push_back(
                        _mylayers[i]->getDatasetPtr().getValue()->_databox[3]);
        }   // if
        else{
            if (_mylayers[i]->getDatasetPtr().getValue()->_databox[0] <
                    this->_shps_databox[0])
                this->_shps_databox[0] = _mylayers[i]->getDatasetPtr().getValue()->_databox[0];
            if (_mylayers[i]->getDatasetPtr().getValue()->_databox[1] <
                    this->_shps_databox[1])
                this->_shps_databox[1] = _mylayers[i]->getDatasetPtr().getValue()->_databox[1];
            if (_mylayers[i]->getDatasetPtr().getValue()->_databox[2] >
                    this->_shps_databox[2])
                this->_shps_databox[2] = _mylayers[i]->getDatasetPtr().getValue()->_databox[2];
            if (_mylayers[i]->getDatasetPtr().getValue()->_databox[3] >
                    this->_shps_databox[3])
                this->_shps_databox[3] = _mylayers[i]->getDatasetPtr().getValue()->_databox[3];
        }   // else
    }   // for
}

void RjpShapes::drawAllShapes(QPainter *painter) const{
    if (_mylayers.size() == 0)
        return;

    for (int i = 0; i < _mylayers.size(); i++){
        painter->setPen(_mylayers[i]->getDatasetPtr().getValue()->_paintcolor);
        _mylayers[i]->drawShape(painter, _shps_databox);
    }
}

ob::ShapesObCommand* RjpShapes::getOb() const{
    return _ob;
}

int RjpShapes::getLayersSize() const{
    return _mylayers.size();
}

QStringList RjpShapes::getPathList() const{
    return _pathlist;
}

RjpShape* RjpShapes::at(int i) const{
    if (i < 0 || i > (_mylayers.size()-1))
        return NULL;
    return _mylayers[i];
}

void RjpShapes::getDatabox(QVector<double> &databox) const{
    databox = _shps_databox;
}

void RjpShapes::notify(){
    _ob->execute();
}

RjpShapes* SingletonShapes::_global_data = NULL;

RjpShapes* SingletonShapes::getGlobalData(){
    if (!_global_data){
        _global_data = new RjpShapes();
    }
    return _global_data;
}

void SingletonShapes::releaseGlobalData(){
    if(_global_data)
        delete _global_data;
}

}   // namespace drawpart
}   // namespace rjpshapefile



