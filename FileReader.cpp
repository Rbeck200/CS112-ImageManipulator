#include "FileReader.h"

//Reads inputed file into a vector

vector<string> file_reader(ifstream& Ifile) {

	vector<string> result{};

	if (Ifile.is_open() == true) {

		string file_line;

		while (Ifile.good() == true) {

			getline(Ifile, file_line);

			result.push_back(file_line);

		}

	}
	return result;
	}

vector<string> file_reader(const string& file_name) {

	ifstream input{ file_name };
	vector<string> result = file_reader(input);
	input.close();
	return result;

}


