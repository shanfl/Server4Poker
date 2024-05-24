#include "../toml/TomlHelper.h"
#include <iostream>
int main()
{
    std::string fullpath = "/media/shanfl/KINGSTON/Server4Poker/demo.toml";
    std::ifstream ifs(fullpath);
    toml::ParseResult pr = toml::parse(ifs);

    if(!pr.valid()) {
        std::clog << "parser toml:" << fullpath << "failed,reason:" << pr.errorReason << std::endl;
        return false;
    }

    int n = TomlHelper::ArrayGetCnt(pr.value,"nats");

    for(int i = 0;i < n ;i++){
        std::string name = TomlHelper::ArrayGet(pr.value,"nats",i,"name",std::to_string(i));
        std::clog << "name:" << name << std::endl;

        std::vector<std::string> v = TomlHelper::ArrayGetVec(pr.value,"nats",i,"subs",std::vector<std::string>());
        for(int i = 0;i < v.size();i++){
            std::clog << v[i] << std::endl;
        }

        //
        v = TomlHelper::ArrayGet(pr.value,"nats",i,"subs",std::vector<std::string>());
        for(int i = 0;i < v.size();i++){
            std::clog << v[i] << std::endl;
        }
    }
}
