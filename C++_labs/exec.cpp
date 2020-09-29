#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "exec.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 5

using namespace std;

void add_elem (intlist **f, int pid) 
{
    intlist *cur;
    if ((*f) == NULL) {
        *f = (intlist *) malloc(sizeof(intlist));
        cur = *f;   
    }
    else {
        cur = *f;
        while (cur -> next != NULL) {
            cur = cur -> next;
        }
        cur -> next = (intlist *) malloc(sizeof(intlist));
        cur = cur -> next;
    }
    cur -> pid = pid;
    cur -> next = NULL;
}

void clear_zombie(intlist **b)
{
	int pid, status;
	intlist *cur, *tmp;
	cur = *b;
	while (cur != NULL) {
		pid = waitpid(cur -> pid, &status, WNOHANG);
		if (pid != 0) {
			*b = (*b) -> next;
			free(cur);
			cur = *b;
		}
		else {
			break;
		}
	}
	if (cur == NULL) {
		return;
	}
	tmp = cur;
	cur = cur -> next;
    while (cur != NULL) {
        pid = waitpid(cur -> pid, &status, WNOHANG);
        if (pid != 0) {
         	tmp -> next = cur -> next;
         	free(cur);
         	cur = tmp -> next;            
        }
        else {
        	cur = cur -> next;
        	tmp = tmp -> next;
        }
    }
}

void print_intlist(intlist *f) 
{
    while(f != NULL) {
        fprintf(stderr, "%d\n", f -> pid);
        f = f -> next;
    }
}

void clear_intlist(intlist *f) 
{
    intlist *cur;
    cur = f;
    while (cur != NULL) {
        cur = cur -> next;
        free(f);
        f = cur;
    }
}

char** makeArgs(list<string> lst) {
	char ** argv = NULL;
	int i = 0, size = 0;	
    argv = (char **) malloc(SIZE * sizeof(char *));
    size = SIZE;
	list<string> ::const_iterator p = lst.begin();
	while (p != lst.end()) {
		argv[i] = (char *)(*p).c_str();
		i++;
		p++;		
		if (i >= size) {
            argv = (char**) realloc(argv, (size + SIZE) * sizeof(char *));
            size += SIZE;
        }
	}
	argv[i] = NULL;
	return argv;
}

int is_com(Tree *t) {
	string com = t -> getArgv().front();
	if (com == "cd" || com == "clear" || com == "exit") {
		return 1;
	}
	return 0;
}


int exec_cd(Tree *t) 
{
	string adress = t -> getSecondArgv();
	if (adress == "") { // only command cd here
		chdir(getenv("HOME"));
        return 0;
	}
	// if at list one arg exist, try to go there
    if (chdir(adress.c_str()) == -1) { // convert string to const char* here
        fprintf(stderr, "cd: %s: no shuch file or directory\n", adress.c_str());
        return 1;
    }
    return 0;
}

int exec_clear()
{
    write(1, "\033[2J\033[H", sizeof("\033[2J\033[H"));
    return 0;
}

int sh_com(Tree *t)
{
    string com = t -> getArgv().front();
    if (com == "cd") {
        return exec_cd(t);
    }
    if (com == "clear") {
        return exec_clear();
    }
    if (com == "exit") {
		throw 21;
        return 0;
    }
    return 1;
}

void chng_iofiles(int in, int out, Tree *t)
{
    int fd;
    if (in != -1) {
        dup2(in, 0);
        close(in);
    }
    if (out != -1) {
        dup2(out, 1);
        close(out);
    }
    if (t -> getInfile() != "") {
        if ((fd = open(t -> getInfile().c_str(), O_RDONLY)) == -1) {
            perror("open");
            exit(1);
        }
        dup2(fd, 0);            
        close(fd);
    }
    if (t -> getOutfile() != "") {
        fd = open(t -> getOutfile().c_str(), O_WRONLY | O_CREAT | (t -> isAppend() ? O_APPEND : O_TRUNC), 0666);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        dup2(fd, 1);
        close(fd);
    }
}

void exec_tree(Tree *t) {
	exec_com_sh(t);
}

int exec_com_sh(Tree *t) {
	return exec_com_list(t, 0);
}

int exec_com_list(Tree *t, int p) {
	int ret;
	ret = exec_conv(t, p);
	while (t -> getNext() != NULL) {
        t = t -> getNext();
        ret = exec_conv(t, p);
    }
    return ret;
}

int exec_conv(Tree *t, int p) {
	int ret, in, out, next_in, status, i = 0;
	int fd[2];
    intlist *frgrnd = NULL;
	if (t -> getPipe() == NULL) {
		return exec_command(t, -1, -1, -1, p,  &frgrnd); 
	}
	next_in = -1;
    while (t -> getPipe() != NULL) {
        i++;
        pipe(fd);
        in = next_in;
        next_in = fd[0];
        out = fd[1];
        ret = exec_command(t, in, out, next_in, 1, &frgrnd);
        close(in);
        close(out);
        t = t -> getPipe();
    }
    ret = exec_command(t, next_in, -1, -1, 1, &frgrnd);
    close(next_in);
    while(frgrnd != NULL) {
        waitpid(frgrnd -> pid, &status, 0); 
        frgrnd = frgrnd -> next;
    }
    clear_intlist(frgrnd);
    return ret;
}

int exec_command(Tree *t, int in, int out, int next_in, int p, intlist **pfrgrnd) {
	int status, pid;
	if (is_com(t)) {
		return sh_com(t); // execute cd, clear, exit
	}

	if ((pid = fork()) == 0) {
		//cout << "in_son" << endl;
		chng_iofiles(in, out, t);
		//cout << "have changed" << endl;
		close(next_in);
		//cout << "have closed" << endl;
		char** argv = makeArgs(t -> getArgv());
		execvp(argv[0], argv);
		//cout << "have execvp" << endl;
		perror(t -> getFirstArgv().c_str());
		exit(1);
	}
	if (t -> isBackground()) {
	//printf("in backgrnd\n");
        waitpid(pid, &status, WNOHANG);
        add_elem(&bckgrnd, pid);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
	else if (p) {
	//printf("in add elem\n");
        add_elem(pfrgrnd, pid);
        return 0;
    }
	else {
		//cout << "in waitpid" << endl;
		waitpid(pid, &status, 0);
	}
	if (WIFEXITED(status)) {
		//cout << "in WIFEXITED" << endl;
		return WEXITSTATUS(status);
	}
	return 1;
}
