#ifndef SAFELY_GUARD_SAFECALL_H
# define SAFELY_GUARD_SAFECALL_H

# include "safely/guard/lock.h"

namespace safely
{
	namespace guard
	{
		template <typename Locker, typename ToCall>
		static inline auto	safecall(Locker& locker, const ToCall& to_call) -> decltype(to_call()) {
			safely::guard::lock<Locker>	l(locker);
			return to_call();
		}
	}
}

#endif