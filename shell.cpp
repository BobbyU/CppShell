#include "shell.h"

class Command
{
    char * program;
    char * inputArray[MAX_ARG_SIZE];
    char inputStr[MAX_BUF_SIZE];
    int jobNumber;
    
    public:
    Command(void)
    {
        program = NULL;
        for( int i = 0; i < MAX_ARG_SIZE; i++ )
        {
            inputArray[i] = NULL;
        }
        jobNumber = 0;
    }

    void setInput( const char * inStr )
    {
        char * end;
        int i = 1;
        strcpy( inputStr, inStr );

        inputArray[0] = inputStr;
        end = inputStr;

        while( *end != '\0' )
        {
            if( *end == ' ' || *end == '\n' )
            {
                *end = '\0';
                inputArray[i++] = ++end;
            } 
            else
            {
                end++;
            }
        }
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
        fgets( strBuf, MAX_BUF_SIZE, stdin );
        moveInputToCommand( strBuf );
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
