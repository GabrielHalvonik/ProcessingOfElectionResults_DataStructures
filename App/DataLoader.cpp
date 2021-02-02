#include "DataLoader.h"

std::wifstream DataLoader::fin {};

void DataLoader::open(const std::string& file) {
	DataLoader::fin.open(file);
	DataLoader::fin.imbue(std::locale("zh_CN.UTF-8"));
//	if (DataLoader::fin.is_open()) {
//		std::wstring line;
//		std::getline(fin, line);
//	} else {
//		std::cerr << "Error, file " << file << " can not open.\n";
//	}
}

void DataLoader::close() {
	DataLoader::fin.close();
}

std::vector<std::wstring> DataLoader::splitLine(const std::wstring& line, size_t size, wchar_t del) {
	std::wistringstream sStream(line);
	std::vector<std::wstring> strs;
	std::wstring s;
	for (size_t i = 0; i < size; ++i) {
		std::getline(sStream, s, del);
		strs.push_back(s);
	}
	return strs;
}
