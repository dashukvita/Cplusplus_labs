#ifndef EXEC_H
#define EXEC_H

#include <list>
#include "tree.h"

typedef struct intList {
    int pid;
    struct intList *next;
} intlist;

extern intlist *bckgrnd;

void add_elem (intlist **f, int pid);
void print_intlist(intlist *f);
void clear_intlist(intlist *f);
int is_com(Tree *t);
int exec_cd(Tree *t);
int exec_clear();
int sh_com(Tree *t);
void chng_iofiles(int in, int out, Tree *t);
void exec_tree(Tree *t);
int exec_com_sh(Tree *t);
int exec_com_list(Tree *t, int p);
int exec_conv(Tree *t, int p);
int exec_command(Tree *t, int in, int out, int next_in, int p);
char** makeArgs(std::list<std::string> lst);
int exec_conv(Tree *t, int p);
int exec_command(Tree *t, int in, int out, int next_in, int p, intlist **pfrgrnd);
void clear_zombie(intlist **b);

#endif
