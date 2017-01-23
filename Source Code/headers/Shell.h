/*
 * Shell.h
 *
 *  Created on: 24/06/2010
 *      Author: F2A
 *      e-mail:	f2a.arte@gmail.com
 *
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

#ifndef SHELL_H_
#define SHELL_H_

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<windows.h>

#include	"../headers/ShellDefines.h"
#include	"../headers/ShellParam.h"
#include	"../headers/ShellParamToPorts.h"
#include	"../headers/ShellPort.h"
#include	"../Ports/PortsInclude.h"
//#include	"../includes/ShellGadgets.h"

class Shell {
public:
	Shell();
	virtual ~Shell();

public:
	void	vStart();
private:
	void		vIni();
	void		vShellPortsIni();
	void		vOutPromt();
	void		vProcessCmd();
	void		vShellLog_AddLine(const char* line);
	void		vShellMessage(const char* message, const char* TypeOf);
	void		vShellTextColor(unsigned char color);
	void		vShellClearScreen();
	void		vShellShowInfo();
	void		vShellToDoInterpeter();
	shell_rok	rokShellMount(const char* domain, const char* name, const char* type);
	shell_rok	rokNewPort(const char* domain, const char* name, const char* type, const char* library);
	void		vShellScript(const char* filename);

private:
	ShellParam		Params;									//Shell's Parameters
	unsigned int	NbrPorts;								//Number of Loaded Ports
	ShellPort *		Ports[shell_NbrPorts];					//Ports' pointers
	MasterPort 		MPort;									//Master Port
};

#endif /* SHELL_H_ */
