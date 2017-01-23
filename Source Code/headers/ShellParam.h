/*
 * ShellConfig.h
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
#ifndef SHELLCONFIG_H_
#define SHELLCONFIG_H_

#include	<stdio.h>
//#include	<stdlib.h>
#include	<string.h>
#include	<windows.h>

#include	"../headers/ShellDefines.h"
#include	"../headers/ShellDomain.h"
#include	"../headers/ShellStatus.h"
#include	"../headers/ShellUser.h"

class ShellParam {
public:
	ShellParam();
	virtual ~ShellParam();

//Methods
public:
	unsigned int	uiGetTag();
	void 			vSetTag(unsigned int tag);

	char			*pcGetDomainName();
	shell_rok 		rokSetDomainName(const char *name);
	unsigned int	uiIsDomainEmpty();

	char 			*pcGetLine();
	shell_rok 		rokSetLine(const char *line);
	unsigned int	uiIsLineEmpty();

	char 			*pcGetCmd();
	shell_rok 		rokSetCmd(const char *cmd);
	unsigned int	uiIsCmdEmpty();

	char 			*pcGetArg(unsigned int arg_i);
	shell_rok 		rokSetArg(unsigned int arg_i, const char *arg);

	char 			*pcGetOneArg();
	shell_rok 		rokSetOneArg(const char *arg);

	unsigned int	uiGetNbrArg();
	shell_rok		rokSetNbrArg(unsigned int narg);

	unsigned int	uiGetCmdDet();
	void			vSetCmdDet(unsigned int cmddet);

	unsigned int	uiGetToDo();
	void			vSetToDo(unsigned int todo);

	void			vProcessLine();
	void			vMessage(const char* message, const char* TypeOf);


private:
	unsigned int	uiIsStringEmpty(const char *str);
	void			vTextColor(unsigned char color);
//Variables
private:
	unsigned int		Tag;									//General purpose variable
	char				DomainName[shell_NameMaxSize];			//Domain's name
	char				Line[shell_SizeLine];					//Full line entered by the user
	char				Cmd[shell_SizeCmd];						//Command, first word in Line
	char				Arg[shell_maxnbrArg][shell_SizeArg];	//Arguments, next words (space is the delimiter character)
	char				OneArg[shell_SizeLine];					//Arguments as a only string
	unsigned int		NbrArg;									//Amount of arguments entered
	unsigned int		CmdDet;									//Command detected flag
	unsigned int		ToDo;									//'To Do' Shell code. This specify a special task to do by the shell

public:
	ShellDomain			DomainStack;							//Pointer to Domain Class
	ShellStatus			Status;									//Pointer to Status Class
	ShellUser			User;									//Pointer to User Class
};

#endif /* SHELLCONFIG_H_ */
