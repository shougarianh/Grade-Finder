
/*
 **
 * project: hw8
 * name: 
 * user??
 * date: 
 * file: driver.c
 */


#include "hw8.h"



int main(int argc, char* argv[])
{
   
	Class * class = readClass(argv[1]);
	sortClass(class);
	freeClass(class);
   
	return 0;
}
