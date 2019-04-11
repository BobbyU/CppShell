#include "shell.h"

class Command
{
    char * program;
    char * inputArray[MAX_ARG_SIZE];
    char inputStr[MAX_BUF_SIZE];
    int jobNumber;
    
    public:
    void Command(void)
    {
        program = NULL;
        inputArray = NULL;
        jobNumber = 0;
    }

    void setInput( char * inStr )
    {
        strcpy( inStr, inputStr );
    }

    void execute(void)
    {
        execv( program, inputArray );
    }
};

class Shell
{
    char strBuf[MAX_BUF_SIZE];
    Command currentCmd;

    public:
    void getInput( void )
    {
        printf( "$>" );
        fgets( strBuff, MAX_BUF_SIZE, stdin );
        moveInputToCommand( strBuff );
    }

    void moveInputToCommand( char * inString )
    {
        currentCmd.setInput( inString );
    }
};

int main( int argc, char * argv[] )
{
    char strBuf[MAX_BUF_SIZE];
    Shell activeShell;

    while( 1 )
    {
        activeShell.getInput();
    }
}

/*
command object?
helpful for background tasks

lets implement it, barebones, and build on its functionality later
*/
