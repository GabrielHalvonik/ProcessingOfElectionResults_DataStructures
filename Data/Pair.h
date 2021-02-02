#pragma once

namespace Structures {
	template <typename F, typename S>
	class Pair {
	public:
		Pair(F f, S s) : first(f), second(s) {}

		F first;
		S second;

		bool operator==(const Pair&);
		void operator+=(const Pair&);
	};

	template<typename F, typename S>
	bool Pair<F, S>::operator==(const Pair& second) {
		return this->first == second.first && this->second == second.second;
	}

	template<typename F, typename S>
	void Pair<F, S>::operator+=(const Pair& second) {
		this->first += second.first;
		this->second += second.second;
	}

}
