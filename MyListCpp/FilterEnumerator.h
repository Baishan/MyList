/**
 *  Summary: Enumerator for lazily evaluating a filter. Wraps existing enumerator returning only items that satisfy the filter.
 *  Author: Brian Cullen (brianshan@gmail.com)
 */

#pragma once

#include <memory>
#include "Enumerator/IEnumerator.h"

namespace MyList
{
	namespace Enumerator
	{
		/**
		 * \brief Enumerator for lazily evaluating a filter.
		 * \tparam TSource 
		 */
		template<class TSource>
		class FilterEnumerator : public IEnumerator < TSource >
		{
		public:
			/**
			 * \brief Instantiates a new FilterEnumerator from an input enumerator and predicate
			 * \param input Pointer to input enumerator
			 * \param predicate Filter function
			 */
			FilterEnumerator(const std::shared_ptr<IEnumerator<TSource> > & input, bool(*predicate)(TSource)) : mPredicate(predicate), mInputEnumerator(input){ }

			/**
			 * \brief Copy constructor
			 * \param other FilterEnumerator
			 */
			FilterEnumerator(const FilterEnumerator & other){
				mPredicate = other.mPredicate;
				mInputEnumerator = other.mInputEnumerator->clone();
			}

			/**
			 * \brief Move enumerator to next position in collection that satisfies the filter.
			 * \return False if enumerator at end of collection, True otherwise.
			 */
			bool moveNext() override
			{
				bool hasValue = false;
				while ((hasValue = mInputEnumerator->moveNext()) && !mPredicate(mInputEnumerator->getCurrent()));
				return hasValue;
			}

			/**
			 * \brief Gets the current value pointed to.
			 * \return Value
			 */
			TSource getCurrent() override
			{
				return mInputEnumerator->getCurrent();
			}

			/**
			 * \brief Clones this enumerator by invoking copy constructor.
			 * \return std::shared_ptr<IEnumerator<TSource>
			 */
			std::shared_ptr<IEnumerator<TSource>> clone() override
			{
				return std::shared_ptr<IEnumerator<TSource>>(new FilterEnumerator(*this));
			}

		private:
			/**
			 * \brief Predicate filter function
			 */
			bool(*mPredicate)(TSource);

			std::shared_ptr<IEnumerator<TSource>> mInputEnumerator;
		};
	}
}
