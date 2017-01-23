/*
 * LibPort.h
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
#ifndef LIBPORT_H_
#define LIBPORT_H_

#include "../headers/ShellPort.h"

class LibPort: public ShellPort {
public:
	LibPort();
	virtual ~LibPort();

public:
	void	vIni();
	int		iSetLib(const char* libname, ShellParamToPorts* params);
	void	vRun(ShellParamToPorts* params);

};


#endif /* LIBSPORT_H_ */
