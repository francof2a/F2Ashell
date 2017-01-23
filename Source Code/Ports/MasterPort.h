/*
 * MasterPort.h
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
#ifndef MASTERPORT_H_
#define MASTERPORT_H_

#include "../headers/ShellDefines.h"
#include "../headers/ShellParam.h"
#include "../headers/ShellPort.h"


class MasterPort: public ShellPort {
public:
	MasterPort();
	virtual ~MasterPort();

public:
	void	vIni();
	int		iSetLib(const char* libname, ShellParam*);
	void	vRun(ShellParam* params);

private:
	void	vCmdExit(ShellParam* params);
	void	vCmdDomain(ShellParam* params);
	void	vCmdSubDomain(ShellParam* params);
	void	vCmdSystem(ShellParam* params);
	void	vCmdMount(ShellParam* params);
	void	vCmdScript(ShellParam* params);
	void	vCmdHelp(ShellParam* params);
	void	vCmdLogin(ShellParam* params);
	void	vCmdLogout(ShellParam* params);
	void	vCmdUnmount(ShellParam* params);

	char*	pcReadPassword();
};

#endif /* MASTERPORT_H_ */
