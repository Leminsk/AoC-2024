#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

void get_vectors_from_file(std::string file_name, std::vector<std::string> &v) {	
	std::ifstream file(file_name);
	if (file.is_open()) {
		std::string line;
		while(std::getline(file, line)) {			
			v.push_back(line);
		}
		file.close();
	}
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
	std::vector<std::string> mem_lines = {};
	get_vectors_from_file("aoc-03_data.txt", mem_lines);
	
	std::regex r("(mul\\(\\d{1,3},\\d{1,3}\\))");
	std::smatch m;
	
	std::vector<std::string> operations;
	long int res = 0;
	
	for(size_t i=0; i<mem_lines.size(); ++i) {
		operations = {};
		std::string::const_iterator searchStart(mem_lines[i].cbegin());
		// dang it don't have /g in C++?
		while( std::regex_search(searchStart, mem_lines[i].cend(), m, r) ) {
			operations.push_back(m[0]);
			searchStart = m.suffix().first;
		}
		
		for(size_t j=0; j<operations.size(); ++j) {
			res += mul(operations[j]);
		}
	}
	
    std::cout << "res: " << res << '\n';
	
	
	return 0;
}
