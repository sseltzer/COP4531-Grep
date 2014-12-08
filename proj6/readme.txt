
Project 6 readme.txt
Team Members:
	Matthew Tannehill
	Sean Seltzer
	Damien King-Acevedo
	Gustavo Maturana

Project Link to Github repository: https://github.com/sseltzer/COP4531-Grep.git

Objectives of this Project
----------------------------

+ Define Regular Expression [RegEx]
+ Define Non-deterministic Finite Automaton [NFA]
+ State Kleene's Theorem
+ Describe how to build an NFA that models a given RegEx.
+ Describe how to use an NFA to find a RegEx pattern-match in a string.

Procedural Requirements
------------------------

1) The official development | testing | assessment environment is g++47 -std=c++11 -Wall 
   -Wextra on the linprog machines

2) Group Duties:

  + Matthew Tannehill (Team Leader):
	Responsible for the grep.h, integration
  + Sean Seltzer
	Responsible for the nfa.h, makefile, integration
  + Gustavo Maturan
  	Responsible for trouble shooting/debugging, testing, make changes to code as necessary, writing test reports
  + Damien King-Acevedo
  	Responsible for grepdriver.cpp, trouble shooting/debugging

  	All team members participated on regular schedule meetings

 3) Standard course C++ library was used for the purpose of this project

Software Development
-----------------------
At the beginning of our development cycle, we were think of using graph or binary three implementation. 
If we used a binary tree implementation, the binary tree would tended to get complicated because we had to build the regex in parts and assemble it as we went. Branching operation would have made the logic a little bit messy. 
If we used a graph implementation, the graph would convert the regex to a graph that can be followed for character matching. However we could be following a potentially infinite number of branches in one. This way regex would have become hard to track.

We decided to implement a grah instead of a binary tree. The concept of crwaling of the graph
for every possible path throught the regex over the whole was very appealing to group.




Expect Operations
-----------------------
Our version of grep is expected to work as per project requirements.
This implementation of grep includes Regular Expression notation like concatenation, or ( | ), closure ( * ), parentheses ( ( , ) ), and wildcard ( ( . ) ).
It also includes regular expression "shorthand" characters.
A general form of NFA is also implemented in this project.
No errors or warning should be expected during the compilation of this application.

The following is expected from the operation of this program.

+ grep.x -n [file]
	Each output line is preceded by its relative line number in the file, starting at line 1.The line number counter is reset for each file processed.  This option is ignored if -c, -L, -l, or -q is specified.

+ grep.x -l [file]
    Only the names of files containing selected lines are written to standard output.  grep will only search a file until a match has been found, making searches potentially less expensive.  Pathnames are listed once per file searched.  If the standard input is searched, the string ``(standard input)'' is written.

+ grep.x -i [file]
    Perform case insensitive matching.  By default, grep is case sensitive.

+ grep.x --v 
    Display version information and exit.

+ grep.x --help
	will display the list of commands supported by the application


Final Testing procedures
--------------------------

December 7, 2014

the following files were created for testing purposes
files 	Avengers.txt
		myTest.txt
		line.dat
		first.ex
		datatest.dat
Folder COP4531
		Avengers1.txt


+ Test 1: args.Size(): 0

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x
args.Size(): 0
Regexp selection and interpretation:
    grep [options] PATTERN [FILE...]
    -E, --extended-regexp     PATTERN is an extended regular expression
    -F, --fixed-strings       PATTERN is a set of newline-separated strings

- grep.x (Empty)
  sould display 
  Regexp selection and interpretation:
     grep [options] PATTERN [FILE...]

- Remove args.Size(): 0

+ Test 2: -help

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -help
args.Size(): 1
Regexp selection and interpretation:
    grep [options] PATTERN [FILE...]
    -E, --extended-regexp     PATTERN is an extended regular expression
    -F, --fixed-strings       PATTERN is a set of newline-separated strings

- Help options display need to be implemented
_ Remove args.Size() from display

