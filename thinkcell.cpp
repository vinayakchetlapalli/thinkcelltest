#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
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

    interval_map(const interval_map<K, V>& m1) {
        m_valBegin = m1.m_valBegin;
        m_map = m1.m_map;
    }

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
    void canonical() {
        if(m_map.empty()) return;

        std::map<int, typename std::map<K, V>::iterator> dl;
        auto it = m_map.begin();
        V curr = it->second;
        int k = 0;
        it++;
        for(it; it != m_map.end(); it++) {
            if(it->second != curr) {
                curr = it->second;
                for(const auto& p: dl) {
                    m_map.erase(p.second);
                }
                dl.clear();
                k = 0;
            }
            else {
                dl[k] = it;
                k++;
            }
        }
        for(const auto& p: dl) {
            m_map.erase(p.second);
        }
        
    }
	int start() const {
        int result = -5;
        if(m_map.begin()->first < result) result = m_map.begin()->first;
        return result;
    }

    int ending() const {
        int result = 10;
        if(m_map.rbegin()->first > result) result = m_map.rbegin()->first;
        return result;
    }
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
        if(!(keyBegin < keyEnd)) return; 

        auto pr = std::make_pair(keyBegin, val);

        auto valueEnd = operator[](keyEnd); //logn

        std::map<int, typename std::map<K, V>::iterator> dl;
        int k = 0;
        auto it = m_map.lower_bound(keyBegin);

        while(it != m_map.end() && it->first < keyEnd) {
            dl[k] = it;
            k++;
            it++;
        }
        for(int i = 0; i < dl.size(); i++) {
            m_map.erase(dl[i]); // because it is iterators each is constant 
        }
        m_map.emplace_hint(it, pr); //logn without hint 

        auto last = std::make_pair(keyEnd, valueEnd);
        if(!(operator[](keyEnd) == valueEnd)) m_map.emplace_hint(it, last); // logn without hint

        while(m_map.begin()->second == m_valBegin) m_map.erase(m_map.begin());
        
        if(m_map.empty()) return;
        
        std::map<int, typename std::map<K, V>::iterator> d;
        it = m_map.begin();
        auto curr = it->second;
        int l = 0;
        it++;
        for(it; it != m_map.end(); it++) {
            if(it->second != curr) {
                curr = it->second;
                for(const auto& p: d) {
                    m_map.erase(p.second);
                }
                d.clear();
                l = 0;
            }
            else {
                d[k] = it;
                l++;
            }
        }
        for(const auto& p: d) {
            m_map.erase(p.second);
        }
    } 

    void assign2(K const& keyBegin, K const& keyEnd, V const& val) {
        if(!(keyBegin < keyEnd)) return; 

        auto pr = std::make_pair(keyBegin, val);

        auto valueEnd = operator[](keyEnd); //logn

        std::map<int, typename std::map<K, V>::iterator> dl;
        int k = 0;
        auto it = m_map.lower_bound(keyBegin);

        while(it != m_map.end() && it->first < keyEnd) {
            dl[k] = it;
            k++;
            it++;
        }
        for(int i = 0; i < dl.size(); i++) {
            m_map.erase(dl[i]); // because it is iterators each is constant 
        }
        m_map.emplace_hint(it, pr); //logn without hint 

        auto last = std::make_pair(keyEnd, valueEnd);
        if(!(operator[](keyEnd) == valueEnd)) m_map.emplace_hint(it, last); // logn without hint

        while(m_map.begin()->second == m_valBegin) m_map.erase(m_map.begin());
        
        if(m_map.empty()) return;
        
        std::map<int, typename std::map<K, V>::iterator> d;
        it = m_map.begin();
        auto curr = it->second;
        int l = 0;
        it++;
        for(it; it != m_map.end(); it++) {
            if(it->second != curr) {
                curr = it->second;
                for(const auto& p: d) {
                    m_map.erase(p.second);
                }
                d.clear();
                l = 0;
            }
            else {
                d[k] = it;
                l++;
            }
        }
        for(const auto& p: d) {
            m_map.erase(p.second);
        }
    }

    void assign3(K const& keyBegin, K const& keyEnd, V const& val) {
        if(!(keyBegin < keyEnd)) return; 
        
        auto pr = std::make_pair(keyBegin, val);
        auto it = m_map.lower_bound(keyBegin); // logn 
        
        V vl;
        bool flag = (it == m_map.end());
        if(flag) {
 			vl = m_valBegin;
            cout << it->first << endl;
		} else {
			vl = it->second;
		}
        
        V valueEnd = it->second;

        auto existingKey = it->first;
        bool equality = (!(keyBegin < existingKey) && !(existingKey < keyBegin));
        bool deleteBegin = false;

        if(equality && !flag) { // !lflag is for when end iterator accidentally gives one
            if(it == m_map.begin()) deleteBegin = true;
            it = m_map.erase(it);
        }
        //assuming insertion at begining of map is constant or non log
        if(!(vl == val)) {
            if(deleteBegin) {
                m_map.insert(pr);
            }
            else m_map.insert(it, pr);
        }
        /* Value Comparions */

        std::map<int, typename std::map<K, V>::iterator> dl;
        typename std::map<K, V>::iterator position = it;

        // if it isnt end iterator and positioniterator isnt >= key bein increment
        //may not be necessary
        if(!flag && !(keyBegin < position->first)) position++;
        int k = 0;
        // check if you are eraseing end 
        //check if [] corresponds to V constructor
        for(position; position != m_map.end(); position++) {  // upperbound is logn 
            if(!(position->first < keyEnd)) break;
            dl[k] = position;
            k++;
        }
        if(!dl.empty()) valueEnd = dl.rbegin()->second->second;
        for(int i = 0; i < dl.size(); i++) {
            m_map.erase(dl[i]); // because it is iterators each is constant 
        }
        if(position == m_map.end()) valueEnd = m_valBegin;
        //check corner casing for this
        if(!(position->second == valueEnd)) { 
            m_map.emplace_hint(position, keyEnd, valueEnd); // logn without hint  
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
    void printmap() const {
        cout << "mmap" << endl;
        for(const auto& p: m_map) {
            cout << "{" << p.first << " " << p.second << "}" << endl;
        }
    }

    vector<string> maplines() const {
        vector<string> result;
        result.push_back("mmap");
        for(const auto& p : m_map) {
            string line = "";
            line += "{";
            line += to_string(p.first);
            line += " ";
            line += p.second;
            line += "}";
            result.push_back(line);
        }
        return result;
    }
    friend ostream& operator<<(ostream& os, const interval_map<K, V>& m1) {
        int beg = -5;
        int end = 10;
        if(m1.m_map.begin()->first < beg) beg = m1.m_map.begin()->first;
        if(m1.m_map.rbegin()->first > end) end = m1.m_map.rbegin()->first;
        for(int i = beg; i <= end; i++) {
            os << i <<  ": " << m1.operator[](i) << endl;
        }
        for(const auto& p: m1.m_map) {
            os << "{" << p.first << " " << p.second << "}" << endl;
        }
        os << endl;
        return os;
    }
    void print() const {
        int beg = -5;
        int end = 10;
        if(m_map.begin()->first < beg) beg = m_map.begin()->first;
        if(m_map.rbegin()->first > end) end = m_map.rbegin()->first;
        for(int i = beg; i <= end; i++) {
            cout << i <<  ": " << operator[](i) << endl;
        }
        for(const auto& p: m_map) {
            cout << "{" << p.first << " " << p.second << "}" << endl;
        }
        cout << endl;
    }

    string result() {
        string result = "";
        int beg = -5;
        int end = 10;
        if(m_map.begin()->first < beg) beg = m_map.begin()->first;
        if(m_map.rbegin()->first > end) end = m_map.rbegin()->first;
        for(int i = beg; i <= end; i++) {
            result+= to_string(i);
            result+= ": "; 
            result+= operator[](i);
            result+= "\n";
        }
        for(const auto& p: m_map) {
            result+="{";
            result+= to_string(p.first);
            result+= " ";
            result += p.second;
            result += "}";
            result += "\n";
        }
        result += "\n";
        return result;
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

class instruction {
    int start;
    int end;
    char c; 
public:
    instruction(int a, int b, char cc) {
        start = a;
        end = b;
        c = cc;
    }
    instruction() {
    }
    friend istream& operator>>(istream& is, instruction& i) {
        is>> i.start >> i.end >> i.c;
        return is;
    }
    friend ostream& operator<<(ostream& os, const instruction& i) {
        os << "{ " << i.start << ", " << i.end << ", " << i.c << "}";
        return os;
    }
    int getStart() const {
        return start;
    }
    int getEnd() const {
        return end;
    }
    char getChar() const {
        return c;
    }
};

template<typename K, typename V> 
class interval_pair {
    interval_map<K, V> m1 = NULL;
    interval_map<K, V> m2 = NULL;

    public:

    interval_pair(const interval_map<K, V>& a, const interval_map<K, V>& b) {
        m1 = interval_map<K, V>(a);
        m2 = interval_map<K, V>(b);
    }
    
    friend ostream& operator<<(ostream& os, const interval_pair& ip) {
        int beg = (ip.m1.start() < ip.m2.start()) ? ip.m1.start() : ip.m2.start();
        int end = (ip.m1.ending() < ip.m2.ending()) ? ip.m2.ending() : ip.m1.ending();
        os << "i: m1:  m2:" << endl; 
        for(int i = beg; i <= end; i++) {
            os << i <<  ": " << ip.m1[i] << " " << ip.m2[i] << endl;
        }
        vector<string> m1_map = ip.m1.maplines();
        vector<string> m2_map = ip.m2.maplines();
        for(const string& s: m1_map) {
            os << s << endl;
        }
        for(const string& s: m2_map) {
            os << s << endl;
        }
        os << endl;
        return os;
    }
};


template<typename K, typename V> 
vector<string> result(const interval_map<K, V>& m1, const interval_map<K, V>& m2) {
    vector<string> v;
    //int beg = (m1.start() < m2.start()) ? m1.start() : m2.start();
    //int end = (m1.ending() < m2.ending()) ? m2.ending() : m1.ending();
    int beg = -10;
    int end = 20;
    v.push_back("i: m1:  m2:");
    for(int i = beg; i <= end; i++) {
        string line = "";
        line+= to_string(i);
        line+=": ";
        line+=m1[i];
        line+=" ";
        line+=m2[i];
        v.push_back(line);
    }
    vector<string> mlines = m1.maplines();
    v.insert(v.end(), mlines.begin(), mlines.end());
    mlines = m2.maplines();
    v.insert(v.end(), mlines.begin(), mlines.end());
    return v;
}
template<typename K, typename V> 
void print(const interval_map<K, V>& m1, const interval_map<K, V>& m2) {
    int beg = (m1.start() < m2.start()) ? m1.start() : m2.start();
    int end = (m1.ending() < m2.ending()) ? m2.ending() : m1.ending();
    cout << "i: m1:  m2:" << endl; 
    for(int i = beg; i <= end; i++) {
        cout << i <<  ": " << m1[i] << " " << m2[i] << endl;
    }
    m1.printmap();
    m2.printmap();
    cout << endl;
}
void testB() {
    interval_map<int, char> m1 = interval_map<int, char>('A');
    interval_map<int, char> m2 = interval_map<int, char>('A');

    ifstream myfile; 
    myfile.open("instructions.txt");
    vector<instruction> instructions;
    instruction i;
    while(myfile >> i) {
        instructions.push_back(i);
    }
    for(const auto& a: instructions) {
        vector<string> backup = result(m1, m2);
        m1.assign(a.getStart(), a.getEnd(), a.getChar());
        m2.assign2(a.getStart(), a.getEnd(), a.getChar());
        if(m1.result() != m2.result()) {
            cout << "failed at " << a << endl;
           // m1.print();
           // m2.print(); 
            break;
        }
        else {
            cout << "passed at " << a << endl; 
        }
    }
    vector<string> rs = result(m1, m2);
    for(const auto& s: rs) {
        cout << s << endl;
    }
    cout << endl;
    myfile.close();
}
void test() {
    interval_map<int, char> m = interval_map<int, char>('A');
}
int main() {
    testB();
}
// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.