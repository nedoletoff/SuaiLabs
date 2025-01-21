#pragma once
#include <iostream>
#include <set>

class mySet : public std::set<int>{
	public:
		mySet combine(const mySet& a) {
			mySet c;
                        for (auto e1 : a)
                                for (auto e2 : *this)
                                        if (e1 == e2)
                                                c.insert(e1);
			            
                        return c;
		}
		mySet intersect(const mySet& a)
 {
			std::set<int> c = a;
                        mySet b = *this;
			b.merge(c);
			return b;
		}

		mySet minus(const mySet& a) {
			mySet r;
                        mySet b;
			r = this->combine(a);
			b = this->intersect(a);
			for (auto e : r)
				b.erase(e);
			return b;
		}	

};
