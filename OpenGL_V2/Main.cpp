/**INCLUDES**/
// External Includes

//Internal Includes
#include "App.h"

/**GLOBALS**/

/**CONSTANTS**/

/**VARIABLES**/
App myApp;

/**FUNCTIONS**/
static void exitProgram(int exitCode) {
	//TODO: Clean Up used contexts etc.
	exit(exitCode);
}

int main(int argc, char *argv[])
{
	myApp = App();
	myApp.start();
	
	exitProgram(ExitCode);
	
	return MAIN_RETURN;
}