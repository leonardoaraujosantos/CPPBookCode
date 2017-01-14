/*
Condition Variables
Here we're going to learn to use condition variables to avoid, busy wait
To compile
g++ -std=c++11 -pthread multi_thread_6_Prod_Consumer.cpp -o multi_thread_6_Prod_Consumer
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <chrono>

using namespace std;

// This resource will be used by 2 threads
deque<int> q;
mutex mu;

condition_variable cond_var;

void func1() {
	int count = 10;
	// Push 10 elements
	while (count > 0) {
		// Ask a lock to protect deque
		unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();

		// Notify one waiting thread, that use this condition variable
		//cond_var.notify_one();
		// Notify all waiting thread, that use this condition variable
		cond_var.notify_all();

		// Sleep for a while
		//this_thread::sleep_for(chrono::milliseconds(1));
		this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

// Slow version with busy wait
void func2_busy_wait() {
	int data = 0;
	// Get 10 elements
	while (data != 1) {
		// Ask a lock to protect deque
		unique_lock<mutex> locker(mu);
		// Keeps checking if q is empty (Busy wait state, is not good)
		if (!q.empty()) {
			data = q.back();
			q.pop_back();
			locker.unlock();
			cout << "t2 got:" << data << endl;
		} else {
			locker.unlock();
		}
	}
}

// Faster version
void func2_cond_variable() {
	int data = 0;
	// Get 10 elements
	while (data != 1) {
		// Ask a lock to protect deque
		unique_lock<mutex> locker(mu);

		// Unlock locker and wait until notified to lock again
		//cond_var.wait(locker);		
		// Unlock locker and wait until notified to lock again
		// But if the q is still empty sleep again
		cond_var.wait(locker, [](){return !q.empty();});
		
		data = q.back();
		q.pop_back();
		locker.unlock();		
		cout << "t2 got:" << data << endl;				
	}
}

int main() {
	// Create 2 threads and wait them to finish
	thread t1(func1);
	//thread t2(func2_busy_wait);
	thread t2(func2_cond_variable);

	// Wait them to complete
	t1.join();
	t2.join();
}