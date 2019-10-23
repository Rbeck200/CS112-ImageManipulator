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

	//read filename into PpmDoc class
	ppm = PpmDoc{ temp_filename };

	// Rename the ppm to the name we want to save it as.
	ppm.setFilename(new_filename);

	//Make Output File
	ofstream output{ new_filename };

	//getter for selection_num
	cout << "*** Image Effects ***" << endl
		<< "1. Remove Red" << endl
		<< "2. Remove Green" << endl
		<< "3. Remove Blue" << endl
		<< "4. Negate Red" << endl
		<< "5. Negate Green" << endl
		<< "6. Negate Blue" << endl
		<< "7. Grayscale" << endl
		<< "8. Random Noise" << endl
		<< "9. High Contrast" << endl
		<< "Enter '0' to exit" << endl;
	

	//Manipulate the ppm based on the users selection
	//Keep making edits to the ppm until the user decides to stop
	do {
		cout << endl << "Selection: ";
		cin >> selection_num;
		ppm.ImageManip(selection_num);
		cout << endl;
		
	} while (selection_num != 0);

	//Shove the ppm information into our output file
	output << ppm;

	//Close the output file
	output.close();

	return 0;
}
