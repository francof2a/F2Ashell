/*
 * ShellDomain.cpp
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
#include "../headers/ShellDomain.h"

ShellDomain::ShellDomain() {
	int i;

	SubDomain[0] = '\0';
	_default = 1;
	for(i = 0; i < shell_domain_nbrCommonStrings; i++) rokSetCommonStrings(i, "");
	for(i = 0; i < shell_domain_nbrCommonData; i++) rokSetCommonData(i, 0);
}

ShellDomain::~ShellDomain() {
	// TODO Auto-generated destructor stub
}

unsigned int	ShellDomain::uiGet_default(){ return _default; }
void			ShellDomain::vSet_default(unsigned int _def){ _default = _def; }
char * 			ShellDomain::pcGetSubDomain(){
	static char	SubDomain_buff[shell_NameMaxSize];

	strcpy(SubDomain_buff, SubDomain);
	return SubDomain_buff;
	}
shell_rok 		ShellDomain::rokSetSubDomain(const char *name){

	if(strlen(name) >= shell_NameMaxSize){
		// TODO error en longitud de la cadena
		return shell_nok;
	}
	else strcpy(SubDomain, name);
	return shell_ok;
}
char *	 		ShellDomain::pcGetCommonStrings(unsigned int index){
	static char CommonStrings_buff[shell_domain_nbrCommonStrings][shell_SizeLine];

	if(index >= shell_domain_nbrCommonStrings){ return NULL; }
	else strcpy(CommonStrings_buff[index], CommonStrings[index]);
	return CommonStrings_buff[index];
}
shell_rok 		ShellDomain::rokSetCommonStrings(unsigned int index, const char *str){

	if(index >= shell_domain_nbrCommonStrings){	return shell_nok; }
	else if(strlen(str) > shell_SizeLine){		return shell_nok; }
	else strcpy(CommonStrings[index], str);
	return shell_ok;
}
unsigned int	ShellDomain::uiGetCommonData(unsigned int index){
	static unsigned int CommonData_buff;
	if(index >= shell_domain_nbrCommonData){
		// TODO error index
		return 0;
	}
	else CommonData_buff = CommonData[index];
	return CommonData_buff;
}
shell_rok		ShellDomain::rokSetCommonData(unsigned int index, unsigned int data){

	if(index >= shell_domain_nbrCommonData){
		// TODO error index
		return shell_nok;
	}
	else CommonData[index] = data;
	return shell_ok;
}
