// Use the GNU Source feature test macro for the following reasons:
// * sighandler_t typdef
#define _GNU_SOURCE 1

#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
//#include <cstdlib>
#include <unistd.h>
//#include <errno>
#include <string>
#include <string.h> // need strcpy from this
#include <signal.h>

// It is my understanding that the following is generally improper
// However, I am doing it here for convenience
using namespace std;

#define MAX_BUF_SIZE 1024
#define MAX_ARG_SIZE 128

typedef enum { FALSE, TRUE } Boolean;

class Shell;
void setSignals();
void sigIntHandler( int sig );
