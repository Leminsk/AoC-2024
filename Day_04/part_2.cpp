#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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

// hey if it's dumb but it works, maybe it's not that stupid (just not elegant))
int has_cross_mas(std::vector<std::string>& lines, int dimension, int line, int col) {
	if(
		(line < 1) || (line > dimension-2) || 
		(col < 1) || (col > dimension-2)
	) { 
		return 0;
	}
	if( // top-left_bottom-right diagonal
		((lines[line-1][col-1] == 'M' && lines[line+1][col+1] == 'S') || (lines[line-1][col-1] == 'S' && lines[line+1][col+1] == 'M')) &&
		// bottom-left_top-right diagonal
		((lines[line+1][col-1] == 'M' && lines[line-1][col+1] == 'S') || (lines[line+1][col-1] == 'S' && lines[line-1][col+1] == 'M'))
	) {
		return 1;
	}
	return 0;
}

int find_xmas_matches(std::vector<std::string>& lines) {
	int dimension = lines.size();
	int cross_mas = 0;
	for(size_t line=0; line<dimension; ++line) {
		for(size_t col=0; col<dimension; ++col) {
			if(lines[line][col] == 'A') {
				cross_mas += has_cross_mas(lines, dimension, line, col);
			}
		}
	}
	return cross_mas;
}

int main() {
	std::vector<std::string> lines = {};
	get_vectors_from_file("aoc-04_data.txt", lines);
	
	
	std::cout << "xmas_counter: " << find_xmas_matches(lines) << '\n';
	
	return 0;
}
