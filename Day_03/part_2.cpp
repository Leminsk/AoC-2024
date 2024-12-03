#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_map>

std::string read_data(std::string file_name) {
	std::ifstream file(file_name);
	std::stringstream res;
	if (file.is_open()) {
		std::string line;
		while(std::getline(file, line)) {			
			res << line;
		}
		file.close();
	}
	return res.str();
}

int mul(std::string s) {
	char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	
    size_t pos_start = 0, pos_end;
    std::string token;
    std::vector<std::string> res;

    while((pos_end = s.find(",", pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        res.push_back(token);
    }
    res.push_back( s.substr(pos_start) );
	
	// if I got less than or more than 2 args then something has gone really bad
	std::stringstream arg1, arg2;
	bool is_digit;
	
	for(size_t i=0; i<res[0].size(); ++i) {
		is_digit = false;
		for(size_t j=0; j<10; ++j) {
			if(res[0][i] == digits[j]) { is_digit = true; break; }
		}
		if(is_digit) { arg1 << res[0][i]; }
	}
	
	for(size_t i=0; i<res[1].size(); ++i) {
		is_digit = false;
		for(size_t j=0; j<10; ++j) {
			if(res[1][i] == digits[j]) { is_digit = true; break; }
		}
		if(is_digit) { arg2 << res[1][i]; }
	}
	
	return std::stoi(arg1.str()) * std::stoi(arg2.str());
}


int main() {
	std::string data = read_data("aoc-03_data.txt");
	
	std::regex r("(mul\\(\\d{1,3},\\d{1,3}\\))");
	std::regex do_ex("do\\(\\)");
	std::regex dont_ex("don't\\(\\)");
	std::smatch m;
	
	std::vector<int> match_positions;
	std::vector<bool> to_add;
	std::vector<int> do_positions;
	std::vector<int> dont_positions;
	std::vector<std::string> operations;
	long int res = 0;
	
	match_positions = {};
	to_add = {};
	do_positions = {};
	dont_positions = {};
	operations = {};
	
	std::string::const_iterator searchStart;

	searchStart = data.cbegin();
	// dang it don't have /g in C++?
	while( std::regex_search(searchStart, data.cend(), m, r) ) {
		match_positions.push_back( searchStart - data.cbegin() + m.position() );
		operations.push_back(m[0]);
		to_add.push_back(true);
		searchStart = m.suffix().first;
	}
	searchStart = data.cbegin();
	while( std::regex_search(searchStart, data.cend(), m, do_ex) ) {
		do_positions.push_back( searchStart - data.cbegin() + m.position() );
		searchStart = m.suffix().first;
	}
	searchStart = data.cbegin();
	while( std::regex_search(searchStart, data.cend(), m, dont_ex) ) {
		dont_positions.push_back( searchStart - data.cbegin() + m.position() );
		searchStart = m.suffix().first;
	}
	
	int min_do;
	int min_do_index = -1;
	int min_dont;
	int min_dont_index = -1;
	int diff;
	for(size_t j=0; j<match_positions.size(); ++j) {
		min_do = 1000000;
		for(size_t k=0; k<do_positions.size(); ++k) {
			diff = match_positions[j] - do_positions[k];
			if((diff>0) && (diff<min_do)){
				min_do = diff;
				min_do_index = k;
			}
		}
		min_dont = 1000000;
		for(size_t k=0; k<dont_positions.size(); ++k) {
			diff = match_positions[j] - dont_positions[k];
			if((diff>0) && (diff<min_dont)){
				min_dont = diff;
				min_dont_index = k;
			}
		}
		
		if(min_do_index==-1 && min_dont_index==-1) { 
			res += mul(operations[j]);
		} else {
			if((min_do_index != -1) && min_dont >= min_do) {
				res += mul(operations[j]);
			}
		}
	}
	
	
    std::cout << "res: " << res << '\n';
	
	
	return 0;
}
