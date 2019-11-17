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

	// A vector that contains vectors of pixels
	//Not needed for basic edits, cases 1-9 in ImageManip function 
	//1-9 can be achived using a vector of pixels and some more lines of code for formatting 
	//but needed for the more complex edits
	vector<vector<Pixel>> _line_data;

	//error check to see if file was input correctly
	void checkDocValidity(istream& stream) {
		try {
			if (stream.good() == false && stream.eof() == false) {
				throw exception{ "Invalid PPM Specifications." };
			}
		}catch (const char* msg) {
			cerr << msg << endl;
		}
	}

	//sets the width of the ppm file
	void setWidth(const int& w) {
		_width = w;
	}

	//sets the height of the ppm file
	void setHeight(const int& h) {
		_height = h;
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

			//Vector of Pixels
			vector<Pixel> _pixel_data;

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
				//seperate the data on each line and make them integers when we put them into the pixel
				istringstream line_data{ temp_data[i] };

				//while the line hasn't ended do this
				while (line_data.eof() == false ) {
					//call basic pixel
					Pixel a;

					//sets max color value inside of pixel
					a.setMax(getColorVal());

					// take the next values on the line and put them into the pixel
					line_data >> a;
						
					//error check
					checkDocValidity(line_data);

					// error check to see if pixel was populated
					if (a.checkPixel() == true) {
							_pixel_data.push_back(a);
					}

					if ((_pixel_data.size() % getWidth() == 0) && _pixel_data.size() > 0) {
						_line_data.push_back(_pixel_data);
						_pixel_data.clear();
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
			}else {
				throw exception{ "Invalid PPM Specifications." };
			}
		}catch (const char* msg) {
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
		for (int i = 0; i < _line_data.size(); i++) {
			for (auto& Pixel : _line_data[i]) {
				Pixel.removeColor(color);
			}
		}
	}
	
	//negate color for all Pixels in pixel vector
	void negatePixels(const char& color) {
		for (int i = 0; i < _line_data.size(); i++) {
			for (auto& Pixel : _line_data[i]) {
				Pixel.negateColor(color);
			}
		}
	}

	//greyscale color for all Pixels in pixel vector
	void grayscalePixels() {
		for (int i = 0; i < _line_data.size(); i++) {
			for (auto& Pixel : _line_data[i]) {
				Pixel.grayscale();
			}
		}
	}

	//adds random noise for all Pixels in pixel vector
	void noisePixels() {
		for (int i = 0; i < _line_data.size(); i++) {
			for (auto& Pixel : _line_data[i]) {
				Pixel.randomNoise();
			}
		}
	}

	//changes contrast to high for all Pixels in pixel vector
	void contrastPixels() {
		for (int i = 0; i < _line_data.size(); i++) {
			for (auto& Pixel : _line_data[i]) {
				Pixel.pixelContrast();
			}
		}
	}

	//Flips the picture across the x-axis
	void hor_flip() {
		vector<vector<Pixel>> temp_data;
		for (int j = 0; j < getHeight(); j++) {
			vector<Pixel> temp_line;
			for (int i = (getWidth() - 1); i >= 0; i--) {
				temp_line.push_back(_line_data[j][i]);
			}
			temp_data.push_back(temp_line);
		}
		_line_data.clear();
		_line_data = temp_data;
	}

	//Flips the picture across the y-axis
	void ver_flip() {
		vector<vector<Pixel>> temp_data;
		for (int j = (getHeight() - 1); j >= 0; j--) {
			temp_data.push_back(_line_data[j]);
		}
		_line_data.clear();
		_line_data = temp_data;
	}

	//Rotates the picture 90 Degrees clock-wise
	void rotate_90() {
		vector<vector<Pixel>> temp_data;
		int temp = 0;
		for (int i = 0; i < getWidth(); i++) {
			vector<Pixel> temp_line;
			for (int j = (getHeight() - 1); j >= 0; j--) {
				temp_line.push_back(_line_data[j][i]);
			}
			temp_data.push_back(temp_line);
		}
		_line_data.clear();
		_line_data = temp_data;
		setWidth(getHeight());
		setHeight(_line_data.size());
	}

	//Rotates the picture 180 Degrees clock-wise
	void rotate_180() {
		hor_flip();
		ver_flip();
	}

	//Rotates the picture 270 Degrees clock-wise
	void rotate_270() {
		rotate_180();
		rotate_90();
	}

	void pixelate(int distance) {
		vector<vector<Pixel>> temp_matrix;
		vector<Pixel> temp_line;
		for (int j = 0; j < _line_data.size(); j++) {
			Pixel temp_pixel;
			if (j % distance == 0){
				temp_line.clear();
				for (int i = 0; i < _line_data[j].size(); i++) {
					if (i % distance == 0) {
						temp_pixel = _line_data[j][i];
						temp_line.push_back(temp_pixel);
					}
					else {
						temp_line.push_back(temp_pixel);
					}
				}
				temp_matrix.push_back(temp_line);
			}
			else {
				temp_matrix.push_back(temp_line);
			}
		}
		_line_data.clear();
		_line_data = temp_matrix;
		
	}

	//Blurs the picture once horizontally
	void blur_hor(){
		vector<vector<Pixel>> temp_data;
		for (int j = 0; j < _line_data.size(); j++) {
			vector<Pixel> temp_line;
			for (int i = 0; i < _line_data[j].size(); i++) {
				Pixel a;
				a.setMax(getColorVal());
				int temp_red = 0;
				int temp_green = 0;
				int temp_blue = 0;
				if (i == 0) {
					temp_red = ((_line_data[j][i].getRed() + _line_data[j][i + 1].getRed())/2);
					temp_green = ((_line_data[j][i].getGreen() + _line_data[j][i + 1].getGreen()) / 2);
					temp_blue = ((_line_data[j][i].getBlue() + _line_data[j][i + 1].getBlue()) / 2);
					a.setPixel(temp_red, temp_green, temp_blue);
					temp_line.push_back(a);
				}else if (i == _line_data[j].size() - 1){
					temp_red = ((_line_data[j][i - 1].getRed() + _line_data[j][i].getRed()) / 2);
					temp_green = ((_line_data[j][i - 1].getGreen() + _line_data[j][i].getGreen()) / 2);
					temp_blue = ((_line_data[j][i - 1].getBlue() + _line_data[j][i].getBlue()) / 2);
					a.setPixel(temp_red, temp_green, temp_blue);
					temp_line.push_back(a);
				}else {
					temp_red = ((_line_data[j][i - 1].getRed() + _line_data[j][i].getRed() + _line_data[j][i + 1].getRed()) / 3);
					temp_green = ((_line_data[j][i - 1].getGreen() + _line_data[j][i].getGreen() + _line_data[j][i + 1].getGreen()) / 3);
					temp_blue = ((_line_data[j][i - 1].getBlue() + _line_data[j][i].getBlue() + _line_data[j][i + 1].getBlue()) / 3);
					a.setPixel(temp_red, temp_green, temp_blue);
					temp_line.push_back(a);
				}
			}
			temp_data.push_back(temp_line);
		}
		_line_data.clear();
		_line_data = temp_data;
	}

	//Blurs the pictures once vertically
	void blur_ver() {
		vector<vector<Pixel>> temp_data;
		temp_data.resize(getHeight());
		for (int i = 0; i < getWidth(); i++) {
			vector<Pixel> temp_line;
			for (int j = 0; j < _line_data.size(); j++) {
				Pixel a;
				a.setMax(getColorVal());
				int temp_red = 0;
				int temp_green = 0;
				int temp_blue = 0;
				if (j == 0) {
					temp_red = ((_line_data[j][i].getRed() + _line_data[j + 1][i].getRed()) / 2);
					temp_green = ((_line_data[j][i].getGreen() + _line_data[j + 1][i].getGreen()) / 2);
					temp_blue = ((_line_data[j][i].getBlue() + _line_data[j + 1][i].getBlue()) / 2);
				}
				else if (j == (_line_data.size() - 1)) {
					temp_red = ((_line_data[j - 1][i].getRed() + _line_data[j][i].getRed()) / 2);
					temp_green = ((_line_data[j - 1][i].getGreen() + _line_data[j][i].getGreen()) / 2);
					temp_blue = ((_line_data[j - 1][i].getBlue() + _line_data[j][i].getBlue()) / 2);
				}
				else {
					temp_red = ((_line_data[j - 1][i].getRed() + _line_data[j][i].getRed() + _line_data[j + 1][i].getRed()) / 3);
					temp_green = ((_line_data[j - 1][i].getGreen() + _line_data[j][i].getGreen() + _line_data[j + 1][i].getGreen()) / 3);
					temp_blue = ((_line_data[j - 1][i].getBlue() + _line_data[j][i].getBlue() + _line_data[j + 1][i].getBlue()) / 3);
					a.setPixel(temp_red, temp_green, temp_blue);
					temp_data[j].push_back(a);
				}
				a.setPixel(temp_red, temp_green, temp_blue);
				temp_data[j].push_back(a);
			}
		}
		_line_data.clear();
		_line_data = temp_data;
	}

	//Blurs the picture once, horizontally, and then vertically
	void blur_single() {
		blur_hor();
		blur_ver();
	}

	//Blurs the picture 10 times,using the full blur loop (blur_single())
	void blur() {
		for (int i = 0; i < 10; i++) {
			blur_single();
		}
	}

	//takes int as parameter to choose how to edit the picture
	void ImageManip(const int& selection) {
		int temp = 1;
		try {
			switch (selection) {
				//remove red from pixels
			case 1:
				removePixels('r');
				cout << "Applying Remove Red effect..." ;
				break;
			case 2:
				//remove green from pixels
				removePixels('g');
				cout << "Applying Remove Green effect..." ;
				break;
			case 3:
				//remove blue from pixels
				removePixels('b');
				cout << "Applying Remove Blue effect..." ;
				break;
			case 4:
				//negate red from pixels
				negatePixels('r');
				cout << "Applying Negate Red effect..." ;
				break;
			case 5:
				//negate green from pixels
				negatePixels('g');
				cout << "Applying Negate Green effect..." ;
				break;
			case 6:
				//negate blue from pixels
				negatePixels('b');
				cout << "Applying Negate Blue effect..." ;
				break;
			case 7:
				//greyscale picture
				grayscalePixels();
				cout << "Applying Grayscale effect..." ;
				break;
			case 8:
				//Add random noise to picture
				noisePixels();
				cout << "Applying Random Noise effect..." ;
				break;
			case 9:
				//Add high constrast to picture
				contrastPixels();
				cout << "Applying High Constrast effect..." ;
				break;
			case 10:
				//Flips the Picture Horizontally
				hor_flip();
				cout << "Applying Horizontal Flip effect...";
				break;
			case 11:
				//Flips the Picture Horizontally
				ver_flip();
				cout << "Applying Vertical Flip effect...";
				break;
			case 12:
				//Rotates the picture 90 Degrees clockwise
				rotate_90();
				cout << "Applying 90 Degree Rotation...";
				break;
			case 13:
				//Rotates the picture 90 Degrees clockwise
				rotate_180();
				cout << "Applying 180 Degree Rotation...";
				break;
			case 14:
				//Rotates the picture 90 Degrees clockwise
				rotate_270();
				cout << "Applying 270 Degree Rotation...";
				break;
			case 15:
				//Pixelates the image
				cout << "Please enter the distance: ";
				cin >> temp;
				pixelate(temp);
				cout << endl << "Applying pixelation effect...";
				break;
			case 16:
				//Blurs the image
				blur();
				cout << "Applying Blur effect...";
				break;
			case 0:
				//Choice to exit the function
				cout << "Done. Exiting Program...";
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

	//read all pixels to the stream

	for (auto vector : ppm._line_data) {
		for (int i = 0; i < vector.size(); i++) {
			stream << vector[i];
			stream << " ";
		}
		stream << endl;
	}

	return stream;
}



#endif // !PPM_DOC_HPP