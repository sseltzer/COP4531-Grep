#include <iostream>
#include <vector.h>
#include <graph.h>
#include <xstring.h>

typedef uint32_t Vertex;
typedef fsu::Vector<char> Vector;
typedef fsu::Vector<size_t> Stack;
typedef fsu::Vector<Vertex> State;
typedef fsu::ALDGraph<Vertex> Graph;

class NFA
{
	public:
		NFA 						(const char* pattern);
		void PatternToNFA			(const char* pattern);
		bool Matches				(const char* line);

	private:
		void AdvanceToNonControl(Vertex state, State &newStates);
		bool IsValidCharacter(const char* cur, char pattern);
		Vector v_;
		Graph g_;
};
NFA::NFA(const char* pattern) {
	NFA::PatternToNFA(pattern);
}
void NFA::PatternToNFA(const char* pattern) {
	v_.PushBack('(');
  	for(const char* c = pattern; *c; ++c) v_.PushBack(*c);
  	v_.PushBack(')');
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
  				g_.AddEdge(i, index - 1);
  				break;
  			default:
  				g_.AddEdge(i, i + 1);
  				break;
  		}
  	}
}

bool NFA::Matches(const char* line) {
	State states;
	State newStates;
	NFA::AdvanceToNonControl(0, states);
	for(const char* c = line; *c; ++c) {
		for (size_t s = 0; s < states.Size(); ++s) {
			if (states[s] == v_.Size()) return true;
			if (NFA::IsValidCharacter(c, v_[states[s]])) {
				NFA::AdvanceToNonControl(states[s], newStates);
				continue;
			}
		}
		states.Clear();
		for (size_t s = 0; s < newStates.Size(); ++s) states.PushBack(newStates[s]);
		newStates.Clear();
		NFA::AdvanceToNonControl(0, states);
		if (*(c + 1) == '\0') c--;
	}
	return false;
}

bool NFA::IsValidCharacter(const char* cur, char pattern) {
	if (*cur == pattern) return true;
	if (pattern == '.') return true;
	if (pattern == '(') return true;
	if (pattern == ')') return true;
	if (pattern == '|') return true;
	if (pattern == '*') return true;
	return false;
}

void NFA::AdvanceToNonControl(Vertex state, State &newStates) {
	if (state == v_.Size()) return;
	Graph::AdjIterator i = g_.Begin(state);
	for (; i != g_.End(state); ++i) {
		if (*i == v_.Size()) {
			newStates.PushBack(*i);
			return;
		}
		char thisChar = v_[*i];
		if (thisChar == '(' || thisChar == '|' || thisChar == ')' || thisChar == '*') NFA::AdvanceToNonControl(*i, newStates);
		else newStates.PushBack(*i);
	}
}