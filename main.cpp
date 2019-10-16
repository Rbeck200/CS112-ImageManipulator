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
	//name of file we are working on
	string temp_filename;

	//what we want to name the new file.
	string new_filename;

	//What selection the user selects
	int selection_num = 0;

	//Initialization of the PpmDoc class
	PpmDoc ppm;

	//getter for temp_filename
	cout << "Enter source file: ";
	cin >> temp_filename;

	//getter for new_filename
	cout << "Enter destination file: ";
	cin >> new_filename;
	cout << endl;

	//getter for selection_num
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

	//read filename into PpmDoc class
	ppm = PpmDoc{ temp_filename };

	// Rename the ppm to the name we want to save it as.
	ppm.setFilename(new_filename);

	//Manipulate the ppm based on the users selection
	ppm.ImageManip(selection_num);

	//output the ppm to a new ppm file
	ofstream output{ new_filename };
	output << ppm;
	output.close();

	//finish program
	cout << "Done. Program complete.";
	return 0;
}
