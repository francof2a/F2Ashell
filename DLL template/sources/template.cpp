/*
 * mdig_dll_interface.cpp
 *
 *  Created on: 19/07/2010
 *      Author: F2A
 *      e-mail:	f2a.arte@gmail.com
 */
/*
This file is part of F2Ashell_dllTemplate.

F2Ashell_dllTemplate is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

F2Ashell_dllTemplate is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with F2Ashell_dllTemplate.  If not, see <http://www.gnu.org/licenses/>.
*/
#include	"../headers/template.h"

//you can change the name of the function: 'template_main'
BOOL WINAPI __declspec(dllexport) template_main (HINSTANCE hInst, DWORD Reason, LPVOID Reserved){
	if(Reason==DLL_PROCESS_ATTACH){
		//you can add code here
		return   TRUE;
	}
	if(Reason==DLL_PROCESS_DETACH){
		//you can add code here
		return   TRUE;
	}

	return   FALSE;
}


extern "C"{

/*
 * Every time there has been a command+params entry, F2Ashell calls this
 * function through this DLL.
 * You have to redirect, according to the command, the function to process
 * the parameters. All this information is in 'params'.
 * Refer to ShellParamToPorts.h and ShellParam.h to know about the class.
 */
unsigned int __declspec (dllexport) LibRun(ShellParamToPorts* params){
	unsigned int	RunReturn;

	RunReturn = PortRunReturn_OK;								//The Command has been processed

	if (!strcmp(params->pcGetCmd(), "test")) 					vShellPort_Test(params);
	else if (!strcmp(params->pcGetCmd(), "test+")) 				vShellPort_TestPlus(params);
//	else if (!strcmp(params->pcGetCmd(), "command name"))		YourFunction(params);
//	...
//	...

	else RunReturn = PortRunReturn_UC;							//Unknown Command

	return RunReturn;
}

/*
 * Every time there has been mount this DLL library into the F2Ashell, this
 * function is called. You can use it to do special routines like initializations.
 */
void		 __declspec (dllexport) LibIni(ShellParamToPorts* params){

}

} //end extern "C"

//--------------------------------------------------------------//
/*
 * User Interface Functions:
 * These functions have the purpose of process the params wich have been
 * entered by the shell.
 */

// Showing a text
void	vShellPort_Test(ShellParamToPorts* params){

	params->vMessage("This library is working!", "info");
}

// Showing an add
void	vShellPort_TestPlus(ShellParamToPorts* params){
	unsigned int	result;
	char			line[64];

	if(params->uiGetNbrArg() == 2){	//check the amount of arguments
		result = atoi(params->pcGetArg(0)) + atoi(params->pcGetArg(1));
		sprintf(line,"%d + %d = %d", atoi(params->pcGetArg(0)), atoi(params->pcGetArg(1)), result);
		params->vMessage(line, "message");
	}
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("test+ param1 param2", "info");
		params->vMessage("Result = param1 + param2", "info");
	}
}
