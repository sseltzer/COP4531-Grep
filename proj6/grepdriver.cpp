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

int main(int argc, char* argv[]) {
	InputVector args;
	for (int i = 1; i < argc; ++i) args.PushBack(argv[i]);

	if (!ValidCall(args)) {
		GrepHelp();
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
	std::cout << "args.Size(): " << args.Size() << "\n";
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
				<< "    -E, --extended-regexp     PATTERN is an extended regular expression\n"
				<< "    -F, --fixed-strings       PATTERN is a set of newline-separated strings\n";
}