
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
We selected the Grep tool because we felt it would be an interesting project to tackle. It's essentially part of every linux
and unix system and is one of the most well known tools in that arena. That being said, it's a fascinating and complex problem
to solve. NFAs are an interesting algorithm because there is so much complexity in parallel operations all validating a string
simultaneously. The problem is this: how do we implement pattern matching to search files where we do not specifically need to
state exactly what we're looking for, but we can give enough information to a program that can interpret what we want and search
for it. Enter: regex. We can use shorthand operations to specify what kind of patterns we'd like to identify. Given that, we can
search for complex patterns that involve multiple routes. Take for example ((A*C|AB)D). Using this pattern we can search based
on special characters, namely ()|* to find what we want. * is a closure that searches for 0 or more of a character. () for order
of operations, and | for or branching. The given pattern searches for ACD AACD AAACD ABD, etc for infinite branches. The problem
now that we've developed complex expressions for our branches for pattern matching. To be efficient we only want to search the
characters in a file once. Thus we must check all possible states at once, for every character. Every character must check if it
is the start of a sequence, or if the previous character(s) passed, if this character is in the middle of a sequence. Once a
branch has failed, it must stop checking. If the character sequence matches any branch of the pattern to the end, we have identified
a match.

That being said, there are multiple implementation options. We explored two of which, a binary tree and a graph. While the binary
tree implementation was our first attempt, it became complex. To compile the pattern and determine all possible sequences, it must
be structured as roots and branching nodes, but the branch operators may come further down in the sequence. Using the previous
example, two branches ACD and ABD must be under a root node. So you must convert the pattern to postfix and build each branch
separately and attach them at the end. This is viable but complex for the developer to reason about. The graph implementation while
it must perform the same logic, is much easier to construct. For every character we can see what control characters we have and branch
accordingly or and open parens with nested ors will require branching. Closures also require branching. Thus, we can add each character
to a graph and add our edges between branching characters.

The traversal is a bit more complex. Once we compile our pattern into the NFA and build our graph, we must start analyzing the lines
to detect matches. While it may be intuitive once explained, we went through numerous iterations during the discovery process on just
how the detection was supposed to work while maintaining scalability. The first several iterations surrounded the concept of a stack
and pushing our history of each verification onto the stack and unwinding once we fail a branch in order to check the next one. The
unintuitive problem with this is that while you're checking each character, you could potentially be skipping the start of a branch
while in the middle of a failed branch. Thus, that algorithm would never work. Another iteration involved discovering all possible
branches and tracing through each one and recording them at the start, so they could be checked in parallel. This also was deemed
unreasonable as it is difficult to traverse the graph and record all possible states when given a complex pattern. The final solution
involved a fast forwarding function. Any time we have a valid match we fast forward that branch through to the next viable character
to match. Since during a previous implementation we found that if we did not, then you would compare control characters and valid
character simultaneously, which would skip valid detections. In order to do this, we maintain a list of all current branches being
checked and for every character, add a new check. When a character is matched, or a control character is detected, we consider it
valid and fast forward to the next viable characters for the next character in the line. All appropriate branches are taken along
the way and pushed onto the stack. So if a control character branches, we will skip it, add both branches, and skip those control
characters until we find valid characters. This was most effectively done recursively. Once we get through to the end of the line
all invalid branches will die off and new searches will be started on each character. The dying off process just involves two lists,
the current branches being checked and new branches. Old branches are dumped, and any new branches or advancing branches are added.
That way we don't inflate memory needlessly, and the algorithm stays quite fast.

That being said, this is how the core of grep works. We implemented several control characters, again: ()|*.
We left plenty of room for scalability for the application. Grepdriver and Grep are maintained in data structures that easily allow
for additional flags to be added with very little modification. NFA itself uses a switch statement to build the graph based on
control characters that may be easily added to. The valid branch checking is done in one simple boolean return function and the
recursive branch fast forwarding is done in a scalable way as well. Thus, we may add additional controls, and flag functionality
with little effort. As we move on, we will see how our grep class is to be used.


A note on usage:
Our grep.x matches grep -E
The extended characters must be enabled on the original grep for comparisions since we use the extended character set.

Our grep is also able to take multiple flags and multiple files/directories. We fully support file matching wildcards, so
a path of ./* may be given to check all files in the current directory or nfa.h for example would check only nfa.h for matches.
You can also pass in multiple file patterns, such as ./*.cpp ./*.h to match all cpp and header files in the current directory.

The pattern must also be wrapped in single quotes to be parsed by the command line properly as does the normal grep. So while
grep.x include ./*.cpp ./*.h would match all include statements in the cpp and header files, if you pass in '((A*C|AB)D)' it must
be in single quotes - this is a unix requirement.

Example grep statements:
grep.x --v
grep.x --help
grep.x include ./*.cpp ./*.h
grep.x -l -n include ./*.cpp ./*.h
grep.x -i -l -n INClude ./*.cpp ./*.h


Expected Operation
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

    -n, --line-number
        Each output line is preceded by its relative line number in the file,
        starting at line 1.
    -l, --files-with-matches
        Only the names of files containing selected lines are written to standard
        output.
    -i, --ignore-case
        Perform case insensitive matching.  By default, grep is case sensitive.
    --v, --version
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





