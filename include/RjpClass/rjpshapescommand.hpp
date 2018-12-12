#ifndef RJPSHAPESCOMMAND_HPP
#define RJPSHAPESCOMMAND_HPP

namespace rjpshapefile{
namespace obpart{

class ShapesObCommand{
public:
    virtual void execute() = 0;
protected:
    ShapesObCommand(){}
};

template<class Receiver>
class ShapesObCommandTemplate : public ShapesObCommand{
public:
    typedef void (Receiver::* Action)();
    ShapesObCommandTemplate(Receiver* r, Action a):
        _receiver(r),
        _action(a)
    {}
    virtual void execute();
private:
    Action _action;
    Receiver* _receiver;
};

template<class Receiver>
void ShapesObCommandTemplate<Receiver>::execute(){
    (_receiver->* _action)();
}


}   // namespace obpart
}   // namespace rjpshapefile





#endif // RJPSHAPESCOMMAND_HPP
