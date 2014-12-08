/*
    grepdriver.cpp
    12/06/14
    Matthew Tannehill
    Sean Seltzer
    Gustavo Maturana
    Damien King-Acevedo

*/
#include <iostream>
#include <vector.h>
#include <xstring.h>
#include <grep.h>


typedef fsu::Vector<char*> 		InputVector;
typedef fsu::Vector<char*> 		SwitchVector;
typedef std::string				String;
typedef fsu::Vector<String>		FileVector;


bool			ValidCall		(InputVector args);
SwitchVector	GetSwitches		(InputVector args);
char*			GetPattern		(InputVector args);
FileVector		GetFiles		(InputVector args);
Grep::Grep		CreateGrep		(SwitchVector switches, char* pattern, FileVector files);
void			GrepHelp		();
void            Version         ();
void            CommandFormat   ();

int main(int argc, char* argv[]) {
	InputVector args;
	for (int i = 1; i < argc; ++i) args.PushBack(argv[i]);

    if (argc == 2 && (strcmp("--v",argv[1]) == 0 || strcmp("-V",argv[1]) == 0)) {
        Version();
        return 1;
    }
    if (argc == 2 && strcmp("--help", argv[1])== 0){
        GrepHelp();
        return 1;
    }
    if (argc < 2)
    {
        CommandFormat();
        return 0;
    }
	if (!ValidCall(args)) {
        CommandFormat();
		return 0;
	}
	SwitchVector switches = GetSwitches(args);
	char* pattern   = GetPattern(args);
	FileVector files = GetFiles(args);
	Grep::Grep grep = CreateGrep(switches, pattern, files);

	fsu::Vector<String> results = grep.Results();
	for (size_t i = 0; i < results.Size(); ++i) {
		std::cout << results[i] << "\n";
	}
}

bool ValidCall (InputVector args) {
	if (args.Size() < 2) return false;
	size_t nonFlagParams = 0;
	for (size_t i = 0; i < args.Size(); ++i) if (*args[i] != '-') ++nonFlagParams;
	if (nonFlagParams < 2) return false;
	if (*args[args.Size() - 1] == '-') return false;
	return true;
}

SwitchVector GetSwitches(InputVector args) {
	SwitchVector switches;
	for (size_t i = 0; i < args.Size(); ++i) if (*args[i] == '-') switches.PushBack(args[i]);
	return switches;
}

char* GetPattern(InputVector args) {
	for (size_t i = 0; i < args.Size(); ++i) if (*args[i] != '-') return args[i];
	GrepHelp();
	return NULL;
}

FileVector GetFiles(InputVector args) {
	FileVector files;
	bool patternSkipped = false;
	for (size_t i = 0; i < args.Size(); ++i) {
		if (*args[i] == '-') continue;
		if (!patternSkipped) {
			patternSkipped = true;
			continue;
		}
		String file(args[i]);
		files.PushBack(file);
	}
	return files;
}

Grep::Grep CreateGrep(SwitchVector switches, char* pattern, FileVector files) {
	Grep::Grep grep;
	for (size_t i = 0; i < switches.Size(); ++i) grep.SetFlag(switches[i]);
	grep.Search(pattern);
	grep.Processing(files);
	return grep;
}

void GrepHelp() {
	std::cout   << "Regexp selection and interpretation:\n"
				<< "    grep [options] PATTERN [FILE...]\n"
                << std::endl
				<< "    -n,        (line-number)\n"
                << "        Each output line is preceded by its relative line number in the file,\n"
                << "        starting at line 1.\n"
				<< "    -l,        (files-with-matches)\n"
                << "        Only the names of files containing selected lines are written to standard\n"
                << "        output.\n"
                << "    -i,        (ignore-case)\n"
                << "        Perform case insensitive matching.  By default, grep is case sensitive.\n"
                << "    --v, -V    (version)\n"
                << "        Display version information and exit.\n"
                << std::endl;

}
void Version() {
    std::cout   <<"gresp.x (linprog) Version 1\n"
                <<std::endl
                <<"Project: grep.x\n"
                <<"December 7, 2014\n"
                <<"Group 6:     Matthew Tannehill, Sean Seltzer, Gustavo Maturana, Damien King-Acevedo\n"
                <<"FSU College of Computer Science\n"
                <<std::endl;
}
void CommandFormat() {
    std::cout   << "Usage: grep.x [OPTION]... PATTERN [FILE]...\n"
                << "Try `grep --help' for more information."
                << std::endl;
}