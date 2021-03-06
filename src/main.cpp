#include <iostream>
#include "safely/safely.h"
#include <unistd.h>
#include <vector>
#include <thread>
#include <list>

safely::locker::locker<safely::locker::atomic>	locker_cout;
safely::guard::access<std::list<int>>	_list;

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
			auto lock = locker_cout.lock();
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
			auto lock = locker_cout.lock();
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