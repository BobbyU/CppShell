#include "shell.h"

class Command
{
    char * path;
    char * inputArray[MAX_ARG_SIZE];
    char inputStr[MAX_BUF_SIZE];
    int arguments;
    pid_t pid;
    int jobNumber;
    
    public:
    Command(void)
    {
        path = NULL;
        for( int i = 0; i < MAX_ARG_SIZE; i++ )
        {
            inputArray[i] = NULL;
        }
        jobNumber = 0;
        arguments = 0;
        pid = 0;
    }

    void setInput( char* inStr )
    {
        // Parses inStr and populates inputArray and path accordingly
        char * end;
        int i = 1;
        strcpy( inputStr, inStr );

        if( *inputStr == '\n' )
            // No input, just return
            return;

        inputArray[0] = inputStr;
        path = inputStr;
        arguments = 1;
        end = inputStr;

        while( *end != '\0' )
        {
            // while we haven't reached the end of the input
            if( *end == ' ' )
            {
                // if we are not reading a argument..
                // TODO: add other whitespace cases
                *end = '\0';
                if( *( end + 1 ) != '\n' || *( end + 1 ) != ' ' )
                {
                    // ..but we are about start
                    // add next argument to array and incrememnt arguments
                    inputArray[i++] = ++end;
                    arguments++;
                }
            }
            else if( *end == '\n' )
            {
                // if we are about to reach the end of the array,
                // just prepare to finish
                inputArray[i] = NULL;
                *end++ = '\0';
            }
            else
            {
                end++;
            }
        }
        
        return;
    }

    void execute(void)
    {
        // Execute the command in inputArray
        if( path == NULL )
        {
            // don't do anything if no path is given
            // since we are in the child process, kill yourself
            exit(0);
        }

        if( execvp( path, inputArray ) == -1 )
        {
            cerr << "Could not find the program: " << path << endl;
        }
    }

    pid_t getPid( void )
    {
        return pid;
    }

    void setPid( pid_t pd )
    {
        pid = pd;
    }

    const char *getPath( void )
    {
        return path;
    }
};

class Shell
{
    char strBuf[MAX_BUF_SIZE];
    Command *foregroundTask;
    int numberOfChildren;

    public:
    void getInput( void )
    {
        // Gets an input from the user, and creates a command based on it
        foregroundTask = new Command();
        cout << "$>";
        cin.getline( strBuf, MAX_BUF_SIZE );
        if( cin.eof() )
            exit(0);
        foregroundTask->setInput( strBuf );
    }

    Boolean isValidInput( void )
    {
        switch( *foregroundTask->getPath() )
        {
            case '\0':
            case '\n':
                return FALSE;
            case EOF:
                exit( 0 );
        }

        // If we aren't an invalid case, then must be valid
        return TRUE;
    }

    void forkAndExecute( )
    {
        pid_t pid = fork();

        // Executes the current cmd
        switch( (int) pid )
        {
            case -1:
                cerr << "Error in fork" << endl;
                break;
            case 0:
                foregroundTask->execute();
                break;
            default:
                foregroundTask->setPid( pid );
                numberOfChildren++;
        }
    }

    void cleanup( )
    {
        int status;

        wait( &status );
        /*
        // currently, no error handling, but it might be useful later
        if( WIFEXITED( status ) )
        {
            cout << "";
        }
        */
        delete foregroundTask;
    }

    pid_t getForegroundPid( void )
    {
        return foregroundTask->getPid( );
    }
};

Shell activeShell;

void sigIntHandler( int sig )
{
    // If we get SIGINT, send it to the child process (if there is one)
    // We are killed by EOF signal

    pid_t fPid = activeShell.getForegroundPid( );
    if( fPid != 0 )
    {
        kill( fPid, SIGINT );
        cout << endl; //not sure if this is good, will think about it
    }
}

int main( int argc, char * argv[] )
{
    int i = 0;
    setSignals();

    while( TRUE )
    {
        activeShell.getInput();
        if( activeShell.isValidInput() )
        {
            activeShell.forkAndExecute();
            activeShell.cleanup();
        }
        i++;
    }
}

void setSignals( void )
{
    struct sigaction sa;

    sa.sa_handler = sigIntHandler;
    sigaction( SIGINT, &sa, NULL );
}

/*
lets do signal redirection next
SIGINT should be sent to child
EOF character should terminate the terminal
*/
