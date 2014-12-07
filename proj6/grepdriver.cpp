#include <fstream>
#include <iostream>
#include "grep.h"


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
bool wildCard(char * input, char* file);

bool wildCard( std::string input, std::string file);


fsu::Vector<std::string> list_dir (const char *path);
bool DirOrFile_(char* path);
std::string newPath(char *path);


void dump();
void GrepHelp();
void CommandFormat();

const char* PATTERN;
vector<char*> flags;
vector<char*> fileNames;
vector<vector<string> > data;

fsu::Vector<std::string> files;
int main(int argc, char* argv[])
{

{//grep [options] [regexp] [filename]
      
    Grep gp;
    gp.setFlag(argv[1]);
    files.PushBack(argv[3]);
    gp.search(argv[2]);
    gp.processing(files);
    gp.results();
/*
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

 //   cout << "here" << endl;
  //  cout << newPath(argv[3]) << endl;

*/
  /*  if (wildCard("*.txt", argv[2]) == true)  // for testing purposes of the wildcard
    {
        cout<< argv[2] << " matches";
        return 1;
    } */
	
/*
	if (setInput(argc, argv) ==  false) return 1;	// set flags and fileNames
	
	if (getData(0) == false) return 1; 				// add lines from fileNames to data

  /*  if (setInput(argc, argv) ==  false) return 1;	// set flags and fileNames
	
	//if (getData(fileNames.Size()-1) == false) return 1;  // This is just for testing purposes
    
    if (getData(0) == false) return 1; 				// add lines from fileNames to
    */

	
	dump();	//just for testing can safely be removed
	
	// needed additions are calls to grep.h to search the files for PATTERN and display the results
	
<<<<<<< Updated upstream
	
*/
    
=======
	Grep grep;																	// create Grep object
	
    for (size_t i = 0; i < flags.Size(); i++) grep.setFlag(flags[i].c_str());	// set flags
	
	if (!grep.search(PATTERN)) return 1;										// set pattern
	
//	if (!grep.processing(fileNames)) return 1;									// set file names
	

	if (!toFile)
		for (size_t i = 0; i < grep.results().Size(); i++) cout<<grep.results()[i];	// print results
	else {
		ofstream myfile;
		myfile.open(file);
		for (size_t i = 0; i < grep.results().Size(); i++) myfile<<grep.results()[i];
		myfile.close();
	}
	

	for (size_t i = 0; i < grep.results().Size(); i++) cout<<grep.results()[i];	// print results */
	dump();
>>>>>>> Stashed changes
    return 1;
}

void dump(){										// this is for testing
	for (int i = 0; i < flags.size(); i ++)			
		cout<<"flag ["<<i<<"]:" << flags[i]<<endl;
		
	cout <<"pattern :" << PATTERN << endl;
		
	for (int i = 0; i < fileNames.size(); i++)
		cout<<"filename ["<<i<<"]:" << fileNames[i]<<endl;
	
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < data[i].size(); j++)
			cout<<"line ["<<j<<"]:"<<data[i][j]<<endl;
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
                fsu::Vector<std::string> tmp(list_dir(argv[i]));
                for(fsu::Vector<std::string>::Iterator j = tmp.Begin(); j != tmp.End(); ++j)
                {
                        fileNames.PushBack(*j);
                }
            }
			else if (st.st_mode & S_IFREG){						// if the filename belongs to a file added it to fileNames
				fileNames.push_back(argv[i]);
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
<<<<<<< Updated upstream
=======

// List all the files in the directory
fsu::Vector<std::string> list_dir (const char *path)
{
    struct dirent *entry;
    fsu::Vector<std::string> files;
    DIR *dir;
    dir = opendir (path);
    
    
    while ((entry = readdir (dir)) != NULL) {
        switch (entry->d_type)
        {
            case DT_REG:
            {
                std::string location(path);
                location = location + "/" + entry->d_name;
                files.PushBack(location);
            }
                break;
            case DT_DIR:
            {
                continue;
            }
                break;
            default:
            {
                cout<< "Error 1: Empty Folder"<<endl;
            }
                break;
        }

    }
    return files;
}

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
std::string newPath(char *path)
{
    std::string sPath;
    size_t file_count = 0;
    for (size_t i = strlen(path)-1; i >= 0; --i)
    {
        if (path[i] != '/')
        {
            ++file_count;
        }
        else
        {
            break;
        }
    }
     char * nPath = new char[(strlen(path) - file_count)+1];
    for (size_t i = 0; i > (strlen(path)-file_count)+1; ++i){
        sPath += file_count;
    }
    
    return sPath;
}
>>>>>>> Stashed changes
