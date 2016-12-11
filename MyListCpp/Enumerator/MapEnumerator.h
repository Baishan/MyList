#pragma once
#include "IEnumerator.h"
#include <functional>

namespace MyList
{
	namespace Enumerator
	{
		template<class TSource, class TOut>
		class MapEnumerator : public IEnumerator < TOut >
		{
		private:
			TOut(*mFunc)(TSource);

			std::shared_ptr<IEnumerator<TSource>> mInputEnumerator;

		public:
			MapEnumerator(const std::shared_ptr<IEnumerator<TSource> > & input, TOut(*func)(TSource)) : mFunc(func), mInputEnumerator(input){ }

			MapEnumerator(const MapEnumerator & other) {
				mFunc = other.mFunc;
				mInputEnumerator = other.mInputEnumerator->clone();
			}

			bool moveNext(){
				return mInputEnumerator->moveNext();
			}

			TOut getCurrent(){
				return mFunc(mInputEnumerator->getCurrent());
			}

			std::shared_ptr<IEnumerator<TOut>> clone(){
				return std::shared_ptr<IEnumerator<TOut> >(new MapEnumerator<TSource, TOut>(*this));
			}
		};
	}
}
