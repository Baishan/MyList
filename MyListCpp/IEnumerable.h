/**
 *  Summary: Interface that represents an enumerable list of items.
 *  Author: Brian Cullen (brianshan@gmail.com)
 */

#pragma once
#include<memory>

#include "ImmutableList.h"
#include "MutableList.h"
#include "LazyList.h"

#include "Enumerator/FilterEnumerator.h"
#include "Enumerator/IEnumerator.h"
#include "Enumerator/MapEnumerator.h"

namespace MyList{

	template <typename T>
	class ImmutableList;

	template <typename T>
	class MutableList;

	/**
	 * \brief Interface that represents an enumerable list of items.
	 * \tparam T Type of item in list.
	 */
	template<class T>
	class IEnumerable
	{
	public:
		/**
		 * \brief Get enumerator
		 * \return std::shared_ptr<IEnumerator<T> >
		 */
		virtual std::shared_ptr<IEnumerator<T> > getEnumerator() const = 0;

		/**
		 * \brief Map this list to another
		 * \tparam TDest Type of item destination list
		 * \param func Map function
		 * \return LazyList of mapped values.
		 */
		template<typename TDest>
		LazyList<TDest> map(TDest(*func)(T));

		/**
		 * \brief Filter list
		 * \param predicate Predicate used to filter items
		 * \return LazyList of filtered values.
		 */
		LazyList<T> filter(bool(*predicate)(T));

		/**
		 * \brief Aggregate values in the list.
		 * \tparam TDest Aggregate value type
		 * \param initial Initial value
		 * \param func Aggregate function
		 * \return Aggregate value
		 */
		template<typename TDest>
		TDest foldLeft(TDest initial, TDest(*func)(TDest, T));

		/**
		 * \brief Convert list to a new ImmutableList. Forces evalutation for the entire list.
		 * \return new ImmutableList
		 */
		ImmutableList<T> toImmutableList(){
			return ImmutableList<T>(this);
		}

		/**
		* \brief Convert list to a new ImmutableList. Forces evalutation for the entire list.
		* \return new ImmutableList
		*/
		MutableList<T> toMutableList(){
			return MutableList<T>(this);
		}

		/**
		 * \brief Destructor
		 */
		virtual ~IEnumerable()
		{
		}
	};
}

#include "IEnumerable.tpp"
