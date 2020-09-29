#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "tree.h"
#include "exec.h"

using namespace std;

intlist *bckgrnd;

void inv()
{
    printf("%s", "\x1b[32m");
    char s[100];
    gethostname(s, 100);
    printf("%s@%s", getenv("USER"), s);
    printf("%s", "\x1B[37m");
    getcwd(s, 100);
    printf(":%s$ ", s);
}

int main()
{
	Tree *tr = NULL;	
    bckgrnd = NULL;
    
	while (true) {
		inv(); 			       
		clear_tree(tr);
		tr = NULL;			
		clear_zombie(&bckgrnd);
		
		list<string> list;	
		try {
			list = makeList();
			if (list.empty()) continue;
		} catch (int e) {
			if (e == 20) break; 
		}			
		changeList(list);       
		try {	
			tr = makeTree(list);
		} catch (int e) {
			if (e == 22) continue; 
		} 
			
		try {	
			exec_tree(tr);
		} catch (int e) {
			if (e == 21) {      
				clear_tree(tr);
				break;
			}
		}			
    }      
    return 0;
}

