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

	//The format of the ppm document (only allows P3 or P6) 
	string _magic_number;

	//The width of the picture
	int _width = -1;

	//The height of the picture
	int _height = -1;

	//The maximum color value for each color
	int _color_val = -1;

	//The name of the file
	string _file_name;

	//Vector of Pixels
	vector<Pixel> _pixel_data;

	//error check to see if file was input correctly
	void checkDocValidity(istream& stream) {
		try {
			if (stream.good() == false && stream.eof() == false) {
				throw exception{ "Invalid PPM Specifications." };
			}
		}
		catch (const char* msg) {
			cerr << msg << endl;
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

	//function to read file into data
	void open(string filename) {

		//sets ppm _file_name
		_file_name = filename;

		//parses file and reads it into vector of strings
		vector<string> temp_data = file_reader(filename);

		//error check to see if file was read correctly
		if (temp_data.size() == 0) {

			throw exception{ "Invalid PPM Specifications." };

		}
		else {

			//set magic number
			_magic_number = temp_data[0];

			//seperate the second line to get the width and height seperately and make them ints instead of strings
			istringstream line{ temp_data[1] };

			//assign width
			line >> _width;

			//assign height
			line >> _height;

			//error check
			checkDocValidity(line);

			//makes the color value a integer instead of a string
			line = istringstream{ temp_data[2] };

			//assign color value
			line >> _color_val;
			
			//error check
			checkDocValidity(line);

			//read the color data and make them a vector of pixels
			for (int i = 3; i < temp_data.size(); i++) {
				//if (temp_data[i].length() > 0) {

					//seperate the data on each line and make them integers when we put them into the pixel
					istringstream line_data{ temp_data[i] };

					//while the line hasn't ended do this
					while (line_data.eof() == false ) {

						//call basic pixel
						Pixel a;
						
						// take the next values on the line and put them into the pixel
						line_data >> a;

						//error check
						checkDocValidity(line_data);

						//error check
						if (a.checkPixel() == true) {
							//add pixel to vector
							_pixel_data.push_back(a);
						}
						
					}
				
			}
		}
	}

	//getter for _magic_num
	string getMagicNum() const {
		return _magic_number;
	}

	//setter for _magic_num
	void setMagicNum(const string& num) {
		try {
			if (num == "P3" || num == "P6") {
				_magic_number = num;
			}
			else {
				throw exception{ "Invalid PPM Specifications." };
			}
		}
		catch (const char* msg) {
			cerr << msg << endl;
		}
	}

	//getter for _width
	int getWidth() const {
		return _width;
	}
	
	//getter for _height
	int getHeight() const {
		return _height;
	}

	//getter for _color_val
	int getColorVal() const {
		return _color_val;
	}

	//getter for _file_name
	string getFilename() const {
		return _file_name;
	}

	//setter for _file_name
	void setFilename(const string& file_name) {
		_file_name = file_name;
	}

	//remove color for all Pixels in pixel vector
	void removePixels(const char& color) {
		for (auto& Pixel : _pixel_data) {
			Pixel.removeColor(color);
		}
	}
	
	//negate color for all Pixels in pixel vector
	void negatePixels(const char& color) {
		for (auto& Pixel : _pixel_data) {
			Pixel.negateColor(color);
		}
	}

	//greyscale color for all Pixels in pixel vector
	void grayscalePixels() {
		for (auto& Pixel : _pixel_data) {
			Pixel.grayscale();
		}
	}

	//takes int as parameter to choose how to edit the picture
	void ImageManip(const int& selection) {
		try {
			switch (selection) {
				//remove red from pixels
			case 1:
				removePixels('r');
				cout << "Applying Remove Red effect..." << endl;
				break;
			case 2:
				//remove green from pixels
				removePixels('g');
				cout << "Applying Remove Green effect..." << endl;
				break;
			case 3:
				//remove blue from pixels
				removePixels('b');
				cout << "Applying Remove Blue effect..." << endl;
				break;
			case 4:
				//negate red from pixels
				negatePixels('r');
				cout << "Applying Negate Red effect..." << endl;
				break;
			case 5:
				//negate green from pixels
				negatePixels('g');
				cout << "Applying Negate Green effect..." << endl;
				break;
			case 6:
				//negate blue from pixels
				negatePixels('b');
				cout << "Applying Negate Blue effect..." << endl;
				break;
			case 7:
				//greyscale picture
				grayscalePixels();
				cout << "Applying Grayscale effect..." << endl;
				break;
			default:
				//No selection made
				throw exception{ "Invalid Selection" };
				break;
			}
		}
		//catch errors
		catch (const char* msg) {
			cerr << msg << endl;
		}
	}


	friend ostream& operator<<(ostream& stream, const PpmDoc& ppm);
};

//write to a new file
ostream& operator<<(ostream& stream, const PpmDoc& ppm) {

	//put in magic number
	stream << ppm.getMagicNum() << endl;

	//put in width and height 
	stream << ppm.getWidth() << " " << ppm.getHeight() << endl;

	//put in color value
	stream << ppm.getColorVal() << endl;

	//counter to arrange rows with the ammount of pixels as the width
	int width_counter = 1;

	//read all pixels to the stream
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