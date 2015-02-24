#ifndef _OUROBOROS_OBSERVER_H_
#define _OUROBOROS_OBSERVER_H_

#include <vector>

namespace ouroboros
{
	//FIXME move implementation to a file observer.ipp
	template <class observer>
	class subject
	{
	public:
		/**	Registers a functor with the subject.
		 *
		 *	@param [in] aObserver Observer functor to call on a notification.
		 *		functor should act like a void() function.
		 */
		void registerObserver(const observer& aObserver)
		{
			mObservers.push_back(aObserver);
		}
		
		/**	Notifies all registered observer by calling their functors.
		 *
		 */
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
