#pragma once
#ifndef FILE_READER_H
#define FILE_READER_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string> file_reader(ifstream& Ifile);
vector<string> file_reader(const string& file_name);


#endif