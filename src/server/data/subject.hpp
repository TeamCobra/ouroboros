#ifndef _OUROBOROS_OBSERVER_H_
#define _OUROBOROS_OBSERVER_H_

#include <vector>

namespace ouroboros
{
	template <class Observer>
	class subject
	{
	public:
		/**	Registers a functor with the subject.
		 *
		 *	@param [in] aObserver Observer functor to call on a notification.
		 *		functor should act like a void() function.
		 */
		void registerObserver(const Observer& aObserver);
		
		/**	Notifies all registered observer by calling their functors.
		 *
		 */
		void notify() const;
		
	private:
		std::vector<Observer> mObservers;
	};
}

#include "subject.ipp"

#endif//_OUROBOROS_OBSERVER_H_
