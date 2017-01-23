/*
 * ShellPort.cpp
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
#include "../headers/ShellPort.h"

ShellPort::ShellPort() {

	MyDomain[0] = '\0';
	PortName[0] = '\0';
	RunReturn = PortRunReturn_UC;
}
ShellPort::~ShellPort() { }
void	ShellPort::vIni(){

	//Inicialización genérica de un puerto
	//printf("\tEl puerto no presenta función de inicialización\n");
	strcpy(MyDomain, "generic");
	RunReturn = PortRunReturn_UC;
}
int		ShellPort::iSetLib(const char* libname, ShellParamToPorts* params){

	return PortLibOK;
}
void	ShellPort::vRun(ShellParamToPorts* params){

	//Ejecución genérica de un puerto
	printf("\tCommand Unknown!\n");
	RunReturn = PortRunReturn_UC;
}
char *	ShellPort::pcGetMyDomain(){
	static char MyDomain_buff[PortSizeDomain];

	strcpy(MyDomain_buff, MyDomain);
	return MyDomain_buff;
}
shell_rok	ShellPort::rokSetMyDomain(const char* domain){

	strcpy(MyDomain, domain);
	return shell_ok;
}
char *		ShellPort::pcGetMyName(){
	static char PortName_buff[PortSizeName];

	strcpy(PortName_buff, PortName);
	return PortName_buff;
}
shell_rok	ShellPort::rokSetMyName(const char* name){

	strcpy(PortName, name);
	return shell_ok;
}
