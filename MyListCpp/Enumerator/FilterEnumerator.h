#pragma once

#include "IEnumerator.h"
namespace MyList
{
	namespace Enumerator
	{
		template<class TSource>
		class FilterEnumerator : public IEnumerator < TSource >
		{
		private:
			bool(*mPredicate)(TSource);

			std::shared_ptr<IEnumerator<TSource>> mInputEnumerator;

		public:
			FilterEnumerator(const std::shared_ptr<IEnumerator<TSource> > & input, bool(*predicate)(TSource)) : mPredicate(predicate), mInputEnumerator(input){ }
			FilterEnumerator(const FilterEnumerator & other){
				mPredicate = other.mPredicate;
				mInputEnumerator = other.mInputEnumerator->clone();
			}

			bool moveNext(){
				bool hasValue = false;
				while ((hasValue = mInputEnumerator->moveNext()) && !mPredicate(mInputEnumerator->getCurrent()));
				return hasValue;
			}

			TSource getCurrent(){
				return mInputEnumerator->getCurrent();
			}

			std::shared_ptr<IEnumerator<TSource>> clone(){
				return std::shared_ptr<IEnumerator<TSource>>(new FilterEnumerator(*this));
			}
		};
	}
}