namespace MyList{

	template<typename T>
	template<typename TDest>
	LazyList<TDest> IEnumerable<T>::map(TDest(*func)(T)){
		// Return shared ptr to map enumerator wrapping func
		return LazyList<TDest>(
			std::shared_ptr<IEnumerator<TDest>>(new MapEnumerator<T, TDest>(this->getEnumerator(), func)));
	}

	template<typename T>
	LazyList<T> IEnumerable<T>::filter(bool(*predicate)(T)){
		// Return shared ptr to filter enumerator wrapping predicate
		return LazyList<T>(
			std::shared_ptr<IEnumerator<T>>(new FilterEnumerator<T>(this->getEnumerator(), predicate)));
	}

	template<typename T>
	template<typename TDest>
	TDest IEnumerable<T>::foldLeft(TDest initial, TDest(*func)(TDest, T)){
		// Need to enumerate over every value
		auto enumerator = getEnumerator();

		TDest accumulator = initial;
		while (enumerator->moveNext()){
			accumulator = func(accumulator, enumerator->getCurrent());
		}

		return accumulator;
	}
}