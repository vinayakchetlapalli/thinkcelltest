#include <vector>
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;

int median(const vector<int>& a, const vector<int>& b) {
    vector<int> merge;
    int m = a.size();
    int n = b.size();
    int i = 0;
    int j = 0;
    while(i < m && j < n) {
        if(a[i] < b[j]) {
            merge.push_back(a[i]);
            i++;
            continue;
        }
        if(a[i] == b[j]) {
            merge.push_back(a[i]);
            merge.push_back(b[j]);
            i++;
            j++;
            continue;
        }
        if(a[i] > b[j]) {
            merge.push_back(b[j]);
            j++;
            continue;
        }
    }
    while(j < n) {
        merge.push_back(b[j]);
        j++;
    }
    while(i < m) {
        merge.push_back(a[i]);
        i++;
    }

    for(const auto& i: merge) {
        cout << i << " ";
    }
    cout << endl;
    int size = m + n;
    if(size % 2 == 1) {
        return merge[size/2];
    }
    else {
        int result = merge[size/2] + merge[1 + size/2];
        return result/2;
    }

}
int main() {
    string a = "2 3 5 9 10 12 13 15 17 18 
                22 23 24 25 27 30 31 32 34 38";

    20
    string b = "10 11 16 21 23
                26 30 33 36 38";


    vector<int> aa;
    vector<int> bb;
    stringstream ss (a);
    string temp;
    while(ss >> temp) {
        aa.push_back(stoi(temp));
    }
    stringstream sss(b);
    while(sss >> temp ) {
        bb.push_back(stoi(temp));
    }
    for(const auto& i: aa) {
        cout << i << " ";
    }
    cout << endl;
    for(const auto& b: bb) {
        cout << b << " ";
    }
    cout << endl;
    cout << median(aa, bb) << endl;

}