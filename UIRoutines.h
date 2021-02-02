#pragma once

#include <string>
#include "App/TypUzemnejJednotky.h"

class UIRoutines {
public:
	static std::wstring getNazov(const TypUzemnejJednotky);
	static std::wstring getNazov(const TypyKriterii);
	static std::wstring getNazov(const DruhyFiltrov);
private:
	UIRoutines() = default;
};

