#include <fstream>
#include <iostream>
#include "grep.h"
#include "vector.h"


#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

typedef std::string            String;

using namespace std;

bool setInput (int argc, char* argv[]);
bool getData (size_t k);
bool addDirectories (char* directory);
bool wildCard(char * input, char* file);


fsu::Vector<String> list_dir (const char *path);
bool DirOrFile_(char* path);


void dump();
void GrepHelp();
void CommandFormat();

const char* PATTERN;
fsu::Vector<String> flags;
fsu::Vector<String> fileNames;
fsu::Vector<fsu::Vector<String> > data;

int main(int argc, char* argv[])
{

	if (argc < 2) {		// no pattern
        CommandFormat();
        return 1;
	}
	
	if (!strcmp("-help", argv[1])){
		std::cout<< "Help arguments\n";
		GrepHelp();
		return 1;
	}
		
	if (argc == 2 && argv[1][0] != '-') {
		cout << "reading from standard in is not implimented" << endl;
		return 1;
	}
    //Dirrectories (argv[2]);
    //DirOrFile(argv[2]);
    //DirOrFile_(argv[2]);

    /*if (wildCard("*.txt", argv[2]) == true)  // for testing purposes of the wildcard
    {
        cout<< argv[2] << " matches";
        return 1;
    } */
    
	
    if (setInput(argc, argv) ==  false) return 1;	// set flags and fileNames
	
	if (getData(0) == false) return 1; 				// add lines from fileNames to data
    
	
	//just for testing can safely be removed
	
	// needed additions are calls to grep.h to search the files for PATTERN and display the results
	
	Grep grep;																	// create Grep object
	
    for (size_t i = 0; i < flags.Size(); i++) grep.setFlag(flags[i].c_str());	// set flags
	
	if (!grep.search(PATTERN)) return 1;										// set pattern
	
	if (!grep.processing(fileNames)) return 1;									// set file names
	
	for (size_t i = 0; i < grep.results().Size(); i++) cout<<grep.results()[i];	// print results
	dump();
    return 1;
    
}

void dump(){										// this is for testing
	for (size_t i = 0; i < flags.Size(); i ++)			
		cout<<"flag ["<<i<<"]:" << flags[i]<<endl;
		
	cout <<"pattern :" << PATTERN << endl;
		
	for (size_t i = 0; i < fileNames.Size(); i++)
		cout<<"filename ["<<i<<"]:" << fileNames[i]<<endl;
	
	for (size_t i = 0; i < data.Size(); i++)
		for (size_t j = 0; j < data[i].Size(); j++)
			cout<<"line ["<<j<<"]:"<<data[i][j]<<endl;
}

/*
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
*/

bool getData(size_t k) {					// works recursively upward from fileNames[k] and puts their data in data[k]
	
	fsu::Vector<String> file;				// temporary vector to hold the data from the current file
	string line;
	ifstream myfile (fileNames[k]);		
	
	while (getline(myfile, line)){
		file.PushBack(line);
	}
	
	data.PushBack(file);
	
	myfile.close();
	
	if (k == fileNames.Size() - 1) return true;				// stops the function at the last filename
	if (k < fileNames.Size() - 1) return getData(k + 1);	// calls the function for the next filename
	
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
	
	for (int i = k; i < argc; i++){
		if (argv[i][0] == '-' && lastFlag == false){			// if argv[i] is a flag and there hasn't been a non-flag then add it to flags
			if (argv[i][1] != '-')								// this is for a single dash flag
				flags.PushBack(argv[i] + 1);
			else
				flags.PushBack(argv[i] + 2);					// this is for a -- flag
				
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
                fsu::Vector<String> tmp(list_dir(argv[i]));
                for(fsu::Vector<String>::Iterator j = tmp.Begin(); j != tmp.End(); ++j)
                {
                    fileNames.PushBack(argv[i]+'/'+*j);
                    // this is just for testing purposes
                    cout<< (argv[i] + *j) << endl;
                }
			}
			else if (st.st_mode & S_IFREG){						// if the filename belongs to a file added it to fileNames
				fileNames.PushBack(argv[i]);
			}
			else {
                // if the filename is invalid give an error
				cout << "grep.x: "<< argv[i] << ": No such file or directory" << endl;
				return false;
			}
		}
	}
	return true;
}
// fucntion is not working properly.
bool wildCard(char * input, char* file)
{
    bool match = false;
        // If we reach at the end of both strings, we are done
    if (*input== '\0' && *file == '\0'){
            return !match;
    }
    
        // Make sure that the characters after '*' are present in second string.
    if (*input == '*' && *(input+1) != '\0' && *file == '\0'){
            return match;
    }
    
        // If the first string contains '?', or current characters of both
        // strings match
    if (*input == '?' || *input == *file){
            return wildCard(input+1, file+1);
    }
    

    if (*input == '*'){
        
        return wildCard(input+1, file) || wildCard(input, file+1);
    }
    
    return match;

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
// List all the files in the directory
fsu::Vector<String> list_dir (const char *path)
{
    size_t size = 1000;
    struct dirent *entry;
    fsu::Vector<String> files;
    DIR *dir;
    dir = opendir (path);
    
    while ((entry = readdir (dir)) != NULL) {
        //char *buffer = path + entry->d_name;
        if (entry->d_name != ".." && entry->d_name != "." && entry->d_name[0] == ".")

        files.PushBack(entry->d_name);

    }

    return files;
}
//
bool DirOrFile_(char *path)
{
    struct stat s;
    if( stat(path,&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            return 1;
        }
        else if( s.st_mode & S_IFREG )
        {
            return 0;
        }
    }
    return 0;
}