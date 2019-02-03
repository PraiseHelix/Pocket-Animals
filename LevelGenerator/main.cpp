#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "json.hpp"

std::string makeTile(unsigned int pos, unsigned char ID) {
	std::string tile =
		"{\n  \"" +
		std::to_string(pos) +
		"\": {\n" +
		"    \"type\": " +
		std::to_string(ID) +
		",\n" +
		"    \"data\": {}\n" +
		"  }\n" +
		"},\n";
	return tile;
}

std::vector<std::string> readFile(std::string fileName) {
	std::ifstream file(fileName, std::ios::binary | std::ios::ate);
	auto size = file.tellg();
	file.seekg(0);
	unsigned int width;
	bool widthFlag = false;
	char buf[256];

	std::vector<std::string> v;

	if (file.is_open()) {
		unsigned int c = 0;
		for (unsigned int i = 0; i < size; i+=256) {
			file.read(buf, 256);
			for(unsigned int j=0; j<256; j++){
				if (buf[j] == 0x7F && !widthFlag){
					width = j; widthFlag = true; continue;
				}
				else if (buf[j] == 0x7F && widthFlag) {
					continue;
				}
				else {
					v.push_back(makeTile(c, buf[j]));
					c++;
				}
			}
		}
	}
	file.close();
	std::cout << "Width:\t" << width << std::endl;
	return v;
}

void genereateLevel(std::string input, std::string output) {
	auto v = readFile(input);
	std::ofstream file(output);

	for (auto &i : v) {
		file << i;
	}
}

int main(int argc, char *argv[]) {
	if (argc == 2) {
		std::string arg1 = argv[1];
		if (arg1 == "-h" || arg1 == "help") {
			std::cout << "[flag] <input file> <output file>" << std::endl << std::endl;

			std::cout << "-g:\t\t" << "Generates a json file from a binary 8bpp image file." << std::endl;
			std::cout << "-h:\t\t" << "Shows information about this program." << std::endl;
		}
		else if (arg1 == "-g") {
			std::cout << "No input/output file" << std::endl;
		}
	}
	else if (argc >= 2) {
		std::string arg1 = argv[1];
		std::string arg2 = argv[2];
		std::string arg3 = argv[3];
		if (arg1 == "-g") {
			std::cout << "Generating json..." << std::endl;
			genereateLevel(arg2, arg3);
			std::cout << "Finsihed generating." << std::endl;
		}
		else {
			std::cout << "Invalid input:\t" << arg1 << std::endl;
		}
	}	
	return 0;
}