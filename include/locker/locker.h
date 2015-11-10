#ifndef SAFELY_LOCKER_LOCKER_H
# define SAFELY_LOCKER_LOCKER_H

# include "guard/lock.h"

namespace safely
{
	namespace locker
	{
		template <typename TypeLock>
		class locker final
		{
		private:
			TypeLock	_lock;

			locker(const locker&) = delete;
			locker&	operator=(const locker&) = delete;

		public:
			explicit locker() noexcept = default;
			~locker() noexcept = default;
			locker(locker&&) noexcept = default;
			locker& operator=(locker&&) noexcept = default;

			guard::lock<TypeLock>	lock() noexcept {
				return guard::lock<TypeLock>(this->_lock);
			}

		};
	}
}

#endif