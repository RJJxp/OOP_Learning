#ifndef RJPFACTORY_H
#define RJPFACTORY_H

#include "QString"

#include "include/RjpClass/rjpshape.h"

namespace rjpshapefile{
namespace drawpart{

class RjpFactory
{
public:
    virtual ~RjpFactory(){}
    virtual RjpShape* createShape(QString filepath) = 0;
    static RjpFactory* getInstance();
protected:
    RjpFactory(){}
    static RjpFactory* _instance;

};

// Usage
// ESRIFactory::getInstance->createShape(filepath)
// the variable 'static RjpFactory* _instance'
// becomes ESRIFactory
class ESRIFactory : public RjpFactory{
public:
    ESRIFactory(){}
    virtual ~ESRIFactory(){}
    virtual RjpShape* createShape(QString filepath);
};

class StaticFactory{
public:
    static RjpShape* createShape(QString filepath);
};

}   // namespace drawpart
}   // namespace rjpshapefile


#endif // RJPFACTORY_H
