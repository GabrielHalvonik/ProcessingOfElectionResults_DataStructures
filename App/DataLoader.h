#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include <sstream>
#include "Data/DataAny.h"

class DataLoader {
public:
	static void open(const std::string&);
	static void close();

	template <typename ...Args>
	static bool loadData(Args&...);
private:
	DataLoader() = default;

	static std::vector<std::wstring> splitLine(const std::wstring&, size_t, wchar_t del);

private:
	static std::wifstream fin;
};

template<typename ...Args>
bool DataLoader::loadData(Args&...args) {
	if (DataLoader::fin.is_open() && !DataLoader::fin.eof()) {
		std::wstring line;
		std::getline(fin, line);
		fin >> std::ws;
//Structures::ArrayList<Data::Any> al = { &args... };
		std::vector<std::wstring> strs = DataLoader::splitLine(line, sizeof...(args), L'|');

		std::vector<Data::Any> params = { &args... };

		for (size_t i = 0; i < params.size(); ++i) {
			switch (params[i].getType()) {
				case Data::Type::WString : params[i] = strs[i]; break;
				case Data::Type::Integer : params[i] = std::stoi(strs[i]); break;
				case Data::Type::Double : params[i] = std::stod(strs[i]); break;
				case Data::Type::VoidPtr: break;
				default: break;
			}
		}
		return true;
	}
	return false;
}
