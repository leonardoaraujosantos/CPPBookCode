#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Human {
private:
    string m_name = "no Name";
public:
    void SetName(const string &name){
        m_name = name;
    }

    void Say(){
        cout << "Hi I'm human, my name is: " << m_name << endl;
    }
};

/*
 * This class will return a a single instance of some class
 * */
template<typename T>
class CreateSingle {
private:
    static shared_ptr<T> m_onlyInstance;
public:
    static const T& Create() {
        if (m_onlyInstance == nullptr){
            m_onlyInstance = make_shared<T>();
        }
        // Get a reference from a shared_ptr
        return *m_onlyInstance.get();
    }
};

// We need to declare inside some cpp file otherwise we will have a linker error
template<typename T>
shared_ptr<T> CreateSingle<T>::m_onlyInstance = nullptr;

int main(int argc, char *argv[]){
    //shared_ptr<Human> pInstance = CreateSingle<Human>::Create();
    auto pInstance = CreateSingle<Human>::Create();
    pInstance.SetName("Leonardo");
    pInstance.Say();
    //pInstance->Say();
    cout << "Hello World!" << endl;
    return 0;
}

