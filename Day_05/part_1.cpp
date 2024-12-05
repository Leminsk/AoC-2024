#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<int> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end;
    std::string token;
    std::vector<int> res;

    while((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        res.push_back( std::stoi(token) );
    }

    res.push_back( std::stoi(s.substr(pos_start)) );
    return res;
}

void get_vectors_from_file(std::string file_name, std::vector< std::vector<int> >& rules, std::vector< std::vector<int> >& raw_updates) {
	std::ifstream file(file_name);
	bool rules_section = true;
	if (file.is_open()) {
		std::string line;
		while(std::getline(file, line)) {
			if(line == "") { 
				rules_section = false;
				continue;
			} else {
				if(rules_section) {
					rules.push_back( split(line, "|") );
				} else {
					raw_updates.push_back( split(line, ",") );
				}
			}
		}
		file.close();
	}
}

int get_position(std::vector<int>& v, int n) {
	for(size_t i=0; i<v.size(); ++i) {
		if(n == v[i]) { return i; }
	}
	return -1;
}

void get_rules(std::vector< std::vector<int> >& rules, std::vector<int>& update, std::vector< std::vector<int> >& output_rules) {
	for(size_t i=0; i<update.size(); ++i) {
		for(size_t j=0; j<rules.size(); ++j) {
			if(
				((rules[j][0] == update[i]) && (get_position(update, rules[j][1]) != -1)) ||
				((rules[j][1] == update[i]) && (get_position(update, rules[j][0]) != -1))
			) {
				output_rules.push_back( rules[j] );
			}
		}
	}
}

bool obeys_rules(std::vector< std::vector<int> >& rules, std::vector<int>& update) {
	std::vector<int> curr_rule;
	int pos_l, pos_r;
	for(size_t i=0; i<rules.size(); ++i) {
		curr_rule = rules[i];
		pos_l = get_position(update, curr_rule[0]);
		pos_r = get_position(update, curr_rule[1]);
		if(pos_l >= pos_r) {
			return false;
		}
	}
	return true;
}

int get_middle_value(std::vector<int>& v) {
	return v[ v.size()/2 ];
}

int main() {
	std::vector< std::vector<int> > rules = {};
	std::vector< std::vector<int> > raw_updates = {};
	get_vectors_from_file("aoc-05_data.txt", rules, raw_updates);
	
	long int counter = 0;
	std::vector< std::vector<int> > current_rules;
	std::vector<int> curr_update;
	for(size_t i=0; i<raw_updates.size(); ++i) {
		current_rules = {};
		curr_update = raw_updates[i];
		get_rules(rules, curr_update, current_rules);
		if( obeys_rules(current_rules, curr_update) ) {
			counter += get_middle_value(curr_update);
		}
	}
	
	std::cout << "counter: " << counter << '\n';
	
	return 0;
}
