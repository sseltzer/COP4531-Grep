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
		cout<<"Error: expected input 'grep [options] PATTERN [FILE...]'"<<endl;
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

bool addDirectories (char* directory){			// this doesn't work yet
	
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
}

bool getData(int k) {
	
	vector<string> file;
	string line;
	ifstream myfile (fileNames[k]);
	
	while (getline(myfile, line)){
		file.push_back(line);
	}
	
	data.push_back(file);
	
	if (k == fileNames.size() - 1) return true;
	if (k < fileNames.size() - 1) return getData(k + 1);
	
	return false;
}

bool setInput (int argc, char* argv[]){
	struct stat st;
	bool lastFlag = false;
	bool havePattern = false;
	
	int k = 1;
	if (argv[1][0] != '-') {		// this fixes the case of no flags
		k = 2;
		PATTERN = argv[1];
		lastFlag = true;
		havePattern = true;
	}
	
	for (size_t i = k; i < argc; i++){
		if (argv[i][0] == '-' && lastFlag == false){
			if (argv[i][1] != '-')
				flags.push_back(argv[i] + 1);
			else
				flags.push_back(argv[i] + 2);
				
			if (i == (argc - 1)) {
				cout<<"Error: expected input 'grep [options] PATTERN [FILE...]'"<<endl;
				return false;
				}
			if (argv[i + 1][0] != '-') lastFlag = true;
		}
		else if (lastFlag == true && argv[i][0] == '-'){
			cout<<"Error: expected input 'grep [options] PATTERN [FILE...]'"<<endl;
			return false;						//either a flag without - or a flag after a file
		}
		else if (lastFlag == true && havePattern == false){
			PATTERN = argv[i];
			havePattern = true;
			if (i == argc - 1) {
				cout << "reading from standard in is not implimented" << endl;
				return false;   // have flags and pattern need to get data from std in
			}
		}
		else if (lastFlag == true && havePattern == true){
			stat(argv[i], &st);
			if (st.st_mode & S_IFDIR){
				addDirectories(argv[i]);		// get files in directory
			}
			else if (st.st_mode & S_IFREG){
				fileNames.push_back(argv[i]);
			}
			else {
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
    std::cout << "grep.x [flags] [pattern] [inFile] [outFile]"
              << std::endl;
}