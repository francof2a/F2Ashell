/*
 * RootPort.cpp
 *
 *  Created on: 25/06/2010
 *      Author: F2A
 *      e-mail:	f2a.arte@gmail.com
 */
/*
This file is part of F2Ashell.

F2Ashell is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

F2Ashell is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with F2Ashell.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "RootPort.h"

RootPort::RootPort() {

	MyDomain[0] = '\0';
	RunReturn = PortRunReturn_UC;
}

RootPort::~RootPort() { }

void	RootPort::vIni(){

	strcpy(MyDomain, "root");
	RunReturn = PortRunReturn_UC;
	Credential = shell_PortFullAccess;
}
int		RootPort::iSetLib(const char* libname){

	return PortLibOK;
}
void	RootPort::vRun(ShellParamToPorts* params){

	RunReturn = PortRunReturn_OK;
	if (!strcmp(params->pcGetCmd(), "show")) 			vCmdShow(params);
	else if (!strcmp(params->pcGetCmd(), "help"))		vCmdHelp(params);
	else RunReturn = PortRunReturn_UC;
}

void	RootPort::vCmdShow(ShellParamToPorts* params){

	if(params->uiGetNbrArg() == 1) params->vSetToDo(shell_ToDo_Users_Show);
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("show [type of info to show]", "info");
	}
}
void	RootPort::vCmdHelp(ShellParamToPorts* params){
	FILE*	help;
	char	line[shell_SizeLine], cmd[shell_SizeLine];
	int		index;
	int		pnl = 0;

	if(params->uiGetNbrArg() <= 1){

		sprintf(cmd, "$%s", params->pcGetArg(0));
		if(params->uiGetNbrArg() == 0) sprintf(cmd, "$help");

		help = fopen(shell_HelpRootFilePath, "r");
		if(help != NULL){
			while(!feof(help)){
				//reading the line
				index = 0;
				do{	line[index] = fgetc(help); } while(!feof(help) && line[index++] != '\n');
				line[--index] = '\0';

				if(feof(help))break;

				if(line[0] == '$' && !strcmp(cmd, line)) pnl++;
				else if(line[0] == '$' && pnl == 1) pnl++;
				else if(pnl == 1) params->vMessage(line, "info");
			}
			fclose(help);
			if(pnl == 0 and !strcmp(params->pcGetDomainName(), "")) params->vMessage("Help entry unknown!", "error");
		}
		else params->vMessage("Help Data Base missing!", "error");
	}
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("help", "info");
		params->vMessage("help [command]", "info");
	}
}
