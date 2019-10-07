#pragma once
#ifndef PPM_DOC_HPP
#define PPM_DOC_HPP

#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "FileReader.h";
using namespace std;

class PpmDoc {

private:

	//names for variables come from ppm specs online - http://netpbm.sourceforge.net/doc/ppm.html 
	string _magic_number; //The format of the ppm document (only allows P3 or P6) 
	int _width = -1;
	int _height = -1;
	int _color_val = -1;
	string _file_name;

	void checkDocValidity(istream& stream) {

		if (stream.good() == false && stream.eof() == false) 
		{

			throw exception{ "Invalid PPM Specifications." };

		}

	}

public:
	//Constructor for our file 
	PpmDoc(string filename) {

		open(filename);

	}
	// Constructor for when a file name isnt supplied.
	PpmDoc() {

	}
	void open(string filename) {

		_file_name = filename;
		vector<string> temp_data = file_reader(filename);

		if (temp_data.size() == 0) {

			throw exception{ "Invalid PPM Specifications." };

		}
		else {

			_magic_number = temp_data[1];

			istringstream line{ temp_data[2] };
			line >> _width;
			line >> _height;
			checkDocValidity(line);

			line = istringstream{ temp_data[2] };
			line >> _color_val;
			checkDocValidity(line);

		}

	}




};




#endif // !PPM_DOC_HPP