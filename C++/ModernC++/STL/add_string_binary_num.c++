#include <string>
#include <iostream>

using namespace std;

string decToBinary (int n) { 
    string str;
    bool firstOne = false;

    // Size of an integer is assumed to be 32 bits 
    for (int i = 31; i >= 0; i--) { 
        int k = n >> i; 

        if (k & 1) {
            str = str + "1";
            firstOne = true;
        } else {
            if (firstOne) 
                str = str + "0"; 
        }
    } 
    return str;
} 

string addBinary (string a, string b) {
        string str = "";
        
        int lena = a.length();
        int lenb = b.length();
        int carry = 0;
        
        while (lena && lenb) {
            char cha = a[lena-1];
            char chb = b[lenb-1];
            int na = cha == '1' ? 1 : 0;
            int nb = chb == '1' ? 1 : 0;
            int nout = na+nb+carry;
            char chout;
            if (nout == 3) {
                chout = '1'; carry = 1;
            } else if (nout == 2) {
                chout = '0'; carry = 1;
            } else {
                chout = nout ? '1' : '0';
                carry = 0;
            }
            str = chout + str;
            lena--;
            lenb--;
        }
        while (lena) {
            char cha = a[lena-1];
            int nout = cha == '1' ? 1 : 0;
            nout += carry;
            char chout;
            if (nout == 2) {
                chout = '0'; 
                carry = 1;
            } else {
                chout = nout ? '1' : '0';
                carry = 0;
            }
            str = chout + str;
            lena--;
        }
        while (lenb) {
            char chb = b[lenb-1];
            int nout = chb == '1' ? 1 : 0;
            nout += carry;
            char chout;
            if (nout == 2) {
                chout = '0'; 
                carry = 1;
            } else {
                chout = nout ? '1' : '0';
                carry = 0;
            }
            str = chout + str;
            lenb--;
        }
        
        if (carry)
            str = "1" + str;
        
        return str;
}

int main (void) {

    string a = decToBinary(10);
    string b = decToBinary(22);

    string out = addBinary(a, b);

    cout << a << " +  " << b << " = " << out << endl;
    return 0;
}

