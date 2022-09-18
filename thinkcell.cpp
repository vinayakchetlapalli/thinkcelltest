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
	void assign2( K const& keyBegin, K const& keyEnd, V const& val ) {
        if(!(keyBegin < keyEnd)) return; 

        /*pair construction not sure if calls constructor for val or keyBegin */
        auto pr = std::make_pair(keyBegin, val);

        auto valueEnd = operator[](keyEnd); //logn 

        /* Value Comparions */

        if(!(operator[](keyBegin) == val)) { // logn
            /* Insert, unsure how insert works */
            m_map.insert(pr).first; //logn without hint 
        }
        
        std::map<int, typename std::map<K, V>::iterator> dl;
        int k = 0;
        for(auto i = m_map.upper_bound(keyBegin); i != m_map.end(); i++) { // upperbound is logn 
            if(!(i->first < keyEnd)) break;
            dl[k] = i;
        }
        
        for(int i = 0; i < dl.size(); i++) {
            m_map.erase(dl[i]); // because it is iterators each is constant 
        }
        auto last = std::make_pair(keyEnd, valueEnd);
        if(!(operator[](keyEnd) == valueEnd)) m_map.insert(last); // logn without hint
    } 

    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        if(!(keyBegin < keyEnd)) return; 
        
        auto pr = std::make_pair(keyBegin, val);
        auto it = m_map.lower_bound(keyBegin); // logn 
        
        V vl;
        bool flag = (it == m_map.end());
        if(flag) {
 			vl = m_valBegin;
		} else {
			vl = it->second;
		}
        
        auto existingkey = it->first;
        V valueEnd;
        if(!(existingkey == keyBegin) && !flag) { // !lflag is for when end iterator accidentally gives one
            valueEnd = it->second;
            m_map.erase(it);
        }
        if(!(vl == val)) {
            m_map.insert(pr);
        }
        print(it);
        cout << "val:" << val << endl;
        /* Value Comparions */

        std::map<int, typename std::map<K, V>::iterator> dl;
        typename std::map<K, V>::iterator position = it;

        if(!flag && !(keyBegin < position->first)) position++;
        int k = 0;
        // check if you are eraseing end 
        for(position; position != m_map.end(); position++) { // upperbound is logn 
            if(!(position->first < keyEnd)) break;
            print(position);
            dl[k] = position;
            k++;
        }

        if(position == m_map.end()  || m_map.empty() ) {
            valueEnd = m_valBegin;
        } 

        for(int i = 0; i < dl.size(); i++) {
            valueEnd = dl[i]->second;
            print(dl[i]);
            m_map.erase(dl[i]); // because it is iterators each is constant 
        }
        cout << valueEnd << endl;
        if(!(position->second == valueEnd)) {  
            m_map.emplace_hint(position, keyEnd, valueEnd); // logn without hint  
        }   

    }
    // logn look up
	// look-up of the value associated with key

	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
    void printmap() {
        cout << "mmap contains" << endl;
        for(const auto& p: m_map) {
            cout << "{" << p.first << " " << p.second << "}" << endl;
        }
        cout << endl;
    }
    void print() {
        for(int i = -5; i < 10; i++) {
            cout << i <<  ": " << operator[](i) << endl;
        }
        for(const auto& p: m_map) {
            cout << "{" << p.first << " " << p.second << "}" << endl;
        }
        cout << endl;
    }

    void print(typename std::map<K, V>::iterator &position) {
        if(position == m_map.end()) {
            cout << "end iterator" << endl;
        }
        else {
            cout << "iterator: " << position->first << " " << position->second << endl;
        }
    }
    
};

void test() {
    interval_map<int, char> m = interval_map<int, char>('A');
    //Testing
    m.assign(2, 5, 'D');
    m.print();
    m.assign(2, 3, 'T');
    m.print();
}
int main() {
    test();
}
// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.