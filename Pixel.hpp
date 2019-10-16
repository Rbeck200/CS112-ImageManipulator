#pragma once
#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "FileReader.h";
using namespace std;

class Pixel
{

private:

	//color value for red in pixel
	int _red = 0;

	//color value for green in pixel
	int _green = 0;

	//color value for blue in pixel
	int _blue = 0;



public:
	//constructor for the pixel
	Pixel(int red, int green, int blue) {
		setPixel(red, green, blue);
	}

	//do nothing constructor for pixel
	Pixel(){
	}

	//setter for red value
	void setRed(const int& red) {
		_red = red;
	}

	//getter for red value
	int getRed() {
		return _red;
	}

	//setter for green value
	void setGreen(const int& green) {
		_green = green;
	}

	//getter for green value
	int getGreen() {
		return _green;
	}

	//setter for blue value
	void setBlue(const int& blue) {
		_blue = blue;
	}

	//getter for blue value
	int getBlue() {
		return _blue;
	}

	//setter for all pixel values
	void setPixel(const int& red, const int& green, const int& blue) {
		setRed(red);
		setGreen(green);
		setBlue(blue);
	}

	//remove a color by setting its value to zero based on what char is passed to it
	void removeColor(const char& color) {
		
		switch (color) {
		case 'r': 			
				_red = 0;		
				  break;
		case 'g': 			
				_green = 0;
			
				  break;
		case 'b': 
				_blue = 0;
				  break;
		}
	}	

	//negate a color by setting its value to 255 - its current value based on what char is passed to it 
	void negateColor(const char& color) {
			switch (color) {
			case 'r':
				_red = 255 - _red;
				break;
			case 'g':
				_green = 255 - _green;

				break;
			case 'b':
				_blue = 255 - _blue;
				break;
			}
	}

	//greyscales the image by averaging its values and setting and setting ALL of the values to the result
	void grayscale() {
		int temp = 0;
		temp = (_red + _green + _blue)/3;
		setPixel(temp, temp, temp);
	}

	//error check to see if pixel was populated with data
	bool checkPixel() {
		if (_red == -1 || _green == -1 || _blue == -1) {
			return false;
		}
		return true;
	}
};

//write to a pixel
istream& operator>>(istream& stream, Pixel& pixel){
	//sets local variables in the function
		int r = -1;
		int g = -1;
		int b = -1;

	// passes the data from the stream into variables
		stream >> r >> g >> b;

	//calls setPixel
		pixel.setPixel(r, g, b);

	return stream;
}

//writes a pixel out to a file
ostream& operator<<(ostream& stream, Pixel& pixel){
	stream << pixel.getRed() << " " << pixel.getGreen() << " " << pixel.getBlue();
	return stream;
}

#endif // !PIXEL_HPP
