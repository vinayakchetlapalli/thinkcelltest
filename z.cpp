#include <iostream>
#include <vector>
using namespace std;
int z(string s) {
    string a = "01";
    string b = "10";
    vector<int> as;
    vector<int> bs;
    int total = 0;
    for(int i = 0; i < s.length() - 1; i++) {
        string sub = s.substr(i, 2);
        if(sub == a) as.push_back(i);
        if(sub == b) bs.push_back(i);
    }

    for(auto pos: as) {
        string check = s.substr(pos, 2);
        int start = pos;
        int end = pos + 1;
        string cp = a;
        while(true) {
            if(check != cp) break;
            total++;
            start--;
            end++;
            if(start < 0) break;
            if(end >= s.length()) break;
            check = s[start] + check + s[end];
            cp = "0" + cp + "1";
        }
    }
    for(auto pos: bs) {
        string check = s.substr(pos, 2);
        int start = pos;
        int end = pos + 1;
        string cp = b;
        while(true) {
            if(check != cp) break;
            total++;
            start--;
            end++;
            if(start < 0) break;
            if(end >= s.length()) break;

            check = s[start] + check + s[end];
            cp = "1" + cp + "0";
        }
    }

    return total;
}
int y(string s) {
    int i = 0;
    int total = 0;
    while(i < s.length()) {
        int ones = 0;
        int zeroes = 0;
        if(s[i] == '0') {
            while(s[i] == '0') {
                zeroes++;
                i++;
            }
            int o = 0;
            int j = i;
            while(s[j] == '1') {
                ones++;
                j++;
            }
        }
        else {
            int o = 0;
            while(s[i] == '1') {
                ones++;
                i++;
            }
            int z = 0;
            int j = i;
            while(s[j] == '0') {
                zeroes++;
                j++;
            }
        }
        total += min(zeroes, ones);
    }
    return total;
}
int main() {
    string s;
    cout << "enter string " << endl;
    cin >> s;
    cout << s << endl;
    cout << z(s) << endl;
    cout << y(s) << endl;
}