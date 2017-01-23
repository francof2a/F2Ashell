/*
 * ShellPort.h
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
#ifndef SHELLPORT_H_
#define SHELLPORT_H_

#include	"../headers/ShellParamToPorts.h"

//command processed status
#define		PortRunReturn_OK		0			//Command taken by this port
#define		PortRunReturn_nOK		1			//Command has not been taken by this port
#define		PortRunReturn_UC		2			//Unknown Command
#define		PortRunReturn_byPass	3			//Command by-pass, enables other ports to take the command too


#define		PortSizeDomain			32
#define		PortSizeName			32

#define		PortLibOK			0
#define		PortLibnOK			1

typedef int (*PortLibRun_ptr) (ShellParamToPorts* params);
typedef int (*PortLibIni_ptr) (ShellParamToPorts* params);

class ShellPort {
public:
	ShellPort();
	virtual ~ShellPort();

public:
	virtual void	vIni();
	virtual int		iSetLib(const char* libname, ShellParamToPorts* params);
	virtual void	vRun(ShellParamToPorts* params);
	char *			pcGetMyDomain();
	shell_rok		rokSetMyDomain(const char* domain);
	char *			pcGetMyName();
	shell_rok		rokSetMyName(const char* name);

public:
	unsigned int	RunReturn;					//Variable to return the command processed status
protected:
	char			MyDomain[PortSizeDomain];	//Specify the domain of this port
	PortLibRun_ptr	PortLibRun;					//Pointer to LibRun function (library)
	PortLibIni_ptr	PortLibIni;					//Pointer to LibIni function (library)
	HMODULE			Library;					//Pointer to Library
	char			LibName[32];				//Library's name
	char			PortName[PortSizeName];		//Port's name
};

#endif /* SHELLPORT_H_ */
