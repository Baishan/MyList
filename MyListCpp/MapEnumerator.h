/**
 *  Summary: Enumerator for lazily evaluating a collection with a mapping function.
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
		 * \brief Enumerator for lazily evaluating a collection with a mapping function.
		 * \tparam TSource Source type
		 * \tparam TOut Destination type
		 */
		template<class TSource, class TOut>
		class MapEnumerator : public IEnumerator < TOut >
		{
		public:
			/**
			 * \brief Instantiates new MapEnumerator from an input enumerator and map function.
			 * \param input Pointer to input enumerator.
			 * \param func Mapping function.
			 */
			MapEnumerator(const std::shared_ptr<IEnumerator<TSource> > & input, TOut(*func)(TSource)) : mFunc(func), mInputEnumerator(input){ }

			/**
			 * \brief Copy constructor
			 * \param other
			 */
			MapEnumerator(const MapEnumerator & other) {
				mFunc = other.mFunc;

				// Clone enumerator
				mInputEnumerator = other.mInputEnumerator->clone();
			}

			/**
			 * \brief Move enumerator to next position.
			 * \return False if at end of list, True otherwise
			 */
			bool moveNext() override
			{
				return mInputEnumerator->moveNext();
			}

			/**
			 * \brief Apply map function to current value
			 * \return Mapped value
			 */
			TOut getCurrent() override
			{
				return mFunc(mInputEnumerator->getCurrent());
			}

			/**
			 * \brief Clone this enumerator.
			 * \return New enumerator.
			 */
			std::shared_ptr<IEnumerator<TOut>> clone() override
			{
				return std::shared_ptr<IEnumerator<TOut> >(new MapEnumerator<TSource, TOut>(*this));
			}

		private:
			/**
			 * \brief Function pointer to map function.
			 */
			TOut(*mFunc)(TSource);

			/**
			 * \brief Enumerator to apply map to
			 */
			std::shared_ptr<IEnumerator<TSource>> mInputEnumerator;
		};
	}
}
