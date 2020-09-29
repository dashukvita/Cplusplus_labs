#ifndef TREE_H
#define TREE_H

#include <list>
#include <string>

class Tree {
private:
  std::list<std::string> argv;
  std::string infile;
  std::string outfile;
  bool background;
  bool append;
  Tree *pipe;
  Tree *next;
public:
  Tree();  
  std::list<std::string> getArgv();  
  std::string getFirstArgv(); 
  std::string getSecondArgv();
  void setArgv(std::list<std::string> lst);  
  std::string getInfile();  
  void setInfile(std::string & str);  
  std::string getOutfile();  
  void setOutfile(std::string & str);  
  bool isBackground();  
  void setBackground();  
  bool isAppend();  
  void setAppend();  
  Tree* getPipe();  
  void setPipe(Tree *t);  
  Tree* getNext();  
  void setNext(Tree *t);
};

std::list<std::string> getNextList(std::list<std::string> & lst);
void printTree(Tree *t);
void clear_tree(Tree *t);
Tree* makeTree(std::list<std::string> list);
Tree* com_sh();
Tree* com_list();
Tree* conv();
Tree* command();
bool is_oper(std::string word);
bool is_next(std::string word);
bool is_inout(std::string word);
void err_file();
void in_file(Tree *t);
void error(char const *s1, char *s2);
void error(char const *s1, std::string s2);
void out_file(Tree *t);
void out_append(Tree *t);
void background(Tree *t);
void clear_tree(Tree *t);

#endif
