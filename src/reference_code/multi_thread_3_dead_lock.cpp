/*
Multithreaded has shared memory so the threads communicate faster than
multiprocess solutions, the problem that multithreaded has issues distribute
tasks accross different machines

References:
https://www.youtube.com/watch?v=_N0B5ua7oN8&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=4

To compile:
g++ -std=c++11 -pthread multi_thread_3_dead_lock.cpp -o multi_thread_3_dead_lock
*/
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <fstream>

using namespace std;

/*
  Now the class LogFile encapsulate the mutex and all accesss to the
  shared resource
*/
class LogFile {
public:
  LogFile() {
    m_file.open("log.txt");
  }
  ~LogFile() {
    cout << "Dumping log do disk" << endl;
    m_file.close();
  }
  void shared_print_1(string id, int value) {
    lock_guard<mutex> guard_1(m_mutex_1);
    lock_guard<mutex> guard_2(m_mutex_2);

    cout << "From " << id << ": " << value << endl;
  }
  void shared_print_2(string id, int value) {
    /*
      Now the bad part if 2 threads use the mutexes with different order
      One of the threads will wait for one mutex forever (Deadlock)
    */
    lock_guard<mutex> guard_2(m_mutex_2);
    lock_guard<mutex> guard_1(m_mutex_1);

    // To solve the Deadlock
    //lock_guard<mutex> guard_1(m_mutex_1);
    //lock_guard<mutex> guard_2(m_mutex_2);

    cout << "From " << id << ": " << value << endl;
  }
private:
  mutex m_mutex_1;
  mutex m_mutex_2;
  // Notice that m_file should never be given outside here because it could
  // be accessed without the mutex/guard
  ofstream m_file;
};

void someFunc(LogFile& log) {
  for (auto i = 100; i > 0; i--) {
    //cout << "From t1 thread: " << i << endl;
    // Calling the version protected by the mutex
    log.shared_print_1(string("t1 thread"), i);
  }
}

// Consider here the main thread
int main() {
  LogFile log;
  auto numCores = thread::hardware_concurrency();
  cout << "Hi i'm the main thread! we have " << numCores << " available."<< endl;
  /*
    This will start a thread (this also take some time)
    Note that we're passing a reference of log
  */
  std::thread t1(someFunc, std::ref(log));

  for (auto i = 0; i < 100; i++) {
    //cout << "From main thread: " << i << endl;
    log.shared_print_2(string("main thread"), i);
  }

  /*
    Wait thead t1 to stop, otherwise the main thread will be long dead while
    t1 is alive
  */
  t1.join();

}
