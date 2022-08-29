#include <map>
#include <iostream>

using namespace std;
template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val
    interval_map(V const& val)
    : m_valBegin(val)
    {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if(keyBegin >= keyEnd) return;
        
        //if(operator[](keyBegin) == val) return; 
        //if(m_map.upper_bound(keyBegin)->second == val) return; 
        V hold = operator[](keyEnd);
        if(operator[](keyBegin) != val) m_map[keyBegin] = val;
        

        for (auto i = m_map.upper_bound(keyBegin), next = i; i != m_map.end(); i = next) {
            if (i->first > keyEnd) break;
            ++next;
            m_map.erase(i);
        }

        if(operator[](keyEnd) != hold) m_map[keyEnd] = hold;
    }
    void assign2(K const &keyBegin, K const &keyEnd, V const &val) {

        // if invalid range do nothing
        if (!(keyBegin < keyEnd)) {
            return;
        }

        // store previous value at keyBegin
        V lastValue = operator[](keyBegin);

        // insert value at keyBegin, if not already the same
        if (operator[](keyBegin) != val) {
            m_map[keyBegin] = val;
        }

        // remove every key inside range and store last value to be put at keyEnd
        for (auto it = m_map.upper_bound(keyBegin), next_it = it; it != m_map.cend(); it = next_it) {
            if (keyEnd < it->first) break;
            ++next_it;
            m_map.erase(it);
            lastValue = it->second;
        }

        // put previous value at keyEnd
        if (!(val == lastValue)) {
            m_map[keyEnd] = lastValue;
        }
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        auto it=m_map.upper_bound(key);
        if(it==m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }

    void print_map() const {
        cout << "Val Begin: " << m_valBegin << endl;
        for(auto it : m_map) {
            cout << it.first << " " << it.second << endl;
        }
        cout << endl;
    }
};


void print(const interval_map<int, char>& map) {
    for(int i = -10; i <= 10; i++) {
        cout << i << ": " << map[i] << endl;
    } 
    map.print_map();
}
void test() {
    interval_map<int, char> map('A');

    print(map);
    int start;
    int end;
    char c;
    cout << "a or b" << endl;
    cin >> c;
    bool flag = (c == 'a');
    
    while(true) {
        cout << "enter inputs | begin | end | value" << endl;
        cin >> start;
        cin >> end;
        cin >> c;
        if(flag) map.assign(start, end, c);
        else map.assign2(start, end, c);
        print(map);
    }
}
int main() {
    test();
}


// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.