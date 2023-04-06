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
	using pFnc = unique_ptr<T>(*)(); 
	static bool registerit(const char& name, pFnc);
	static unique_ptr<T> create(const char& name);

private:
	static auto& getMap() {
		static map<char, pFnc> map;
		return map;
	}

};

//register a pair of char+creator function into the map:
template<typename T>
bool Factory<T>::registerit(const char& name, pFnc f) {
	Factory::getMap().emplace(name, f);
	return true;
}

//creates the objects according to the char that represents it
//(searches this char in the map):
template<typename T>
unique_ptr<T> Factory<T>::create(const char& name) {
	auto it = Factory::getMap().find(name);
	if (it == Factory::getMap().end())
		return nullptr;
	return it->second();
}

