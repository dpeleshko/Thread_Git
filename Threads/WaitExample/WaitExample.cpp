// WaitExample.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <vector>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

std::vector<int> data;
std::condition_variable data_cond;
std::mutex m;

void thread_func1() {
	std::unique_lock<std::mutex> lock(m);
	data.push_back(10);
	data_cond.notify_one();
}
void thread_func2() {
	std::unique_lock<std::mutex> lock(m);
	data_cond.wait(lock, [] { return !data.empty(); });
	std::cout << data.back() << std::endl;
}
int main() {
	std::thread th1(thread_func1);
	std::thread th2(thread_func2);
	th1.join();
	th2.join();
	return 0;
}