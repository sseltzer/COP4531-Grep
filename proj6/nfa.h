#include <iostream>
#include <vector.h>
#include <graph.h>
#include <xstring.h>

typedef uint32_t Vertex;
typedef fsu::String String;
typedef fsu::Vector<char> Vector;
typedef fsu::Vector<size_t> Stack;
typedef fsu::ALDGraph<Vertex> Graph;

class NFA
{
	public:
		NFA 						(const char* pattern);
		void PatternToNFA			(const char* pattern);
		bool Matches				(const char* line);

	private:
		Vector v_;
		Graph g_;
};
NFA::NFA(const char* pattern) {
	std::cout << pattern << "\n";
	NFA::PatternToNFA(pattern);
}
void NFA::PatternToNFA(const char* pattern) {
  	for(const char* c = pattern; *c; ++c) v_.PushBack(*c);
  	g_.SetVrtxSize(v_.Size());

  	Stack stack;
  	size_t i, index, back;
  	for(i = 0; i < v_.Size(); ++i) {
  		index = i;
  		switch(v_[i]) {
  			case '(':
  				g_.AddEdge(i, i + 1);
  				stack.PushBack(i);
  				break;
  			case ')':
				back = stack.Back();
				stack.PopBack();
				if (v_[back] == '|') {
					index = stack.Back();
					stack.PopBack();
					g_.AddEdge(back, i);
					g_.AddEdge(index, back + 1);
				}
				g_.AddEdge(i, i + 1);
  				break;
  			case '|':
  				stack.PushBack(i);
  				break;
  			case '*':
  				g_.AddEdge(i, i + 1);
  				if (i >= v_.Size()) continue;
  				//g_.AddEdge(index - 1, i);
  				g_.AddEdge(i, index - 1);
  				break;
  			default:
  				g_.AddEdge(i, i + 1);
  				break;
  		}
  	}

    v_.Dump(std::cout);
    g_.Dump(std::cout);
	std::cout << "\n";
}

bool NFA::Matches(const char* line) {

	Vertex pos = 0;
	
	fsu::Vector<Graph::AdjIterator> stack;
	fsu::Vector<Vertex> history;
	//Stack stack;
	Stack alt;

	typename Graph::AdjIterator edge;
	
	for (; pos < v_.Size(); ++pos) {
		if (g_.EdgeSize() > 1) stack.PushBack(g_.Begin(pos));
	}

	const char* c = line;
	pos = 0;
	history.PushBack(pos);
	for(; *c; ++c) {
		if (pos == v_.Size()) return true;
		std::cout << "*c: " << *c << " v_[pos]: " << v_[pos] << " pos: " << pos;
		std::cout << "\nhistory: \n";
		history.Dump(std::cout);
		if (v_[pos] == '(' || v_[pos] == '|' || v_[pos] == ')' || v_[pos] == '*') {
			std::cout << " skipping\n";
			pos = *stack[pos];
			history.PushBack(pos);
			--c;
			std::cout << " end skipping\n";
			continue;
		}
		std::cout << "\n";
		if (*c == v_[pos]) {
			if (*stack[pos] == stack.Size()) return true;
			if (*stack[pos] < v_.Size() && v_[*stack[pos]] == '*') {
				std::cout << "found closure\n";
				while (*c == v_[pos]) ++c;
				--c;
				pos = *stack[pos];
				history.PushBack(pos);
				continue;
			}
			if (pos == stack.Size()) return true;
			pos = *stack[pos];
			history.PushBack(pos);

		} else {
			if (*stack[pos] < v_.Size() && v_[*stack[pos]] == '*') continue;
			pos = 0;
		}


		if (++c == '\0') {
			c = line;
			std::cout << "Popping History: \n";
			std::cout << pos << "\n";
			while(history.Size() > 0) {
				pos = history.Back();
				history.PopBack();
				if (v_[pos] == '*') {
					pos = history.Back();
					history.PopBack();
					continue;
				}
				++(stack[pos]);
				std::cout << pos << "\n";
				if (stack[pos] != g_.End(pos)) break;
			}
			if (history.Size() == 0) return false;
		}
		--c;
	}

	//stack.Dump(std::cout);
	//*/
	return false;
}