/*
Multithreaded has shared memory so the threads communicate faster than
multiprocess solutions, the problem that multithreaded has issues distribute
tasks accross different machines

References:
http://www.nuonsoft.com/blog/2012/10/21/implementing-a-thread-safe-singleton-with-c11/comment-page-1/
http://stackoverflow.com/questions/13398313/is-this-a-correct-implemenation-of-the-singleton-pattern
http://stackoverflow.com/questions/34457432/c11-singleton-static-variable-is-thread-safe-why
http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
http://stackoverflow.com/questions/11711920/how-to-implement-multithread-safe-singleton-in-c11-without-using-mutex
http://en.cppreference.com/w/cpp/thread/call_once
http://www.cplusplus.com/reference/sstream/ostringstream/ostringstream/
To compile:
g++ -std=c++11 -pthread multi_thread_5_Singleton_thread_safe.cpp -o multi_thread_5_Singleton_thread_safe
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <sstream>

using namespace std;

/*
  Now the class LogFile encapsulate the mutex and all accesss to the
  shared resource
*/
class LogFileSingleton {
public:
  LogFileSingleton() {
    m_file.open("log.txt");
  }
  ~LogFileSingleton() {    
    m_file.close();
  }
  static LogFileSingleton& GetInstance() {
    std::call_once(m_onceFlag,[] {m_instance.reset(new LogFileSingleton);});
    return *m_instance.get();
  }
  void shared_print(string id, int value) {
    unique_lock<mutex> guard(m_mutex);
    m_file << "From " << id << ": " << value << endl;
    guard.unlock();
  }
  void shared_simple_print(string id) {
    unique_lock<mutex> guard(m_mutex);
    m_file << id;
    guard.unlock();
  }
private:
  mutex m_mutex;
  ofstream m_file;
  static std::unique_ptr<LogFileSingleton> m_instance;
  static std::once_flag m_onceFlag;
};

void someFunc() {
  for (auto i = 100; i > 0; i--) {
    //cout << "From t1 thread: " << i << endl;
    // Calling the version protected by the mutex
    LogFileSingleton::GetInstance().shared_print(string("t1 thread"), i);
  }
}

// Define the instance and once_flag before using
unique_ptr<LogFileSingleton> LogFileSingleton::m_instance;
once_flag LogFileSingleton::m_onceFlag;

// Consider here the main thread
int main() {
  // Get number of available cores
  auto numCores = thread::hardware_concurrency();

  // C++ way for sprintf
  std::ostringstream stringStream;
  stringStream <<
    "Hi i'm the main thread! we have " << numCores << " available." << endl;
  LogFileSingleton::GetInstance().shared_simple_print(stringStream.str());

  /*
    This will start a thread (this also take some time)
    Note that we're passing a reference of log
  */
  std::thread t1(someFunc);

  for (auto i = 0; i < 100; i++) {
    LogFileSingleton::GetInstance().shared_print(string("main thread"), i);
  }

  /*
    Wait thead t1 to stop, otherwise the main thread will be long dead while
    t1 is alive
  */
  t1.join();

}
