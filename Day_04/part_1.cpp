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



int up_match(std::vector<std::string>& lines, int line, int x_pos) {
	if(
		lines[line-3][x_pos] == 'S' && 
		lines[line-2][x_pos] == 'A' && 
		lines[line-1][x_pos] == 'M'
	) {
		return 1;
	}
	return 0;
}
int diagonal_up_right(std::vector<std::string>& lines, int line, int x_pos) {
	if(x_pos > lines.size()-3) { return 0; }
	if(
		lines[line-3][x_pos+3] == 'S' && 
		lines[line-2][x_pos+2] == 'A' && 
		lines[line-1][x_pos+1] == 'M'
	) {
		return 1;
	}
	return 0;
}
int diagonal_up_left(std::vector<std::string>& lines, int line, int x_pos) {
	if(x_pos < 3) { return 0; }
	if(
		lines[line-3][x_pos-3] == 'S' && 
		lines[line-2][x_pos-2] == 'A' && 
		lines[line-1][x_pos-1] == 'M'
	) {
		return 1;
	}
	return 0;
}
int up_section(std::vector<std::string>& lines, int line, int x_pos) {
	if(line < 3) { return 0; }
	return (
		up_match(lines, line, x_pos) + 
		diagonal_up_right(lines, line, x_pos) + 
		diagonal_up_left(lines, line, x_pos)
	);
}


int down_match(std::vector<std::string>& lines, int line, int x_pos) {
	if(
		lines[line+1][x_pos] == 'M' && 
		lines[line+2][x_pos] == 'A' && 
		lines[line+3][x_pos] == 'S'
	) {
		return 1;
	}
	return 0;
}
int diagonal_down_right(std::vector<std::string>& lines, int line, int x_pos) {
	if(x_pos > lines.size()-4) { return 0; }
	if(
		lines[line+1][x_pos+1] == 'M' && 
		lines[line+2][x_pos+2] == 'A' && 
		lines[line+3][x_pos+3] == 'S'
	) {
		return 1;
	}
	return 0;
}
int diagonal_down_left(std::vector<std::string>& lines, int line, int x_pos) {
	if(x_pos < 3) { return 0; }
	if(
		lines[line+1][x_pos-1] == 'M' && 
		lines[line+2][x_pos-2] == 'A' && 
		lines[line+3][x_pos-3] == 'S'
	) {
		return 1;
	}
	return 0;
}
int down_section(std::vector<std::string>& lines, int line, int x_pos) {
	if(line > lines.size()-4) { return 0; }
	return (
		down_match(lines, line, x_pos) + 
		diagonal_down_right(lines, line, x_pos) + 
		diagonal_down_left(lines, line, x_pos)
	);
}



int find_xmas_matches(std::vector<std::string>& lines, int line, int x_pos) {
	return up_section(lines, line, x_pos) + down_section(lines, line, x_pos);
}

int main() {
	std::vector<std::string> lines = {};
	get_vectors_from_file("aoc-04_data.txt", lines);
	
	std::regex linear_xmas("XMAS|SAMX");
	std::smatch m;
	std::string::const_iterator searchStart;

	std::vector< std::vector<int> > lines_x_pos = {};
	std::vector<int> x_pos = {};
	
	int xmas_counter = 0;
	int curr_pos;
	bool new_position;
	std::string data;
	
	for(size_t j=0; j<lines.size(); ++j) {
		data = lines[j];
		
		x_pos = {};
		for(size_t i=0; i<data.size(); ++i) {
			if(data[i] == 'X') {
				new_position = true;
				for(size_t k=0; k<x_pos.size(); ++k) {
					if(x_pos[k] == i) { new_position = false; break; }
				}
				if(new_position) { x_pos.push_back(i); }
			}
		}
		lines_x_pos.push_back( x_pos );
		
		
		
		searchStart = data.cbegin();
		while( std::regex_search(searchStart, data.cend(), m, linear_xmas) ) {
			curr_pos = searchStart - data.cbegin() + m.position();
			if(m[0] == "SAMX") { curr_pos += 3; }
			// need to account for SMAXMAS or XMASMAX
			searchStart = m.suffix().first - 1;
			++xmas_counter;
		}
	}
	
	
	for(size_t i=0; i<lines_x_pos.size(); ++i) {
		for(size_t j=0; j<lines_x_pos[i].size(); ++j) {
			xmas_counter += find_xmas_matches(lines, i, lines_x_pos[i][j]);
		}
	}
	
	std::cout << "xmas_counter: " << xmas_counter << '\n';
	
	return 0;
}
