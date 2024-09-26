#pragma once
#include "tinytoml/toml.h"
namespace TomlHelper
{
    bool Has(const toml::Value&root,std::string name){
        const toml::Value* table = root.find(name);
        return table != nullptr;
    }

	template<class T>
    T TGet(const toml::Value& root, std::string tableName, std::string key, T v = T()) {
		const toml::Value* table = root.find(tableName);
		if (!table) return v;
		const toml::Value* keyValue = table->find(key);
		if (!keyValue) return v;
		return keyValue->as<T>();
	}

    int ArrayGetCnt(const toml::Value&root,std::string tableName){
        const toml::Value* table = root.find(tableName);
        if (!table) return 0;
        const toml::Array arryValue = table->as<toml::Array>();
        return arryValue.size();
    }

    template <typename T>
    T ArrayGet(const toml::Value&root,std::string arryname,int index,std::string key,T v = T()){
        const toml::Value* table = root.find(arryname);
        if (!table) return v;
        const toml::Array arryValue = table->as<toml::Array>();

        if(arryValue.size() <= index ) return v;

        const toml::Value* vtoml = arryValue.at(index).find(key);
        if(!vtoml) return v;
        return vtoml->as<T>();
    }



    template<typename T>
    T SubKeyArrayGet(const toml::Value&root,std::string key,std::string subkey){
        const toml::Value* table = root.find(key);
        if (!table) return T();

        const toml::Value*subkeyPtr = table->find(subkey);
        if(!subkeyPtr) return T();
        return subkeyPtr->as<T>();
    }

#if 0
    template <typename T>
    std::vector<T> ArrayGetVec(const toml::Value&root,std::string arryname,int index,std::string key,std::vector<T> v = std::vector<T>()){
        const toml::Value* table = root.find(arryname);
        if (!table) return v;
        const toml::Array arryValue = table->as<toml::Array>();

        if(arryValue.size() <= index ) return v;

        const toml::Value* vtoml = arryValue.at(index).find(key);
        if(!vtoml)
            return v;
        const toml::Array arryKey = vtoml->as<toml::Array>();
        std::vector<T> ret;
        for(auto&t:arryKey){
            ret.push_back(t.as<T>());
        }
        return ret;
    }
#endif
}
