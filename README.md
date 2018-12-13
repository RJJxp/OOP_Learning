# 2018年12月09日18:06:41

一下午都在看老张以前的代码和我自己写的代码

毕竟要重写一遍

需要注意的有

- 变量的命名问题: 类, 函数, 变量的命名......
- 留白问题: 指针类型变量定义的留白, 函数的大括号......
- 命名空间的使用

2018年12月13日11:00 完成代码的重写

---

# 问题

- 工厂设计模式的继承

  ```c++
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
  ```

  `ESRIFactory` 继承 `RjpFatory` 

  但是用的时候是

  `ESRIFactory::getInstance::createShape(QString filepath)` 

  `getInstance` 返回的`_instance` 可以调用 `createShape` 

  说明不是虚函数, 它的返回值是一个子类

  但它的定义是一个父类

  难道C++的继承这么神奇的吗???