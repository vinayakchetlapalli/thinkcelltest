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
            k++;
        }
        
        for(int i = 0; i < dl.size(); i++) {
            m_map.erase(dl[i]); // because it is iterators each is constant 
        }
        auto last = std::make_pair(keyEnd, valueEnd);
        if(!(operator[](keyEnd) == valueEnd)) m_map.insert(last); // logn without hint
    } 

    void assign2(K const& keyBegin, K const& keyEnd, V const& val) {
        if(!(keyBegin < keyEnd)) return; 
        
        // investigate make_pair 
        auto pr = std::make_pair(keyBegin, val);
        auto it = m_map.lower_bound(keyBegin); // logn 
        
        V vl;
        bool flag = (it == m_map.end());
        if(flag) {
            vl = m_valBegin;
		} else {
			vl = it->second;
		}
        
        V valueEnd = it->second;
        bool equality = (!(keyBegin < it->first) && !(it->first < keyBegin));
        bool deleteBegin = false;

        if(equality && !flag) { // !lflag is for when end iterator accidentally gives one
            if(it == m_map.begin()) deleteBegin = true;
            it = m_map.erase(it);
        }
        
        if(!(vl == val)) {
            m_map.insert(it, pr);
        }
        /* Value Comparions */

        std::map<int, typename std::map<K, V>::iterator> dl;
        typename std::map<K, V>::iterator position = it;

        if(!flag && !(keyBegin < position->first)) position++;
        int k = 0;

        for(position; position != m_map.end(); position++) { // upperbound is logn 
            if(!(position->first < keyEnd)) break;
            dl[k] = position;
            k++;
        }
        for(int i = 0; i < dl.size(); i++) {
            m_map.erase(dl[i]); // because it is iterators each is constant 
        }
        
        if(position == m_map.end()) {
            valueEnd = m_valBegin;
            m_map.emplace_hint(position, keyEnd, valueEnd);
        }
        else if (!dl.empty() && !(position->second == valueEnd)) {
            valueEnd = dl.rbegin()->second->second;
            m_map.emplace_hint(position, keyEnd, valueEnd);
        }
        else if(!(position->second == valueEnd)) {
            m_map.emplace_hint(position, keyEnd, valueEnd);
        }
        while(m_map.begin()->second == m_valBegin) m_map.erase(m_map.begin());   
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

    /*
    m.assign(2, 5, 'D');
    m.print();
    m.assign(2, 3, 'C');
    m.print();
    m.assign(4, 20, '2');
    m.print();
    m.assign(0, 5, 'x');
    m.print();
    m.assign(-1, 5, 'A');
    m.print();
    */
    m.assign(2, 5, 'D');
    m.print();
    m.assign(2, 3, 'C');
    m.print();
    m.assign(8, 10, 'E');
    m.print();
    m.assign(7, 10, 'A');
    m.print();
    m.assign(0, 5, 'x');
    m.print();
    m.assign(0, 20, 'A');
    m.print();

}

int main() {
    test();
}
// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.