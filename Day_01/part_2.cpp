#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const std::vector<int> INPUT = {/*assume I am filled*/};

int parse_get_amount(std::unordered_map<int, int> &map, int n, std::vector<int> &v) {
	int counter = 0;
	for(size_t i=0; i<v.size(); ++i) {
		if(v[i] == n) { ++counter; }
	}
	map[n] = counter;
	return counter*n;
}

int main() {
	std::vector<int> l_list = {};
	std::vector<int> r_list = {};
	for(size_t i=0; i<INPUT.size(); ++i) {
		if(i%2 == 0) { l_list.push_back( INPUT[i] ); } 
		else { r_list.push_back( INPUT[i] ); }
	}
	
	
	std::unordered_map<int, int> occurrences = {};
	long unsigned int similarity_score = 0;
	int current;
	for(size_t i=0; i<l_list.size(); ++i) {
		current = l_list[i];
		if(occurrences.count(current) != 0) {
			similarity_score += occurrences[current] * current;
		} else {
			similarity_score += parse_get_amount(occurrences, current, r_list);
		}
	}
	
	std::cout << "similarity_score: " << similarity_score << '\n';
	return 0;
}
