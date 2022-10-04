#include <iostream>

using namespace std;
string helper( string& s, const int& pos) {
    int left = pos - 1;
    int right = pos + 1;
    int length = 1;
    string result = "";
    result += s[pos];
    while(true) {
        if(left < 0) break;
        if(right >= s.length()) break;
        if(s[left] != s[right]) break;
        
        result = s[left] + result + s[right];
        length += 2;
        left--;
        right++;

    }
    return result;
}
string helper(const string& s, const int& l, const int& r) {
    int left = l;
    int right = r;
    int length = 0;
    string result = "";
    while(true) {
        if(left < 0) break;
        if(right >= s.length()) break;
        if(s[left] != s[right]) break;
        
        result = s[left] + result + s[right];
        length += 2;
        left--;
        right++;

    }
    return result;
}
string longestSubstring(string& s) {
    string result = "";
    int length = 0;
    for(int i = 0; i < s.length(); i++) {
        string sub = helper(s, i);
        cout << sub << " ";
        if(sub.length() > length) {
            length = sub.length();
            result = sub;
        }
    }
    cout << endl;
    for(int i = 1; i < s.length(); i++) {
        string sub = helper(s, i - 1, i);
        cout << sub << " ";
        if(sub.length() > length) {
            length = sub.length();
            result = sub;
        }
    }
    cout << endl;
    return result;
}
int main() {
    string s;
    cin >> s;
    cout << longestSubstring(s) << endl;
}