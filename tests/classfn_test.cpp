#include <string>
#include <iostream>
#include <vector>
#include <functional>
class Session
{
    public:
    std::string name;
};

class Message
{
    public:
    std::string name;
};

class BaseClass;
using MEMFN = std::function<void(Session*s,Message*m)>;
struct container
{
    MEMFN fn;
};

class BaseClass
{
public:

    BaseClass(){
        G_FN.push_back(container{std::bind(&BaseClass::hello,this,std::placeholders::_1,std::placeholders::_2)});
        G_FN.push_back(container{&BaseClass::hi});
    }

    void hello(Session*s,Message*msg) {
        std::cout << "BaseClass-hello" << std::endl;
    }

    void hi(Session*s,Message*msg) {
        std::cout << "BaseClass-hi" << std::endl;
    }

    std::vector<container> G_FN;
};

class P1:public BaseClass
{

    P1(){
        G_FN.push_back(container{&P1::hello1});
        G_FN.push_back(container{&P1::hi1});
    }

public:

    void hello1(Session*s,Message*msg) {
        std::cout << "P1-hello1" << std::endl;
    }

    void hi1(Session*s,Message*msg) {
        std::cout << "P1-hi1" << std::endl;
    }

};


int main(){

    BaseClass cls;

    return 0;
}   


