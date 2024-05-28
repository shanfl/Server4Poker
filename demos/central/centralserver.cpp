#include "centralserver.h"



void CentralServer::on_natspub_RegisterToCentral(Base::NatsClinetPtr nats,Base::Message&msg)
{

}

int main(int argc,char*argv[])
{
    CentralServer gs;

    bool ret =  gs.init(argc,argv);
}
