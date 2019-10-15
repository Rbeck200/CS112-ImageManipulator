#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "FileReader.h";
#include "PpmDoc.hpp";
#include "Pixel.hpp"
using namespace std;


int main(int argc, char* argv[])
{
	string temp_filename;
	string new_filename;
	int selection_num = 0;

	PpmDoc ppm;

	cout << "Enter source file: ";
	cin >> temp_filename;

	cout << "Enter destination file: ";
	cin >> new_filename;
	cout << endl;

	cout << "*** Image Effects ***" << endl
		<< "1. Remove Red" << endl
		<< "2. Remove Green" << endl
		<< "3. Remove Blue" << endl
		<< "4. Negate Red" << endl
		<< "5. Negate Green" << endl
		<< "6. Negate Blue" << endl
		<< "7. Grayscale" << endl;

	cout << endl;
	cout << "Selection: ";
	cin >> selection_num;
	cout << endl;

	ppm = PpmDoc{ temp_filename };
	ppm.setFilename(new_filename);

	ppm.ImageManip(selection_num);

	ofstream output{ new_filename };
	output << ppm;
	output.close();


	cout << "Done. Program complete.";
	return 0;
}
