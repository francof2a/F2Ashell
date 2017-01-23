/*
 * Shell.cpp
 *
 *  Created on: 24/06/2010
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
#include "../headers/Shell.h"

Shell::Shell() {

	NbrPorts = 0;
}

Shell::~Shell() { }

void	Shell::vStart() {
	char	Line[shell_SizeLine];

	vIni();		//inicializa el shell

	//Bucle del shell
	for(;;){
		vOutPromt();						//Muestra el Promt
		gets(Line);							//Tomar la línea de comando y parámetros
		Params.rokSetLine(Line);			//Carga la línea en el shell
		Params.vProcessLine();				//Procesa la línea

		if(Params.Status.uiGetLogging()== 1) vShellLog_AddLine(Params.pcGetLine());
		if(Params.uiGetCmdDet() == 1) vProcessCmd();

		if(Params.uiGetToDo() == shell_ToDo_exit) break;
		vShellToDoInterpeter();
	}
	//scape sequence
	vShellTextColor(shell_message_color);
	vShellScript("Dat/close.ssf");
}
void	Shell::vIni(){

	system("title F2A Shell");
	vShellTextColor(shell_default_color);
	vShellPortsIni();
	vShellClearScreen();
	vShellShowInfo();

	//open script
	vShellTextColor(shell_message_color);
	vShellScript("Dat/open.ssf");
	vShellTextColor(shell_default_color);

	return;
}
void	Shell::vShellPortsIni(){
	unsigned int	index;

	//Se inicializa el puntero
	for(index = 0; index < shell_NbrPorts; index++) Ports[index] = new ShellPort;

	//--------------------------------------------------//
	//Asignación de puertos
	rokNewPort(shell_PortType_root, "P_root", shell_PortType_root, NULL);
	rokNewPort("system", "P_sys", shell_PortType_lib, "Libs/ShellPort_system.dll");

	//Ohter Ports...

	//--------------------------------------------------//
	//Master Port Init
	MPort.vIni();

	return;
}
void	Shell::vOutPromt(){

	vShellTextColor(shell_default_color);
	printf("\n");
	if(Params.User.pcGetName()[0] != 0) printf("$%s", Params.User.pcGetName());
	printf(">%s", Params.pcGetDomainName());
	if(Params.DomainStack.pcGetSubDomain()[0] != 0) printf("::%s", Params.DomainStack.pcGetSubDomain());
	printf("> ");

	return;
}
void	Shell::vProcessCmd(){
	unsigned int	index;
	unsigned int	taken;

	vShellTextColor(shell_default_color);

	//Shell MasterPort Commands
	MPort.vRun(&Params);
	taken = MPort.RunReturn;

	//Commands on Added Ports
	if(taken == PortRunReturn_UC || taken == PortRunReturn_byPass){
		vShellTextColor(shell_message_color);
		for(index = 0; index < NbrPorts; index++){
			//printf("%s\n", Ports[index]->pcGetMyDomain());
			if(!strcmp(Ports[index]->pcGetMyDomain(), Params.pcGetDomainName())){
				Ports[index]->vRun((ShellParamToPorts*)&Params);
				taken = Ports[index]->RunReturn;
				//printf("%s, %d\n", Ports[index]->pcGetMyDomain(), taken);
				if(taken == PortRunReturn_OK) break;

			}
		}
	}

	if(taken == PortRunReturn_UC) vShellMessage("Unknown Command!", "error");
	vShellTextColor(shell_default_color);
}
void	Shell::vShellLog_AddLine(const char* line){
	FILE	*log;

	log = fopen(shell_logfile_name, "a");
	if(log != NULL){
		fprintf(log, "%s\n", line);
		fclose(log);
	}
	else vShellMessage("Log File Error!", "error");
}
void	Shell::vShellMessage(const char* message, const char* TypeOf){
	unsigned int	tab = 1;

	vShellTextColor(shell_message_color);	//default

	if(!strcmp(TypeOf, "error"))			vShellTextColor(shell_error_color);
	else if(!strcmp(TypeOf, "warning"))		vShellTextColor(shell_warning_color);
	else if(!strcmp(TypeOf, "info"))		vShellTextColor(shell_info_color);
	else if(!strcmp(TypeOf, "special"))		vShellTextColor(shell_special_color);
	else if(!strcmp(TypeOf, "message"))		{}
	else if(!strcmp(TypeOf, "untab"))		tab = 0;
	else 									vShellTextColor(shell_message_color);

	for(;tab > 0; tab--) printf("\t");
	printf("%s\n", message);
	vShellTextColor(shell_default_color);
	return;
}
void	Shell::vShellTextColor(unsigned char color){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hcon, color);
	return;
}
void	Shell::vShellClearScreen(){

#ifdef shell_OS_windows
	system("cls");
#endif
	return;
}
void	Shell::vShellShowInfo(){
	char	Line[shell_SizeLine];

	Line[0] = '\0';
	sprintf(Line, "F2A Shell - Version %s\nCopyright (C) 2010/07/21 - GPL Licensed", shell_version);
	vShellMessage(Line, "untab");
	sprintf(Line, "This program comes with ABSOLUTELY NO WARRANTY");
	vShellMessage(Line, "untab");
	sprintf(Line, "This program doesn't assure the good functionality of third-party libraries");
	vShellMessage(Line, "untab");
	sprintf(Line, "This is free software, and you are welcome to redistribute it under certain conditions");
	vShellMessage(Line, "untab");
	return;
}
void	Shell::vShellToDoInterpeter(){
	char	DomainName[shell_NameMaxSize];

	DomainName[0] = '\0';

	switch(Params.uiGetToDo()){
	case shell_ToDo_exit:	break;
	case shell_ToDo_Mount:
		strcpy(DomainName, Params.pcGetArg(1));
		if(rokShellMount(DomainName, Params.pcGetArg(0), shell_PortType_lib) == shell_ok){ }
		else vShellMessage("Library has not been found!", "error");
		break;
	case shell_ToDo_script:
		vShellScript(Params.pcGetArg(0));
		break;
	default:

		break;
	}
	Params.vSetToDo(0);
}
shell_rok	Shell::rokShellMount(const char* domain, const char* name, const char* type){
	HMODULE			Library;


	if(!strcmp(type, shell_PortType_lib)){
		Library = LoadLibrary(name);

		if(Library){
			FreeLibrary(Library);
			Ports[NbrPorts] = new LibPort();
			Ports[NbrPorts]->vIni();
			if(Ports[NbrPorts]->iSetLib(name, (ShellParamToPorts*)&Params) == PortLibnOK){ return shell_nok; }
			Ports[NbrPorts]->rokSetMyDomain(domain);
			NbrPorts++;

			vShellMessage("Library mounted!", "info");
		}
		else return shell_nok;
	}

	return shell_ok;
}
shell_rok	Shell::rokNewPort(const char* domain, const char* name, const char* type, const char* library){

	if(!strcmp(type, shell_PortType_lib)){
		if(rokShellMount(domain, library, shell_PortType_lib) == shell_ok){
			Ports[NbrPorts - 1]->rokSetMyName(name);
			vShellMessage("Library Port created!", "info");
		}
		else{
			vShellMessage("Library Port couldn't be created!", "error");
			return shell_nok;
		}
	}
	else if(!strcmp(type, shell_PortType_root)){
		Ports[NbrPorts] = new RootPort();
		Ports[NbrPorts]->vIni();
		Ports[NbrPorts]->rokSetMyDomain(domain);
		Ports[NbrPorts]->rokSetMyName(name);
		NbrPorts++;
		vShellMessage("Root Port created!", "info");
	}
	else{
		vShellMessage("Port Type unknown", "error");
		return shell_nok;
	}
	return shell_ok;
}
void		Shell::vShellScript(const char* filename){
	FILE*	script;
	char	line[shell_SizeLine];
	int		index;

	script = fopen(filename, "r");
	if(script != NULL){
		while(!feof(script)){
			//reading the line
			index = 0;
			do{	line[index] = fgetc(script); } while(!feof(script) && line[index++] != '\n');
			line[--index] = '\0';

			if(feof(script))break;

			//Show Promt & Line
			vOutPromt();

			vShellTextColor(shell_message_color);
			printf("%s: ", filename);
			vShellTextColor(shell_script_color);
			printf("%s\n", line);
			vShellTextColor(shell_message_color);

			//Process Line
			Params.rokSetLine(line);
			Params.vProcessLine();
			if(Params.Status.uiGetLogging()== 1) vShellLog_AddLine(Params.pcGetLine());
			if(Params.uiGetCmdDet() == 1) vProcessCmd();
			vShellToDoInterpeter();
		}
		fclose(script);
	}
	else vShellMessage("Script file has not been found!", "error");
}



