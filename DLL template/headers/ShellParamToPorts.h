/*
 * ShellParamToPorts.h
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
#ifndef SHELLPARAMTOPORTS_H_
#define SHELLPARAMTOPORTS_H_

#include "../headers/ShellParam.h"

//Shell Param interface to Users' Ports (libraries through ports as well)
class ShellParamToPorts: public ShellParam {
public:
//	ShellParamToPorts();
//	virtual ~ShellParamToPorts();

private:
	//Forbidden Functions
	void 			vSetTag(unsigned int tag);
	shell_rok 		rokSetDomainName(const char *name);
	shell_rok 		rokSetLine(const char *line);
	shell_rok 		rokSetCmd(const char *cmd);
	shell_rok 		rokSetArg(unsigned int arg_i, const char *arg);
	shell_rok 		rokSetOneArg(const char *arg);
	shell_rok		rokSetNbrArg(unsigned int narg);
	void			vSetCmdDet(unsigned int cmddet);
	void			vSetToDo(unsigned int todo);
	void			vProcessLine();
};

#endif /* SHELLPARAMTOPORTS_H_ */
