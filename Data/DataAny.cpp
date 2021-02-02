#include "DataAny.h"

namespace Data {

	Any::Any(void* par) {
		this->data.VoidPtr = par;
		this->type = Type::VoidPtr;
	}

	Any::Any(int* par) {
		this->data.Integer = par;
		this->type = Type::Integer;
	}

	Any::Any(double* par) {
		this->data.Double = par;
		this->type = Type::Double;
	}

	Any::Any(std::wstring* par) {
		this->data.WString = par;
		this->type = Type::WString;
	}

	Any& Any::operator=(int par) {
		*this->data.Integer = par;
		return *this;
	}

	Any& Any::operator=(double par) {
		*this->data.Double = par;
		return *this;
	}

	Any& Any::operator=(std::wstring& par) {
		*this->data.WString = par;
		return *this;
	}

	Type Any::getType() const {
		return this->type;
	}

}
