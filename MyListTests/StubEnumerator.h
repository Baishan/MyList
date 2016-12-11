#pragma once
#include "../MyListCpp/Enumerator/IEnumerator.h"

using namespace MyList::Enumerator;
namespace MyListTests
{
	template<typename T>
	class StubEnumerator : public IEnumerator < T >
	{
	public:
		bool moveReturnValue;
		T getCurrentReturnValue;
		StubEnumerator(bool moveReturnValue, T currentValue) : moveReturnValue(moveReturnValue), getCurrentReturnValue(currentValue){}
		bool moveNext() override { return moveReturnValue; }
		T getCurrent() override { return getCurrentReturnValue; };
		std::shared_ptr<IEnumerator<int>> clone() override { return std::shared_ptr<IEnumerator<T>>(this); }
	};
}
