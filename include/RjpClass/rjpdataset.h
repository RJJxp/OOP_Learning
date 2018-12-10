#ifndef RJPDATASET_H
#define RJPDATASET_H

#include "include/shapelib/shapefil.h"

#include "QVector"
#include "QString"
#include "QColor"

namespace rjpshapefile{
namespace drawpart{

// Save the data of a shapefile
class RjpDataset{
public:
    RjpDataset(QString filepath);
    ~RjpDataset();
public:
    // Source data part, once initialized, fixed
    QString _filename;
    bool _is_show;
    SHPHandle _shp_header;
    SHPTree* _shp_tree;
    QVector<double> _databox;
    QColor _paintcolor;
    // Smart pointer data part
    int _refcount;
};

// Smart pointer, Contain RjpDataset
class RjpDatasetPtr{
public:
    RjpDatasetPtr(QString filepath);    // 3 construct
    RjpDatasetPtr(RjpDataset * value);
    RjpDatasetPtr(const RjpDatasetPtr& rhs);
    RjpDatasetPtr& operator = (const RjpDatasetPtr& rhs);   // overload of string =
    RjpDataset* getValue() const;
private:
    RjpDataset* _value;
};

}   // namespace drawpart
}   // namespace rjpshapefile
#endif // RJPDATASET_H
