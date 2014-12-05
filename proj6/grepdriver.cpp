#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h> 

using namespace std;

bool setInput (int argc, char* argv[]);
bool getData (int k);
bool addDirectories (char* directory);

void GrepHelp();
void CommandFormat();

const char* PATTERN;
vector<char*> flags;
vector<char*> fileNames;
vector<vector<string> > data;

int main(int argc, char* argv[])
{

	if (argc < 2) {		// no pattern
        CommandFormat();
        return 1;
	}
	
	if (!strcmp("-help", argv[1])){
		std::cout<< "help arguments";
		GrepHelp();
		return 1;
	}
		
	if (argc == 2 && argv[1][0] != '-') {
		cout << "reading from standard in is not implimented" << endl;
		return 1;
	}
	
	if (setInput(argc, argv) ==  false) return 1;	// set flags and fileNames
	
	if (getData(0) == false) return 1; 			// add lines from fileNames to data
	
	//currently, it stores all flags in flags, it stores the pattern in PATTERN, it stores the data from all files listed in data, it can recognize a directory and iterate through it, but it can't get the files from it.
	
	//this is just for testing
	
	for (int i = 0; i < flags.size(); i ++)
		cout<<"flag :" << flags[i]<<endl;
		
	cout <<"pattern :" << PATTERN << endl;
		
	for (int i = 0; i < fileNames.size(); i++)
		cout<<"filename :" << fileNames[i]<<endl;
	
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < data[i].size(); j++)
			cout<<"line :"<<data[i][j]<<endl;
	
    
    return 1;
}

bool addDirectories (char* directory){					// this doesn't work yet and is likely unneeded in keeping in the behaviour of grep on linprog
	
	char buf[PATH_MAX + 1]; 
	struct stat st;
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (directory)) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (!strcmp(ent->d_name, ".")) ;
			else if (!strcmp(ent->d_name, "..")) ;
			else {
				stat(directory, &st);
				if (st.st_mode & S_IFDIR){
					addDirectories(ent->d_name);		// get files in directory
				}
				else if (st.st_mode & S_IFREG){
					fileNames.push_back(ent->d_name);
				}
			}
		}
		closedir (dir);
	}
    return 1;
}

bool getData(int k) {					// works recursively upward from fileNames[k] and puts their data in data[k]
	
	vector<string> file;				// temporary vector to hold the data from the current file
	string line;
	ifstream myfile (fileNames[k]);		
	
	while (getline(myfile, line)){
		file.push_back(line);
	}
	
	data.push_back(file);
	
	if (k == fileNames.size() - 1) return true;				// stops the function at the last filename
	if (k < fileNames.size() - 1) return getData(k + 1);	// calls the function for the next filename
	
	return false;
}

bool setInput (int argc, char* argv[]){
	struct stat st;
	bool lastFlag = false;			// this is set to true if there are no options or once something that is not formatted as an option has been found
	bool havePattern = false;		// this is set to true when PATTERN stores the pattern
	
	int k = 1;
	if (argv[1][0] != '-') {		// if there are no flags store the pattern and set the above bools
		k = 2;
		PATTERN = argv[1];
		lastFlag = true;
		havePattern = true;
	}
	
	for (size_t i = k; i < argc; i++){
		if (argv[i][0] == '-' && lastFlag == false){			// if argv[i] is a flag and there hasn't been a non-flag then add it to flags
			if (argv[i][1] != '-')								// this is for a single dash flag
				flags.push_back(argv[i] + 1);
			else
				flags.push_back(argv[i] + 2);					// this is for a -- flag
				
			if (i == (argc - 1)) {								// this is if a flag is the last entry instead of a pattern
                CommandFormat();
				return false;
				}
			if (argv[i + 1][0] != '-') lastFlag = true;
		}
		else if (lastFlag == true && argv[i][0] == '-'){
            CommandFormat();
			return false;										// this is if a flag shows up after a non-flag
		}
		else if (lastFlag == true && havePattern == false){
			PATTERN = argv[i];
			havePattern = true;
			if (i == argc - 1) {
				cout << "reading from standard in is not implemented" << endl;
				return false;   								// have flags and pattern need to get data from std in
			}
		}
		else if (lastFlag == true && havePattern == true){
			stat(argv[i], &st);
			if (st.st_mode & S_IFDIR){							// if the filename is for a directory search through the directory and add all files in it to fileNames
				//addDirectories(argv[i]);						// this probably won't be implemented as it isn't implemented on grep when used on linprog
			}
			else if (st.st_mode & S_IFREG){						// if the filename belongs to a file added it to fileNames
				fileNames.push_back(argv[i]);
			}
			else {												// if the filename is invalid give an error
				cout << "invalid file" << endl;
				return false;
			}
		}
	}
	return true;
}

void GrepHelp()
{
    // Implementation according to flags
    std::cout << "Regexp selection and interpretation:"
              << "\n -E, --extended-regexp     PATTERN is an extended regular expression "
              << "\n -F, --fixed-strings       PATTERN is a set of newline-separated strings ";

    std::cout << std::endl;
}
void CommandFormat()
{
    std::cout << "Error: expected input grep.x [flags] [pattern] [inFile] [outFile]"
              << "\nType -help for help"
              << std::endl;
}