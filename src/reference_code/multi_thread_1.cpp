/*
Multithreaded has shared memory so the threads communicate faster than
multiprocess solutions, the problem that multithreaded has issues distribute
tasks accross different machines

References:
http://en.cppreference.com/w/cpp/thread/sleep_for
https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
https://www.youtube.com/watch?v=LL8wkskDlbs&index=1&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M

To compile:
g++ -std=c++11 -pthread multi_thread_1.cpp -o multi_thread_1
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

// Mutex
mutex myMutex;

/*
  Now if all threads use this function to use cout we're good.
  The problem still exist if someone just use cout, outside here...
  It's better to encapsulate all this on a class...
*/
void shared_print(string msg, int num) {

  // Only one thread can access the code between lock..unlock
  /*myMutex.lock();
  cout << msg << num << endl;
  myMutex.unlock();*/

  /*
    If your code inside the lock raise an exception you may never call
    unlock, so a safer way would be to use a lock_guard
  */
  lock_guard<mutex> guard(myMutex);
  cout << msg << num << endl;
}

void someFunc() {
  for (auto i = 100; i > 0; i--) {
    //cout << "From t1 thread: " << i << endl;
    // Calling the version protected by the mutex
    shared_print(string("From t1 thread: "), i);
  }
  /*// Count elapsed time and wait a bit
  auto start = std::chrono::high_resolution_clock::now();
  // Sleep for 200 ms
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end-start;

  std::cout << "Thread 1 id:" << std::this_thread::get_id() << endl;
  std::cout << "thread 1 finished in: " << elapsed.count() << " ms\n";*/
}

// Consider here the main thread
int main() {
  auto numCores = thread::hardware_concurrency();
  cout << "Hi i'm the main thread! we have " << numCores << " available."<< endl;
  /*
    This will start a thread (this also take some time)
  */
  std::thread t1(someFunc);

  /*
    Print some stuff on main thread. Observe that the main thread and t1 share
    the cout resource. Without proper protection you could see messages like
    "From t1 thread: 63From main thread: 87"
    "70From t1 thread: 23"
  */
  for (auto i = 0; i < 100; i++) {
    //cout << "From main thread: " << i << endl;
    shared_print(string("From main thread: "), i);
  }

  /*
    Wait thead t1 to stop, otherwise the main thread will be long dead while
    t1 is alive
  */
  t1.join();

  /*
    If you don't want to wait t1 to finish you can detach it from the main
    thread, the problem is that now you have no control over t1, this means
    after you detach you cannot "join"

    By the way you need to choose to join or detach, doing nothing os not an
    option
  */
  //t1.detach();

  // Wait a bit otherwise the main thread will finish before t1 even start
  //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