+ Test 4: grep.x [options] PATTERN [FILE...]

Our group 6 grep.x application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep.x test alfa.txt
args.Size(): 2
this is a test for my
maturana@linprog2.cs.fsu.edu:~/projtest>

Original grep application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep test alfa.txt
this is a test for my
maturana@linprog2.cs.fsu.edu:~/projtest>

+ Test 5: One parameter after grep.x (args.Size(): 1)

- When just one parameter, our group 6 grep.x display the correct format and 
  -help commands
maturana@linprog2.cs.fsu.edu:~/projtest>grep.x test
args.Size(): 1
Regexp selection and interpretation:
    grep [options] PATTERN [FILE...]
    -E, --extended-regexp     PATTERN is an extended regular expression
    -F, --fixed-strings       PATTERN is a set of newline-separated strings

- Original grep goes into an finite loop and the application has to be suspended
maturana@linprog2.cs.fsu.edu:~/projtest>grep test

Suspended

+ Test 6: grep.x [options] PATTERN '*'

- Our grou 6 grep.x displays the following:
maturana@linprog2.cs.fsu.edu:~/projtest>grep.x test *
args.Size(): 9
this is a test for my
maturana@linprog3.cs.fsu.edu:~>cd projtest
maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Westra grepdriver.cpp
maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
maturana@linprog3.cs.fsu.edu:~/projtest>pico grepdriver.cpp
maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
maturana@linprog3.cs.fsu.edu:~/projtest>rm a.out
maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
maturana@linprog3.cs.fsu.edu:~/projtest>ls -l
maturana@linprog3.cs.fsu.edu:~/projtest>pico grepdriver.cpp
maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
maturana@linprog3.cs.fsu.edu:~/projtest>a.out
maturana@linprog3.cs.fsu.edu:~/projtest>
maturana@linprog3.cs.fsu.edu:~/projtest>ls -l
maturana@linprog3.cs.fsu.edu:~/projtest>a.out alfa.txt
maturana@linprog3.cs.fsu.edu:~/projtest>a.out -i test alfa.txt
pattern :test
line :this is a test for my
I did a thing! -i test
maturana@linprog3.cs.fsu.edu:~/projtest>
maturana@linprog3.cs.fsu.edu:~/projtest>a.out
maturana@linprog3.cs.fsu.edu:~/projtest>
maturana@linprog3.cs.fsu.edu:~/projtest>a.out --help
maturana@linprog3.cs.fsu.edu:~/projtest>
maturana@linprog3.cs.fsu.edu:~/projtest>a.out -help
maturana@linprog3.cs.fsu.edu:~/projtest>
maturana@linprog3.cs.fsu.edu:~/projtest>grep -help
maturana@linprog3.cs.fsu.edu:~/projtest>grep --help
        maturana@linprog3.cs.fsu.edu:~/projtest>a.out -i test alfa.txt
        maturana@linprog3.cs.fsu.edu:~/projtest>

maturana@linprog2.cs.fsu.edu:~/projtest>grep test *
alfa.txt:this is a test for my
report.txt:maturana@linprog3.cs.fsu.edu:~>cd projtest
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Westra grepdriver.cpp
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>pico grepdriver.cpp
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>rm a.out
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>ls -l
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>pico grepdriver.cpp
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>g++47 -std=c++11 -Wall -Wextra grepdriver.cpp
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>a.out
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>ls -l
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>a.out alfa.txt
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>a.out -i test alfa.txt
report.txt:pattern :test
report.txt:line :this is a test for my
report.txt:I did a thing! -i test
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>a.out
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>a.out --help
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>a.out -help
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>grep -help
report.txt:maturana@linprog3.cs.fsu.edu:~/projtest>grep --help
report.txt:     maturana@linprog3.cs.fsu.edu:~/projtest>a.out -i test alfa.txt
report.txt:     maturana@linprog3.cs.fsu.edu:~/projtest>
maturana@linprog2.cs.fsu.edu:~/projtest>

