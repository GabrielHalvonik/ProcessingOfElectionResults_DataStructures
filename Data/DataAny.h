#pragma once

#include <string>
#include "App/UzemnaJednotka.h"
#include "App/PolitickySubjekt.h"

inline const void* empty = nullptr;

namespace Data {


	union Data {
		int* Integer;
		double* Double;
		std::wstring* WString;
		void* VoidPtr;
	};

	enum Type {
		Integer,
		Double,
		WString,
		VoidPtr
	};

	class Any {
	public:
		Any(void*);
		Any(int*);
		Any(double*);
		Any(std::wstring*);

		Any& operator=(int);
		Any& operator=(double);
		Any& operator=(std::wstring&);

		Type getType() const;

	private:
		Data data;
		Type type;
	};

}
