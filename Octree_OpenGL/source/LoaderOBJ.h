#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<double> > LoadObj(const string filename) {

	vector<vector<double>> vertices;
	stringstream ss;
	ifstream ifs(filename.c_str(), std::ifstream::in);
	string line, key;
	
	if (!ifs.is_open()) 
		throw "Error::OBJLOADER::Could not open file";

	while (ifs.good() && !ifs.eof() && getline(ifs, line)) {
		key = "";
		stringstream stringstream(line);
		stringstream >> key >> std::ws;
		vector<double> temp;
		if (key == "v") {
			vector<double> v; double x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.push_back(x);
			}
			vertices.push_back(v);
		}
	}
	return vertices;
}


