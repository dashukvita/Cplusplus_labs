#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

using namespace std;

Tree::Tree() {
	infile = "";
	outfile = "";
	background = false;
	append = false;
	pipe = NULL;
	next = NULL;  
  }  
  
  list<string> Tree::getArgv() {
    return argv;
  }
  
  string Tree::getFirstArgv() {
	return argv.front();
  }
  
  string Tree::getSecondArgv() {
	list<string> temp = getNextList(argv);
	if (temp.size() == 0) {
		return "";
	}
	return temp.front();
  }
  
  void Tree::setArgv(list<string> lst) {
	list<string> ::const_iterator p = lst.begin();
	while (p != lst.end()) {
		argv.push_back(*p);
		p++;
	}
  }
  
  string Tree::getInfile() {
	return infile;  
  }
  
  void Tree::setInfile(string & str) {
	infile = str;  
  }
  
  string Tree::getOutfile() {
	return outfile;  
  }
  
  void Tree::setOutfile(string & str) {
	outfile = str;  
  }
  
  bool Tree::isBackground() {
	return background;  
  }
  
  void Tree::setBackground() {
	background = true;  
  }
  
  bool Tree::isAppend() {
	return append;  
  }
  
  void Tree::setAppend() {
	append = true;  
  }
  
  Tree* Tree::getPipe() {
	return pipe;  
  }
  
  void Tree::setPipe(Tree * t) {
	pipe = t;  
  }
  
  Tree* Tree::getNext() {
	return next;  
  }
  
  void Tree::setNext(Tree * t) {
    next = t;
  }

void printListInLine(list<string> lst) {
	list<string> ::const_iterator p = lst.begin();
	while (p != lst.end()) {
		cout << *p << ' ';
		p++;
	}
}

void printTree(Tree *t) {
	if (t == NULL) return;
	printf("\nargv:       ");
	printListInLine(t -> getArgv());
	printf("\ninfile:     "); 
	cout << t -> getInfile();
	printf("\noutfile:    "); 
	cout << t -> getOutfile();
    printf("\nappend:     %d", t -> isAppend());
    printf("\nbackground: %d", t -> isBackground());
    if (t -> getPipe() != NULL) {
        printf("\n\nPipe: called from ");
        cout << t -> getFirstArgv();
        printTree(t -> getPipe());
    }
    if (t -> getNext() != NULL) { 
        printf("\n\nCommand: called from ");
        cout << t -> getFirstArgv();
        printTree(t -> getNext());
    }
    printf("\n");
}

// recursive parser

list<string> list_of_lexem; // will make recursive descent for this list
string cur_lex;

// return list without first elem
// if list was empty return empty list
list<string> getNextList(list<string> & lst) {
	if (lst.size() == 0) return lst;
	list<string> ::const_iterator p = lst.begin();
	p++;
	list<string> newList;
	while (p != lst.end()) {
		newList.push_back(*p);
		p++;
	}
	return newList;
}

// return tree_structure from parsing list
Tree* makeTree(list<string> list) {
	list_of_lexem = list;cat
	Tree* p = com_sh();
	return p;
}

void err_file() {
	if (list_of_lexem.empty()) {
		error("filename expected", NULL);
	}
	string cur_lex = list_of_lexem.front();
	if (is_oper(cur_lex)) {
		error("unexpected operation", cur_lex);
	}
}

void in_file(Tree *t) {
	err_file();
	string cur_lex = list_of_lexem.front(); 
	t -> setInfile(cur_lex);
}

void out_file(Tree *t) {
	err_file();
	string cur_lex = list_of_lexem.front(); 
	t -> setOutfile(cur_lex);
}

void out_append(Tree *t) {
	err_file();
	string cur_lex = list_of_lexem.front(); 
	t -> setOutfile(cur_lex);
	t -> setAppend();
}

void error(char const *s1, char *s2)
{
    fprintf(stderr, "%s", "\x1b[31m");
    fprintf(stderr, "shell: syntax error: ");
    fprintf(stderr, "%s", "\x1b[0m");
    fprintf(stderr, "%s", s1);
    if (s2 != NULL) {
        fprintf(stderr, " '%s'", s2);
    }
    fprintf(stderr, "\n");
    throw 22;
}

