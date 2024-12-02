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

void get_vectors_from_file(std::string file_name, std::vector< std::vector<int> > &v) {
	std::ifstream file(file_name);
	if (file.is_open()) {
		std::string line;
		while(std::getline(file, line)) {
			v.push_back( split(line, " ") );
		}
		file.close();
	}
}

int is_safe(std::vector<int> &report) {
	int diff = report[1] - report[0];
	if(diff == 0 || diff>3 || diff<-3) { return 0; }
	
	int limit = report.size()-1;
	
	if(diff > 0) {
		// increasing
		for(size_t i=1; i<limit; ++i) {
			diff = report[i+1] - report[i];
			if((diff <= 0) || (diff > 3)) { return 0; }
		}
	} else {
		// decreasing
		for(size_t i=1; i<limit; ++i) {
			diff = report[i+1] - report[i];
			if((diff >= 0) || (diff < -3)) { return 0; }
		}
	}
	
	return 1;
}

int main() {
	std::vector< std::vector<int> > reports = {};
	get_vectors_from_file("aoc-02_data.txt", reports);
	
	int safe_amount = 0;
	for(size_t i=0; i<reports.size(); ++i) {
		safe_amount += is_safe(reports[i]);
	}
	std::cout << "safe_amount: " << safe_amount << '\n';
	
	return 0;
}
