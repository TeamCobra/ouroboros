#ifndef _OUROBOROS_OBSERVER_H_
#define _OUROBOROS_OBSERVER_H_

#include <vector>

namespace ouroboros
{
	template <class observer>
	class subject
	{
	public:
		
		void registerObserver(const observer& mObserver)
		{
			mObservers.push_back(mObserver);
		}
		
		void notify() const
		{
			for (std::size_t i = 0; i < mObservers.size(); ++i)
			{
				mObservers[i]();
			}
		}
		
	private:
		std::vector<observer> mObservers;
	};
}

#endif//_OUROBOROS_OBSERVER_H_