void error(char const *s1, string s2)
{
    printf("%s", "\x1b[31m");
    printf("shell: syntax error: ");
    printf("%s", "\x1b[0m");
    printf("%s ", s1);
        cout << s2;
    printf("\n");
    throw 22;
}

bool is_oper(string word)
{
    return is_next(word) || is_inout(word) || (word == "|");
}

bool is_next(string word)
{
    return (word == ";") || (word == "&");
}

bool is_inout(string word)
{
    return (word == "<") || (word == ">")|| (word == ">>");
}

void background(Tree *t) {
	while (t != NULL) {
		t -> setBackground();
		t = t -> getPipe();
	}
}

// shell command realisation
// shell_command ::= <command_list>
Tree* com_sh() {
	Tree *t;
	t = com_list();
	if (!list_of_lexem.empty()) {
		cur_lex = list_of_lexem.front();
		error("unexpected operation", cur_lex);
	}
	return t;
}

// command list realization
// command_list ::= <conv> {; <conv>} [&, ;]
Tree* com_list() {
	Tree *t1, *t2, *t;
	t = t1 = conv();
	cur_lex = list_of_lexem.front();
	while (!list_of_lexem.empty() && is_next(cur_lex)) {
		if (cur_lex == "&") {
			list_of_lexem = getNextList(list_of_lexem);
			background(t1);
		} else { // cur_lex == ";"
			list_of_lexem = getNextList(list_of_lexem);
		}
		/*
		if (cur_lex == "&") { // should be only last
			list_of_lexem = getNextList(list_of_lexem);	
			if (list_of_lexem.empty()) {
				background(t1);
				break;
			} else {
				error("operation & shoul be last", NULL);
			}					
		}
		* */
		//if (cur_lex == ";") {
		//list_of_lexem = getNextList(list_of_lexem);
		if (list_of_lexem.empty()) { // chek for the last ;
			break;
		}
		//}			
		t2 = conv();
		t1 -> setNext(t2);
		t1 = t2; 
		cur_lex = list_of_lexem.front();
	}
	return t;
}

// conveir realization
// conv ::= <command> {| <command>}
Tree* conv() {
	Tree *t1, *t2, *t;
	t = t1 = command();
	cur_lex = list_of_lexem.front();
	while (!list_of_lexem.empty() && cur_lex == "|") {
		list_of_lexem = getNextList(list_of_lexem);
		t2 = command();
		t1 -> setPipe(t2);
		t1 = t2;
		cur_lex = list_of_lexem.front();
	}	
	return t;
}

// command realization:
// command ::= <file_name> {<arguments>} [< <file_name>] [[>, >>] <file_name>] 
Tree* command() {	
	if (list_of_lexem.empty()) {
		error("filename expected", NULL);
	}
	cur_lex = list_of_lexem.front();
	if (is_oper(cur_lex)) {
		error("unexpected operation", cur_lex);
	}
	Tree *t = new Tree();
	list<string> argv;	
	while (!list_of_lexem.empty() && !is_oper(cur_lex)) {	
		argv.push_back(cur_lex);
		list_of_lexem = getNextList(list_of_lexem);		
		cur_lex = list_of_lexem.front();
	}	
	t -> setArgv(argv);	
	if (!list_of_lexem.empty() && cur_lex == "<") {
		list_of_lexem = getNextList(list_of_lexem);
		in_file(t);	
		list_of_lexem = getNextList(list_of_lexem);
		cur_lex = list_of_lexem.front();
	}
	if (!list_of_lexem.empty() && cur_lex == ">") {
		list_of_lexem = getNextList(list_of_lexem);
		out_file(t);	
		list_of_lexem = getNextList(list_of_lexem);
		cur_lex = list_of_lexem.front();
	}
	else if (!list_of_lexem.empty() && cur_lex == ">>") {
		list_of_lexem = getNextList(list_of_lexem);
		out_append(t);	
		list_of_lexem = getNextList(list_of_lexem);
	}	
	return t;
}

void clear_tree(Tree *t) {
	if (t == NULL) return;
	clear_tree(t -> getNext());
	clear_tree(t -> getPipe());
	delete t;
}
































