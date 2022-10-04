#include <map>
#include <iostream> 
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

        
        auto valueEnd = operator[](keyEnd);

        /* Value Comparions */

        if(!(operator[](keyBegin) == val)) {
            /* Insert, unsure how insert works */
            m_map.insert(pr);
        }
        
        std::map<int, typename std::map<K, V>::iterator> dl;
        int k = 0;
        for(auto i = m_map.upper_bound(keyBegin); i != m_map.end(); i++) {
            if(!(i->first < keyEnd)) break;
            dl[k] = i;
            k++;
        }
        
        for(int i = 0; i < dl.size(); i++) {
            m_map.erase(dl[i]);
        }
        auto last = std::make_pair(keyEnd, valueEnd);
        if(!(operator[](keyEnd) == valueEnd)) m_map.insert(last);

	}
    void assign3(K const &keyBegin, K const &keyEnd, V const &val) {

        // if invalid range do nothing
        if (!(keyBegin < keyEnd)) {
            return;
        }

        // store previous value at keyBegin
        V lastValue = operator[](keyBegin);

        // insert value at keyBegin, if not already the same

        if (operator[](keyBegin) != val) {
            std::cout << "inserting " << keyBegin << ", " << val << std::endl;
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
            std::cout << "inserting at end" << keyEnd << ", " << lastValue << std::endl;
            m_map[keyEnd] = lastValue;
        }
    }
	// look-up of the value associated with key
    void assign2( K const& keyBegin, K const& keyEnd, V const& val ) {

			if (!(keyBegin < keyEnd)) return;

			std::pair<K,V> beginExtra;
			std::pair<K,V> endExtra;
			bool beginHasExtra = false;
			bool endHasExtra = false;

			typename std::map<K,V>::const_iterator itBegin;
			itBegin = m_map.lower_bound(keyBegin);
			if ( itBegin!=m_map.end() && keyBegin < itBegin->first ) {
				if (itBegin != m_map.begin()) {
					beginHasExtra = true;
					--itBegin;
					beginExtra = std::make_pair(itBegin->first, itBegin->second);
				}
				// openRange for erase is prevIterator
				// insert (prevIterator->first, prevIterator->second) as well!
			}

			typename std::map<K,V>::const_iterator itEnd;
			itEnd = m_map.lower_bound(keyEnd);
			if ( itEnd!=m_map.end() && keyEnd < itEnd->first ) {
				endHasExtra = true;
				typename std::map<K,V>::const_iterator extraIt = itEnd;
				--extraIt;
				endExtra = std::make_pair(keyEnd, extraIt->second);
				// closeRange for erase is this iterator
				// insert (keyEnd, prevIterator->second) as well!
			}

			// 4 canonical conflicts:
			//	 beginExtra w/ mid
			//	 before-mid w/ mid (beginHasExtra==false)
			//	 mid w/ endExtra
			//	 mid w/ after-mid (endHasExtra==false)

			bool insertMid = true;
			if (beginHasExtra) {
				if (beginExtra.second == val)
					insertMid = false;
			} else {
				if (itBegin != m_map.begin()) {
					typename std::map<K,V>::const_iterator beforeMid = itBegin;
					--beforeMid;
					if (beforeMid->second == val)
						insertMid = false;
				}
			}


			if (endHasExtra) {
				if ( (insertMid && endExtra.second == val) || (!insertMid && endExtra.second == beginExtra.second) )
					endHasExtra = false;
			} else {
				if ( (insertMid && itEnd!=m_map.end() && itEnd->second == val) || (!insertMid && itEnd!=m_map.end() && itEnd->second == beginExtra.second) )
					itEnd = m_map.erase(itEnd);
			}

			itBegin = m_map.erase(itBegin, itEnd);
			if (beginHasExtra)
				itBegin = m_map.insert(itBegin, beginExtra);
			if (insertMid)
				itBegin = m_map.insert(itBegin, std::make_pair(keyBegin, val));
			if (endHasExtra)
									m_map.insert(itBegin, endExtra);

// INSERT YOUR SOLUTION HERE
    }
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
    void printmap() {
        std::cout << "mmap contains" << std::endl;
        for(const auto& p: m_map) {
            std::cout << "{" << p.first << " " << p.second << "}" << std::endl;
        }
    }
    void print() {
        for(int i = -5; i < 10; i++) {
            std::cout << i <<  ": " << operator[](i) << std::endl;
        }
        for(const auto& p: m_map) {
            std::cout << "{" << p.first << " " << p.second << "}" << std::endl;
        }
        std::cout << std::endl;
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
    m.assign(0, 5, 'A');
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