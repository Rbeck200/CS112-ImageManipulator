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

class Pixel{
private:
	//color value for red in pixel
	int _red = 0;

	//color value for green in pixel
	int _green = 0;

	//color value for blue in pixel
	int _blue = 0;

	//max integer one of our color values can be
	int _max_value = 0;

public:
	//constructor for the pixel
	Pixel(int max, int red, int green, int blue) {
		setPixel(red, green, blue);
	}

	//do nothing constructor for pixel
	Pixel(){
	}

	//setter for red value
	void setRed(const int& red) {
		_red = valueCheck(red);
	}

	//getter for red value
	int getRed() {
		return _red;
	}

	//setter for green value
	void setGreen(const int& green) {
		_green = valueCheck(green);
	}

	//getter for green value
	int getGreen() {
		return _green;
	}

	//setter for blue value
	void setBlue(const int& blue) {
		_blue = valueCheck(blue);
	}

	//getter for blue value
	int getBlue() {
		return _blue;
	}

	//setter for max color value
	void setMax(const int& max) {
		_max_value = max;
	}

	//getter for max color value
	int getMax() {
		return _max_value;
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
				setRed(0);		
				  break;
		case 'g': 			
				setGreen(0);
				  break;
		case 'b': 
				setBlue(0);
				  break;
		}
	}	

	//negate a color by setting its value to 255 - its current value based on what char is passed to it 
	void negateColor(const char& color) {
			switch (color) {
			case 'r':
				setRed(255 - _red);
				break;
			case 'g':
				setGreen(255 - _green);

				break;
			case 'b':
				setBlue(255 - _blue);
				break;
			}
	}

	//greyscales the image by averaging its values and setting and setting ALL of the values to the result
	void grayscale() {
		int temp = 0;
		temp = (getRed() + getGreen() + getBlue())/3;
		setPixel(temp, temp, temp);
	}

	// Generates a random number from -10 to 10 and adds it to each value of a pixel
	void randomNoise() {
		int noise = (rand() % 21) - 10;
		setPixel((getRed() + (noise)), 
			((getGreen() + (noise))), 
			((getBlue() + (noise))));
	}

	// Calculates high contrast for single color value
	int highContrast(const int& color, const int& max_color_val) {
		int result = 0;
		if (color > (max_color_val/2)) {
			result = max_color_val;
		}
		return result;
	}

	//sets pixel to values derived from highContrast()
	void pixelContrast() {
		setPixel(highContrast(getRed(), _max_value), 
			highContrast(getGreen(), _max_value),
			highContrast(getBlue(), _max_value));
	}

	//error check to see if the pixel is inbetween our bounds i.e. 0 to _max_value
	int valueCheck(const int& color) {
		int result = color;
		//less than zero 
		if (color < 0 && color > -_max_value) {
			result = 0;
		}
		if (color > _max_value) {
			result = _max_value;
		}
		return result;
	}

	//error check to see if pixel was populated with data
	//if not populated it will equal negative of the max color value minus one
	//as to always have a number that will be out of bounds (because we could
	//change the parameters on teh contrast function to make it more than -10 
	//to 10, but it will always have less than the max value, which means it
	//always has to be more than the negative max value.)
	bool checkPixel() {
		if (_red == (-(_max_value)-1)
			|| _green == (-(_max_value)-1)
			|| _blue == (-(_max_value)-1)) {
			return false;
		}
		return true;
	}

	friend istream& operator>>(istream& stream, Pixel& pixel);
};

//write to a pixel
istream& operator>>(istream& stream, Pixel& pixel){
	//sets local variables in the function
		int r = -(pixel._max_value) - 1;
		int g = -(pixel._max_value) - 1;
		int b = -(pixel._max_value) - 1;

	// passes the data from the stream into variables
		stream >> r >> g >> b;

	//calls setPixel
		pixel.setPixel(r, g, b);
	return stream;
}

//writes a pixel out to a file
ostream& operator<<(ostream& stream, Pixel& pixel){
	stream << pixel.getRed() 
		<< " " << pixel.getGreen() 
		<< " " << pixel.getBlue();
	return stream;
}
#endif // !PIXEL_HPP
