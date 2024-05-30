#include "gateserver.h"

int main(int argc,char*argv[])
{
    std::shared_ptr<GateServer> gs = std::make_shared<GateServer>();

    bool ret =  gs->init(argc,argv);
    gs->run();

    return 0;
}
