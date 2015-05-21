namespace ouroboros
{
	template <class Observer>
	void subject<Observer>::registerObserver(const Observer& aObserver)
	{
		mObservers.push_back(aObserver);
	}

	template <class Observer>
	void subject<Observer>::notify() const
	{
		for (std::size_t i = 0; i < mObservers.size(); ++i)
		{
			mObservers[i]();
		}
	}
}
