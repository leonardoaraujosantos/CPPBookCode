/*
Multithreaded has shared memory so the threads communicate faster than
multiprocess solutions, the problem that multithreaded has issues distribute
tasks accross different machines

References:
http://en.cppreference.com/w/cpp/thread/sleep_for
https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
https://www.youtube.com/watch?v=LL8wkskDlbs&index=1&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M

To compile:
g++ -std=c++11 -pthread multi_thread_2.cpp -o multi_thread_2
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
  void shared_print(string id, int value) {
    lock_guard<mutex> guard(m_mutex);
    m_file << "From " << id << ": " << value << endl;
  }
private:
  mutex m_mutex;
  // Notice that m_file should never be given outside here because it could
  // be accessed without the mutex/guard
  ofstream m_file;
};

void someFunc(LogFile& log) {
  for (auto i = 100; i > 0; i--) {
    //cout << "From t1 thread: " << i << endl;
    // Calling the version protected by the mutex
    log.shared_print(string("t1 thread"), i);
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

  /*
    Print some stuff on main thread. Observe that the main thread and t1 share
    the cout resource. Without proper protection you could see messages like
    "From t1 thread: 63From main thread: 87"
    "70From t1 thread: 23"
  */
  for (auto i = 0; i < 100; i++) {
    //cout << "From main thread: " << i << endl;
    log.shared_print(string("main thread"), i);
  }

  /*
    Wait thead t1 to stop, otherwise the main thread will be long dead while
    t1 is alive
  */
  t1.join();

}
