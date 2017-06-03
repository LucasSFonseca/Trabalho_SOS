#ifndef _PROCSTAT_H_
#define _PROCSTAT_H_

#include <iostream>
#include <string.h>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fnmatch.h>
#include <algorithm>
#include <ncurses.h>
#include <list>
#include <stdlib.h>

std::string fltMin;
std::string fltMaj; 
std::string vmSize; 
std::string vmSwap;

struct proc_data {
	const char* pid;
	std::string flt_min;
	std::string flt_maj;
	std::string vm_size;
	std::string vm_swap;
};

std::list<proc_data> processes;

int filter(const struct dirent *dir);
const char* processdir(const struct dirent *dir);
void procCounter();
void getProcStat(const char *pid);
void getVmSwap(const char *pid);

#endif