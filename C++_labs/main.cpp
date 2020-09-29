#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "tree.h"
#include "exec.h"

// exceptions:
// 20 - CTRL+D
// 21 exit command
// 22 shell: syntax error


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
		inv(); 			        //  invitation to enter
		clear_tree(tr);
		tr = NULL;			
		clear_zombie(&bckgrnd);
		
		list<string> list;	
		try {
			list = makeList();
			if (list.empty()) continue;
		} catch (int e) {
			if (e == 20) break; // CTRL+D
		}		
		//print_list(list);	
		changeList(list);       // replace environment variables
		try {	
			tr = makeTree(list);
			//printTree(tr);
		} catch (int e) {
			if (e == 22) continue; // shell: syntax error
		} 
			
		try {	
			exec_tree(tr);
		} catch (int e) {
			if (e == 21) {      // exit command
				clear_tree(tr);
				break;
			}
		}			
    }     
    //cout << "done!" << endl;    
    return 0;
}

