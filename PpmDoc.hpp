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
#include "Pixel.hpp"
using namespace std;

class PpmDoc {

private:

	//names for variables come from ppm specs online - http://netpbm.sourceforge.net/doc/ppm.html 
	string _magic_number; //The format of the ppm document (only allows P3 or P6) 
	int _width = -1;
	int _height = -1;
	int _color_val = -1;
	string _file_name;
	vector<Pixel> _pixel_data;

	void checkDocValidity(istream& stream) {

		if (stream.good() == false && stream.eof() == false) {
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

			_magic_number = temp_data[0];

			istringstream line{ temp_data[1] };
			line >> _width;
			line >> _height;
			checkDocValidity(line);

			line = istringstream{ temp_data[2] };
			line >> _color_val;
			checkDocValidity(line);

			for (int i = 3; i < temp_data.size(); i++) {
				if (temp_data[i].length() > 0) {
					istringstream line_data{ temp_data[i] };
					while (line_data.eof() == false) {
						Pixel a;
						line_data >> a;
						checkDocValidity(line_data);
						if (a.checkPixel == true) {
							_pixel_data.push_back(a);
						}
						
					}
				}
			}
		}
	}

	string getMagicNum() const {
		return _magic_number;
	}

	void setMagicNum(const string& num) {
		if (num == "P3" || num == "P6") {
			_magic_number = num;
		}else {
			throw exception{ "Invalid PPM Specifications." };
		}
	}

	int getWidth() const {
		return _width;
	}

	int getHeight() const {
		return _height;
	}

	int getColorVal() const {
		return _color_val;
	}

	string getFilename() const {
		return _file_name;
	}

	void setFilename(const string& file_name) {
		_file_name = file_name;
	}

	void removePixels(const char& color) {
		for (auto& Pixel : _pixel_data) {
			Pixel.removeColor(color);
		}
	}
	
	void negatePixels(const char& color) {
		for (auto& Pixel : _pixel_data) {
			Pixel.negateColor(color);
		}
	}

	void grayscalePixels() {
		for (auto& Pixel : _pixel_data) {
			Pixel.grayscale();
		}
	}

	void ImageManip(const int& selection) {
		switch (selection) {
		case 1:
			removePixels('r');
			cout << "Applying Remove Red effect..." << endl;
			break;
		case 2:
			removePixels('g');
			cout << "Applying Remove Green effect..." << endl;
			break;
		case 3:
			removePixels('b');
			cout << "Applying Remove Blue effect..." << endl;
			break;
		case 4:
			negatePixels('r');
			cout << "Applying Negate Red effect..." << endl;
			break;
		case 5:
			negatePixels('g');
			cout << "Applying Negate Green effect..." << endl;
			break;
		case 6:
			negatePixels('b');
			cout << "Applying Negate Blue effect..." << endl;
			break;
		case 7:
			grayscalePixels();
			cout << "Applying Grayscale effect..." << endl;
			break;
		default:
			throw exception{ "Invalid Selection" };
			break;
		}
	}


	friend ostream& operator<<(ostream& stream, const PpmDoc& ppm);
};

ostream& operator<<(ostream& stream, const PpmDoc& ppm) {
	stream << ppm.getMagicNum() << endl;
	stream << ppm.getWidth() << " " << ppm.getHeight() << endl;
	stream << ppm.getColorVal() << endl;
	int width_counter = 1;
	for (auto Pixel : ppm._pixel_data) {
		width_counter++;
		stream << Pixel;
		if (width_counter > ppm._width) {
			stream << endl;
			width_counter = 1;
		}else {
			stream << " ";
		}
		
	}
		return stream;
}



#endif // !PPM_DOC_HPP