#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <string>

using std::unique_ptr;
using std::map;

template<typename T>
class Factory {

public:
	//the pointer to the function that creates the object
	using creationFunc = unique_ptr<T>(*)();

	//register a pair of char+creator function into the map:
	static bool registerit(const char& name, creationFunc f) {
		getMap().emplace(name, f);
		return true;
	}

	//creates the objects according to the char that represents it
	//(searches this char in the map):
	static unique_ptr<T> create(const char& name) {
		const auto& map = getMap();
		auto it = map.find(name);
		if (it == map.end())
			return nullptr;
		return it->second();
	}

private:
	static auto& getMap() {
		static map<char, creationFunc> map;
		return map;
	}
};

