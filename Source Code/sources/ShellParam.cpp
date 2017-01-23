/*
 * ShellConfig.cpp
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
#include "../headers/ShellParam.h"

ShellParam::ShellParam() {
	unsigned int index;

	Tag = 0;
	DomainName[0] = '\0';
	Line[0] = '\0';
	Cmd[0] = '\0';
	for(index = 0; index < shell_maxnbrArg; index++) Arg[index][0] = '\0';
	OneArg[0] = '\0';
	NbrArg = 0;
	CmdDet = 0;
	ToDo = 0;
	User.rokSetName("");
}

ShellParam::~ShellParam() {
	// TODO Auto-generated destructor stub
}

unsigned int	ShellParam::uiGetTag(){ return Tag; }
void 			ShellParam::vSetTag(unsigned int tag){ Tag = tag; }
char *			ShellParam::pcGetDomainName(){
	static char	DomainName_buff[shell_NameMaxSize];

	strcpy(DomainName_buff, DomainName);
	return DomainName_buff;
	}
shell_rok 		ShellParam::rokSetDomainName(const char *name){

	if(strlen(name) >= shell_NameMaxSize){ return shell_nok; }
	else strcpy(DomainName, name);
	return shell_ok;
}
unsigned int	ShellParam::uiIsDomainEmpty(){ return uiIsStringEmpty(DomainName); }
char *			ShellParam::pcGetLine(){
	static char Line_buff[shell_SizeLine];

	strcpy(Line_buff, Line);
	return Line_buff;
	}
shell_rok 		ShellParam::rokSetLine(const char *line){

	if(strlen(line) >= shell_SizeLine){	return shell_nok; }
	else{
		strcpy(Line, line);
		strcat(Line, " ");		//Es necesario que el último caracter sea un espacio
	}
	return shell_ok;
}
unsigned int	ShellParam::uiIsLineEmpty(){ return uiIsStringEmpty(Line); }
char *			ShellParam::pcGetCmd(){
	static char Cmd_buff[shell_SizeCmd];

	strcpy(Cmd_buff, Cmd);
	return Cmd_buff;
	}
shell_rok 		ShellParam::rokSetCmd(const char *cmd){

	if(strlen(cmd) >= shell_SizeCmd){ return shell_nok;	}
	else strcpy(Cmd, cmd);
	return shell_ok;
}
unsigned int	ShellParam::uiIsCmdEmpty(){ return uiIsStringEmpty(Cmd); }
char *	 		ShellParam::pcGetArg(unsigned int arg_i){
	static char		Arg_buff[shell_maxnbrArg][shell_SizeArg];

	if(arg_i >= shell_maxnbrArg){ return NULL; }
	else strcpy(Arg_buff[arg_i], Arg[arg_i]);
	return Arg_buff[arg_i];
}
shell_rok 		ShellParam::rokSetArg(unsigned int arg_i, const char *arg){

	if(arg_i >= shell_maxnbrArg){ return shell_nok;	}
	else if(strlen(arg) > shell_SizeArg){ return shell_nok; }
	else strcpy(Arg[arg_i], arg);
	return shell_ok;
}
char * 			ShellParam::pcGetOneArg(){
	static char OneArg_buff[shell_SizeLine];

	strcpy(OneArg_buff, OneArg);
	return OneArg_buff;
}
shell_rok		ShellParam::rokSetOneArg(const char *arg){

	if(strlen(arg) >= shell_MaxSizeOneArg){	return shell_nok; }
	else strcpy(OneArg, arg);
	return shell_ok;
}
unsigned int	ShellParam::uiGetNbrArg(){ return NbrArg; }
shell_rok		ShellParam::rokSetNbrArg(unsigned int narg){

	if(narg > shell_maxnbrArg){	return shell_nok; }
	else NbrArg = narg;
	return shell_ok;
}
unsigned int	ShellParam::uiGetCmdDet(){ return CmdDet; }
void			ShellParam::vSetCmdDet(unsigned int cmddet){ CmdDet = cmddet; }
unsigned int	ShellParam::uiGetToDo(){ return ToDo; }
void			ShellParam::vSetToDo(unsigned int todo){ ToDo = todo; }

void			ShellParam::vProcessLine(){
	char			c[2];
	char			aux[shell_SizeLine];
	unsigned int	index;

	c[0] = 0;
	c[1] = 0;
	aux[0] = 0;
	rokSetNbrArg(0);
	vSetCmdDet(0);
	if(uiIsLineEmpty()) return;		//si no hay ingreso valido no hace nada
	OneArg[0] = '\0';

	for(index = 0; Line[index] != 0; index++){
		c[0] = Line[index];
		if(c[0] == ' ' || c[0] == 0){
			if(CmdDet == 0){
				strcpy(Cmd, aux);
				CmdDet = 1;
				aux[0] = 0;
			}
			else if (NbrArg < shell_maxnbrArg){
				if(aux[0] != 0) strcpy(Arg[(NbrArg)++], aux);

				strcat(aux, " ");
				strcat(OneArg, aux);

				aux[0] = 0;
			}
			else{
				strcat(aux, " ");
				strcat(OneArg, aux);
				aux[0] = 0;
			}
		}
		else{
			strcat(aux, c);
		}
	}
	return;
}
unsigned int	ShellParam::uiIsStringEmpty(const char *str){

	if(str[0] == ' ' && str[1] == '\0'){ return 1; }
	return 0;
}
void			ShellParam::vMessage(const char* message, const char* TypeOf){
	unsigned int	tab = 1;
	unsigned int	pj = 1;

	vTextColor(shell_message_color);	//default

	if(!strcmp(TypeOf, "error"))			vTextColor(shell_error_color);
	else if(!strcmp(TypeOf, "warning"))		vTextColor(shell_warning_color);
	else if(!strcmp(TypeOf, "info"))		vTextColor(shell_info_color);
	else if(!strcmp(TypeOf, "special"))		vTextColor(shell_special_color);
	else if(!strcmp(TypeOf, "message"))		{}
	else if(!strcmp(TypeOf, "untab"))		tab = 0;
	else if(!strcmp(TypeOf, "nojump"))		pj = 0;
	else if(!strcmp(TypeOf, "untab_nojump")){
		tab = 0;
		pj = 0;
	}
	else 									vTextColor(shell_message_color);

	for(;tab > 0; tab--) printf("\t");
	if(pj != 0) printf("%s\n", message);
	else printf("%s", message);

	vTextColor(shell_default_color);
	return;
}
void			ShellParam::vTextColor(unsigned char color){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hcon, color);
	return;
}

