#pragma once
#include "toml.h"
namespace TomlHelper
{
	template<class T>
    T TGet(const toml::Value& root, std::string tableName, std::string key, T v = T()) {
		const toml::Value* table = root.find(tableName);
		if (!table) return v;
		const toml::Value* keyValue = table->find(key);
		if (!keyValue) return v;
		return keyValue->as<T>();
	}
}
