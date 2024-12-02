#include <iostream>
#include <vector>
#include <algorithm>

const std::vector<int> INPUT = { /*assume I am filled*/ };

int compare(int a, int b) {
	return a < b;
}

int main() {
	std::vector<int> l_list = {};
	std::vector<int> r_list = {};
	for(size_t i=0; i<INPUT.size(); ++i) {
		if(i%2 == 0) { l_list.push_back( INPUT[i] ); } 
		else { r_list.push_back( INPUT[i] ); }
	}
	
	std::sort(l_list.begin(), l_list.end(), compare);
	std::sort(r_list.begin(), r_list.end(), compare);

	long unsigned int counter = 0;
	for(size_t i=0; i<l_list.size(); ++i) {
		if(l_list[i] < r_list[i]) {
			counter += (r_list[i] - l_list[i]);
		} else {
			counter += (l_list[i] - r_list[i]);
		}
	}
	
	std::cout << "counter: " << counter << '\n';
	return 0;
}
