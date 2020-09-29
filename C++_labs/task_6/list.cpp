#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

char c;                     
list<string> lexem_list;    

void gc() { 
	c = cin.get();
	if (cin.eof()) throw 20; 
}  

void print_list(list<string> & lst) {
	list<string> ::const_iterator p = lst.begin();
	printf("In print_list\n");
	while (p != lst.end()) {
		cout << *p << endl;
		p++;
	}
}

int is_special(char c)
{
	if (c == ';' || c == '<' || c == '|') {
		return 1;
	}
	if (c == '>') { 
		return 2;
	}
	return 0;
}

void parsing_error() {
	printf("%s\n", "myShell: parsing error: \" expected");
}

void parse_command() {
	enum state {
		START,       
		WORD,       
		IN_QUOTES,   
		SPECIAL2,    
		END          
	};

	state current_state; 
	current_state = START;
	string s;
	
	printf("=> ");

	do {
		gc();
		switch (current_state) {
			case START: {
				s = "";
				if (c == ' ' || c == '\t') {
					current_state = START;
				}
				else if (c == '\"') {
					current_state = IN_QUOTES;
				}
				else if (is_special(c) == 1) {
					current_state = START;
					s += c;
					lexem_list.push_back(s);
				}
				else if (is_special(c) == 2) {
					current_state = SPECIAL2;
					s += c;
				}
				else if (c == EOF || c == '\n') {
					current_state = END;
				}
				else {
					current_state = WORD;
					s += c;					
				}
				break;
			}
			case WORD: {
				if (c == ' ' || c == '\t') {
					current_state = START;
					lexem_list.push_back(s);
				}
				else if (c == EOF || c == '\n') {
					current_state = END;
					lexem_list.push_back(s);
				}
				else if (is_special(c) == 1) {
					current_state = START;
					lexem_list.push_back(s);
					s = c;
					lexem_list.push_back(s);
				}
				else if (is_special(c) == 2) {
					current_state = SPECIAL2;
					lexem_list.push_back(s);
					s = c;
				}
				else {
					current_state = WORD;
					s += c;
				}
				break;
			}
			case IN_QUOTES: {
				if (c == '\"') {
					current_state = START;
					lexem_list.push_back(s);
				}
				else if (c == EOF || c == '\n') {
					parsing_error();
					current_state = END;
				}
				else {
					current_state = IN_QUOTES;
					s += c;
				}
				break;
			}
			case SPECIAL2: { 
				if (is_special(c) == 1) {
					current_state = START;
					lexem_list.push_back(s);
					s = c;
					lexem_list.push_back(s);
				}
				else if (is_special(c) == 2) {
					current_state = START;
					s += c;
					lexem_list.push_back(s);
				}
				else if (c == ' ' || c == '\t') {
					current_state = START;
					lexem_list.push_back(s);
				}
				else if (c == EOF || c == '\n') {					
					current_state = END;
					lexem_list.push_back(s);
				}
				else {
					current_state = WORD;
					lexem_list.push_back(s);
					s = c;
				}
				break;
			}
			default: {
				printf("end");
				break;
			}
			
		}
	} while (current_state != END);
}

/* ----------------------------------------------------------------- */
/* FUNCTION  makeList:                                               */
/*  make list<string> from enter command                             */
/* ----------------------------------------------------------------- */
list<string> makeList() {
	lexem_list.clear();
	parse_command();
	return lexem_list;
}

/* ----------------------------------------------------------------- */
/* FUNCTION  changeList:                                             */
/*  replace enviroment variables like $HOME and $USER                */
/*  in list<string>                                                  */
/* ----------------------------------------------------------------- */
void changeList(list<string> &lst) {
	list<string> ::iterator p = lst.begin();
	while (p != lst.end()) {
		if ((*p).at(0) == '$') {
			string str = (*p);
			str = str.erase(0, 1);
			const char* w = getenv(str.c_str());
			if (w != NULL) {
				string s(w);
				cout << s << endl;
				p = lst.erase(p);
				lst.insert(p, s);
				p++;
			}
		}
		p++;
	}	
}
