#include "Echo.h"

//Class Echo

void Echo::process(char* arg) {
	for(int i = 0; i < sizeof(arg); i++)
	(*out) << arg[i];
}