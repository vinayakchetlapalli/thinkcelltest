#include <map>
#include <iostream>
using namespace std;
  
int main()
{
    // initialize container
    map<int, int> mp;
  
    // insert elements in random order
    mp.insert({ 12, 30 });
    mp.insert({ 11, 10 });
    mp.insert({ 15, 50 });
    mp.insert({ 14, 40 });
  
    // when 11 is present
    auto it = mp.upper_bound(9);
    cout << "The upper bound of key 11 is ";
    cout << (*it).first << " " << (*it).second << endl;
  
    // when 13 is not present
    it = mp.upper_bound(13);
    cout << "The upper bound of key 13 is ";
    cout << (*it).first << " " << (*it).second << endl;
  
    // when 17 is exceeds the maximum key, so size
        // of mp is returned as key and value as 0.
    it = mp.upper_bound(15);
    cout << "The upper bound of key 15 is ";
    if(it == mp.end()) cout << "printed end";
    cout << (*it).first << " " << (*it).second;
    return 0;
}