the output from both programs is similar

+ Test 7: No such file or directory

- Our group 6 grep.x application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep.x ave .dat
args.Size(): 2
grep: .dat: No such file or directory

- Original grep output
maturana@linprog2.cs.fsu.edu:~/projtest>grep ave .dat
grep: .dat: No such file or directory
maturana@linprog2.cs.fsu.edu:~/projtest>

Both applications have similar output

+ Test 8: -i wildcard

- Our group 6 grep.x application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -i AVE COP4531/*.txt
args.Size(): 4
Line 5 We may now have our first look at him. An Instagram photo that surfaced yesterday 
Line 6: Genesis,” Sarah Connor (Emilia Clarke) explains that somehow the Trousers of Time™ have 

- Original grep application
maturana@linprog2.cs.fsu.edu:~/projtest>grep -i AVE COP4531/*.txt
COP4531/Avengers.txt:Line 2 summer’s Avengers: Age of Ultron (below), there was one major character who even
COP4531/Avengers.txt:Line 5 We may now have our first look at him. An Instagram photo that surfaced yesterday 
COP4531/Avengers.txt:Line 7 rough art from Joss Whedon’s Avengers sequel, featuring a half-dozen our heroes,
COP4531/myTest.txt:Line 6: Genesis,” Sarah Connor (Emilia Clarke) explains that somehow the Trousers of Time™ have 
maturana@linprog2.cs.fsu.edu:~/projtest>

grep finds two additional lines that show "AVE" while grep.x shows only 2 line of text that show "AVE"

+ Test 9: -n line number

- Our group 6 grep.x application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -n ave COP4531/*.txt
args.Size(): 4
COP4531/Avengers.txt
    We may now have our first look at him. An Instagram photo that surfaced yesterday 
COP4531/myTest.txt
    Genesis,” Sarah Connor (Emilia Clarke) explains that somehow the Trousers of Time™ have 
    There is an ave here

- Original grep application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep -n ave COP4531/*.txt
COP4531/Avengers.txt:7:We may now have our first look at him. An Instagram photo that surfaced yesterday 
COP4531/myTest.txt:7:Genesis,” Sarah Connor (Emilia Clarke) explains that somehow the Trousers of Time™ have 
COP4531/myTest.txt:14:There is an ave here
maturana@linprog2.cs.fsu.edu:~/projtest>

grep.x does not display the line number while grep does.

+ Test 10: -l --files-with-matches

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -l ave COP4531
args.Size(): 3


Suspended

grep
maturana@linprog2.cs.fsu.edu:~/projtest>grep -l ave COP4531
maturana@linprog2.cs.fsu.edu:~/projtest>

grep.x goes into an infinite loop while grep recovers

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -l ave COP4531/*
args.Size(): 8

Suspended
maturana@linprog2.cs.fsu.edu:~/projtest>grep -l ave COP4531/*
COP4531/Avengers.txt
COP4531/myTest.txt
maturana@linprog2.cs.fsu.edu:~/projtest>

grep displays the files in which “ave” appears while grep.x goes into an infinite loop

-l display the wrong output

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -l ave COP4531/*.txt
args.Size(): 4
Line [7] : We may now have our first look at him. An Instagram photo that surfaced yesterday 
Line [7] : Genesis,” Sarah Connor (Emilia Clarke) explains that somehow the Trousers of Time™ have 
Line [14] : There is an ave here
maturana@linprog2.cs.fsu.edu:~/projtest>

+ Test 11: -v 
- Original grep application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep -v ave COP4531/*.txt
COP4531/Avengers.txt:
COP4531/Avengers.txt:For all the tidbits served up (and dug up by fans) in that first trailer for next 
COP4531/Avengers.txt:summer’s Avengers: Age of Ultron (below), there was one major character who even
COP4531/Avengers.txt:now remains a mystery: the Vision, the turncoat synthezoid played by Paul Bettany 
COP4531/Avengers.txt:(who previously lent his voice to Tony Stark’s digital valet J.A.R.V.I.S.)
COP4531/Avengers.txt:
COP4531/Avengers.txt:(from an account that has since been made private) shows what appears to be some 
COP4531/Avengers.txt:rough art from Joss Whedon’s Avengers sequel, featuring a half-dozen our heroes,
COP4531/Avengers.txt:and a character who quite possibly could be Vision smack dab in the middle of
COP4531/Avengers.txt:them. Empire Online reported that the Instagram user, Israel06, spotted the
COP4531/Avengers.txt:image in a banner at an international Disney event — which, if true, certainly
COP4531/Avengers.txt:lends it some legitimacy. 
COP4531/myTest.txt:Six years after we collectively decided to forget “Terminator: Salvation” ever Line 2: happened,
COP4531/myTest.txt:Arnold Schwarzenegger is back to resuscitate the franchise.
COP4531/myTest.txt:
COP4531/myTest.txt:
COP4531/myTest.txt:In the first full trailer for Paramount Pictures and Skydance Productions 
COP4531/myTest.txt:“Terminator: 
COP4531/myTest.txt:split, and we’re in a new leg/reality now. One where Connor was raised by Schwarzengger’s 
COP4531/myTest.txt:T-800 and became a stone cold badass years before her alternate personality in the Prime 
COP4531/myTest.txt:timeline.
COP4531/myTest.txt:Empty Line
COP4531/myTest.txt:Empty Line
COP4531/myTest.txt:There is nothing here AVE
COP4531/myTest.txt:Fruits: Apple, Orange, Banana
COP4531/myTest.txt:Date: December 12, 2014

- Our group 6 grep.x application output
maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -v ave COP4531/*.txt
args.Size(): 4
We may now have our first look at him. An Instagram photo that surfaced yesterday 
Genesis,” Sarah Connor (Emilia Clarke) explains that somehow the Trousers of Time™ have 
There is an ave here
maturana@linprog2.cs.fsu.edu:~/projtest>

the output from both application is different

+ Test 12: folder input without a wildcard *

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x test COP4531/
args.Size(): 2
 
Suspended

+ Test 13: --help

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x --help
Regexp selection and interpretation:
    grep [options] PATTERN [FILE...]

    -n, line-number
        Each output line is preceded by its relative line number in the file,
        starting at line 1.
    -l, files-with-matches
        Only the names of files containing selected lines are written to standard
        output.
    -i, ignore-case
        Perform case insensitive matching.  By default, grep is case sensitive.
    --v, -V version
        Display version information and exit.

maturana@linprog2.cs.fsu.edu:~/projtest>

+ Test 14: --v (Version)

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x --v
gresp.x (linprog) Version 1

Project: grep.x
December 7, 2014
Group 6:     Matthew Tannehill, Sean Seltzer, Gustavo Maturana, Damien King-Acevedo
FSU College of Computer Science

maturana@linprog2.cs.fsu.edu:~/projtest>

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x
Usage: grep.x [OPTION]... PATTERN [FILE]...
Try `grep --help' for more information.
maturana@linprog2.cs.fsu.edu:~/projtest>

+ Test 15: when pattern is not found

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x -i AVE COP4531/*.dat
args.Size(): 4
maturana@linprog2.cs.fsu.edu:~/projtest>

maturana@linprog2.cs.fsu.edu:~/projtest>grep -1 AvE COP4531/*.dat
maturana@linprog2.cs.fsu.edu:~/projtest>

+ Test 16: when the file is not found

maturana@linprog2.cs.fsu.edu:~/projtest>grep t col
grep: col: No such file or directory
maturana@linprog2.cs.fsu.edu:~/projtest>

maturana@linprog2.cs.fsu.edu:~/projtest>grep.x t col
args.Size(): 2
grep: col: No such file or directory
maturana@linprog2.cs.fsu.edu:~/projtest>





