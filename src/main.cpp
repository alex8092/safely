#include <iostream>
#include "locker/atomic.h"
#include "guard/lock.h"
#include "guard/safecall.h"
#include "guard/access.h"
#include <unistd.h>
#include <vector>
#include <thread>
#include <list>

safely::locker::atomic 	lock;
safely::locker::atomic	lock_cout;
safely::guard::access<decltype(lock), std::list<int>>	_list;

void	consumer(int n)
{
	while (true) {
		int i = _list.get([](auto& list) {
			if (list.size() > 0) {
				int i = list.front();
				list.pop_front();
				return i;
			} else
				return -1;
		});
		if (i != -1) {
			safely::guard::lock<decltype(lock_cout)>	l(lock_cout);
			std::cout << "consumer (" << n << ") - get (" << i << ")" << std::endl;
		}
		usleep(10000 * (n + 1));
	}
}

void	producer(int n)
{
	int i = 0;
	while (true) {
		_list.call([i](auto& list) {
			list.push_back(i);
		});
		{
			safely::guard::lock<decltype(lock_cout)>	l(lock_cout);
			std::cout << "producer (" << n << ") - add (" << i << ")" << std::endl;
		}
		usleep(100000 * (n + 1));
		++i;
	}
}

int		main(void)
{
	std::vector<std::thread>	threads;
	for (int i = 0; i < 10; ++i) {
		threads.push_back(std::move(std::thread(&::producer, i)));
	}
	for (int i = 0; i < 2; ++i) {
		threads.push_back(std::move(std::thread(&::consumer, i)));
	}
	for (auto& it : threads)
		it.join();
	return (0);
}