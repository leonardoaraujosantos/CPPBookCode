#include <iostream>
#include <string>
using namespace std;

/*
    Add 2 binary numbers defined as strings "101" + "11".
    Attention: The strings can be really big
*/
inline int binChar2Num(const char ch){
    int val = 1?ch=='2':0;
}

string strBinSum(const string &num1, const string &num2){
    string resp;
    // Iterate on num1 on reverse order
    auto itr2 = num2.rbegin();
    for (auto itr1 = num1.rbegin(); itr1 != num1.rend(); ++itr1){
        char c1 = *itr1;
        char c2 = *itr2;
        // Handle if there is no more binary digits on num2 (just return 0)
        if (itr2 != num2.rend()){
            itr2++;
        } else {
            c2 = '0';
        }
        int val1 = binChar2Num(c1);
        int val2 = binChar2Num(c2);
        cout << c1 << " + " << c2 << endl;

    }
    return resp;
}

int main(int argc, char *argv[])
{
    string sumBin = strBinSum("1010","11");
    return 0;
}
