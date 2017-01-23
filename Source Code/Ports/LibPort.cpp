/*
 * LibPort.cpp
 *
 *  Created on: 15/07/2010
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
#include "LibPort.h"

LibPort::LibPort() {

	MyDomain[0] = '\0';
	RunReturn = PortRunReturn_UC;

	PortLibRun = NULL;
	Library = NULL;
	LibName[0] = '\0';
	Credential = shell_PortNoAccess;
}

LibPort::~LibPort() { }

void	LibPort::vIni(){

	strcpy(MyDomain, "lib");
	strcpy(LibName, "default.dll");
	RunReturn = PortRunReturn_UC;
}
int		LibPort::iSetLib(const char* libname, ShellParamToPorts* params){

	Library = LoadLibrary(libname);
	strcpy(LibName, libname);

	if(Library){
		PortLibIni = (PortLibIni_ptr) GetProcAddress(Library, "LibIni");

		if(PortLibIni) PortLibIni(params);
		else params->vMessage("Library Init Function Error!", "error");

		FreeLibrary(Library);
	}
	else return PortLibnOK;
	return PortLibOK;
}
void	LibPort::vRun(ShellParamToPorts* params){

	Library = LoadLibrary(LibName);

	if(Library){
		PortLibRun = (PortLibRun_ptr) GetProcAddress(Library, "LibRun");

		if(PortLibRun) RunReturn = PortLibRun(params);
		else params->vMessage("Function Access Error!", "error");

		FreeLibrary(Library);
	}
	else params->vMessage("Library Access Error!", "error");
}
