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

	int _red = 0;
	int _green = 0;
	int _blue = 0;



public:
	Pixel(int red, int green, int blue) {
		setPixel(red, green, blue);
	}

	Pixel(){
	}

	void setRed(const int& red) {
		_red = red;
	}

	int getRed() {
		return _red;
	}

	void setGreen(const int& green) {
		_green = green;
	}

	int getGreen() {
		return _green;
	}

	void setBlue(const int& blue) {
		_blue = blue;
	}

	int getBlue() {
		return _blue;
	}

	void setPixel(const int& red, const int& green, const int& blue) {
		setRed(red);
		setGreen(green);
		setBlue(blue);
	}

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

	void grayscale() {
		int temp = 0;
		temp = (_red + _green + _blue)/3;
		setPixel(temp, temp, temp);
	}

	bool checkPixel() {
		if (_red == -1 || _green == -1 || _blue == -1) {
			return false;
		}
		return true;
	}
};

istream& operator>>(istream& stream, Pixel& pixel){
	if (stream.good() == true) {
		int r = -1;
		int g = -1;
		int b = -1;
		stream >> r >> g >> b;
		pixel.setPixel(r, g, b);
	}else {
		throw exception{ "Bad Stream Format" };
	}
	return stream;
}

ostream& operator<<(ostream& stream, Pixel& pixel){
	stream << pixel.getRed() << " " << pixel.getGreen() << " " << pixel.getBlue();
	return stream;
}

#endif // !PIXEL_HPP
