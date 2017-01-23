/*
 * MasterPort.cpp
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
#include "MasterPort.h"

MasterPort::MasterPort() { }

MasterPort::~MasterPort() { }

void	MasterPort::vIni(){
	strcpy(MyDomain, "SuperDomain");
	RunReturn = PortRunReturn_UC;
	Credential = shell_PortFullAccess;
}
int		MasterPort::iSetLib(const char* libname, ShellParam* params){

	return PortLibOK;
}
void	MasterPort::vRun(ShellParam* params){

	RunReturn = PortRunReturn_OK;
	if (!strcmp(params->pcGetCmd(), "exit")) 			vCmdExit(params);
	else if (!strcmp(params->pcGetCmd(), "domain")) 	vCmdDomain(params);
	else if (!strcmp(params->pcGetCmd(), "subdomain"))	vCmdSubDomain(params);
	else if (!strcmp(params->pcGetCmd(), "system"))		vCmdSystem(params);
	else if (!strcmp(params->pcGetCmd(), "mount"))		vCmdMount(params);
	else if (!strcmp(params->pcGetCmd(), "script"))		vCmdScript(params);
	else if (!strcmp(params->pcGetCmd(), "login"))		vCmdLogin(params);
	else if (!strcmp(params->pcGetCmd(), "logout"))		vCmdLogout(params);
	else if (!strcmp(params->pcGetCmd(), "unmount"))	vCmdUnmount(params);
	else if (!strcmp(params->pcGetCmd(), "help")){
		vCmdHelp(params);
		RunReturn = PortRunReturn_byPass;
	}
	else{
		//params->vMessage("Unknown Command!", "error");
		RunReturn = PortRunReturn_UC;
	}
}
void	MasterPort::vCmdExit(ShellParam* params){ params->vSetToDo(shell_ToDo_exit); }
void	MasterPort::vCmdDomain(ShellParam* params){
	if(params->uiGetNbrArg() == 1){
		if(!strcmp(params->pcGetArg(0), ".")){
			params->rokSetDomainName("");
			params->DomainStack.rokSetSubDomain("");
			params->DomainStack.vSet_default(1);
		}
		else{
			params->rokSetDomainName(params->pcGetArg(0));
			params->DomainStack.vSet_default(1);
		}
	}
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("domain .", "info");
		params->vMessage("domain [domain name]", "info");
	}
	return;
}
void	MasterPort::vCmdSubDomain(ShellParam* params){

	if(params->uiGetNbrArg() == 1){
		if(!strcmp(params->pcGetArg(0), ".")){
			params->DomainStack.rokSetSubDomain("");
			params->DomainStack.vSet_default(1);
		}
		else{
			params->DomainStack.rokSetSubDomain(params->pcGetArg(0));
			params->DomainStack.vSet_default(0);
		}
	}
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("subdomain .", "info");
		params->vMessage("subdomain [subdomain name]", "info");
	}
	return;
}
void	MasterPort::vCmdSystem(ShellParam* params){

	if(params->uiGetNbrArg() >= 1){

#ifdef shell_OS_windows
		system(params->pcGetOneArg());
#endif

	}
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("system [string to system console]", "info");
	}
	return;
}
void	MasterPort::vCmdMount(ShellParam* params){

	if(params->uiGetNbrArg() == 1) params->vSetToDo(shell_ToDo_Mount);
	else if(params->uiGetNbrArg() == 2) params->vSetToDo(shell_ToDo_Mount);
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("mount [library name]", "info");
		params->vMessage("\tdefault domain = lib", "info");
		params->vMessage("mount [library name] [domain]", "info");
	}
}
void	MasterPort::vCmdScript(ShellParam* params){

	if(params->uiGetNbrArg() == 1)params->vSetToDo(shell_ToDo_script);
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("script [Script File name]", "info");
	}
}
void	MasterPort::vCmdHelp(ShellParam* params){
	FILE*	help;
	char	line[shell_SizeLine], cmd[shell_SizeLine];
	int		index;
	int		pnl = 0;

	if(params->uiGetNbrArg() <= 1){

		sprintf(cmd, "$%s", params->pcGetArg(0));
		if(params->uiGetNbrArg() == 0) sprintf(cmd, "$help");

		help = fopen(shell_HelpFilePath, "r");
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
void	MasterPort::vCmdLogin(ShellParam* params){
	char	Line[shell_SizeLine];

	if(params->uiGetNbrArg() == 0){
		params->vMessage("User: ", "untab_nojump");
		gets(Line);
		params->User.rokSetName(Line);
		params->vMessage("Password: ", "untab_nojump");
		gets(Line);
		//pcReadPassword();
		params->User.rokSetPass(Line);
	}
	else if(params->uiGetNbrArg() == 1){
		params->User.rokSetName(params->pcGetArg(0));
		params->vMessage("Password: ", "untab_nojump");
		gets(Line);
		params->User.rokSetPass(Line);
	}
	else if(params->uiGetNbrArg() == 2){
			params->User.rokSetName(params->pcGetArg(0));
			params->User.rokSetPass(params->pcGetArg(1));
		}
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("login", "info");
		params->vMessage("login [user name]", "info");
		params->vMessage("login [user name] [password]", "info");
	}
	return;
}
void	MasterPort::vCmdLogout(ShellParam* params){

	if(params->uiGetNbrArg() == 0){
		params->User.rokSetName("");
		params->User.rokSetPass("");
	}
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("logout", "info");
	}
	return;
}

char*	MasterPort::pcReadPassword(){
	// TODO: Falta esto.
	static char		Line[shell_SizeLine];

	Line[0] = '\0';
	return Line;
}
void	MasterPort::vCmdUnmount(ShellParam* params){

	if(params->uiGetNbrArg() == 1) params->vSetToDo(shell_ToDo_Unmount);
	else{
		params->vMessage("Format Error:", "error");
		params->vMessage("unmount [library name]", "info");
	}
}
