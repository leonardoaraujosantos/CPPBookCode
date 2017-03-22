#include <iostream>
#include <string>
#include <stack>
using namespace std;


inline int binChar2Num(const char ch){
    int val = 1?(ch=='1'):0;
    return val;
}

/*
    Add 2 binary numbers defined as strings "101" + "11"=1000.
    Attention: The strings can be really big
*/
string strBinSum(const string &num1, const string &num2){
    // Initialize with the size of the biggest string plus one character (Worst sum case 11+11=110)
    string resp(max(num1.size(), num2.size())+1,'0');

    // Select biggest operand
    const string &refBig = (num1.size()>num2.size())?num1:num2;
    const string &refSmall = (num1.size()<num2.size())?num1:num2;

    // Create stack for carry-bit
    stack<int> stCarry;

    // Iterate on num1 on reverse order
    auto itr2 = refSmall.rbegin();
    auto itrResp = resp.rbegin();
    for (auto itr1 = refBig.rbegin(); itr1 != refBig.rend(); ++itr1){
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

        // Get carry bit
        int carry = 0;
        if (stCarry.empty()){
            carry = 0;
        } else {
            carry = stCarry.top();
            stCarry.pop();
        }

        // Do the sum including carry
        int res = val1 + val2 + carry;
        if (res > 1) {
            stCarry.push(1);
            res = 0;
        }
        *itrResp = to_string(res).at(0);
        itrResp++;
    }
    // Add carry there is still something to add
    if (!stCarry.empty()){
        auto lastVal = stCarry.top();
        stCarry.pop();
        *itrResp = to_string(lastVal).at(0);
    }
    return resp;
}

int main()
{
    //string sumBin = strBinSum("101","11");
    string sumBin = strBinSum("10001110001001100101","100110011");
    auto resultRef = string("10001110001110011000");
    cout << "10001110001001100101 + 100110011 = " << sumBin << endl;
    return 0;
}
