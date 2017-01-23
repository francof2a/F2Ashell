/*
 * ShellStatus.h
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
#ifndef SHELLSTATUS_H_
#define SHELLSTATUS_H_

#include	"../headers/ShellDefines.h"

class ShellStatus {
public:
	ShellStatus();
	virtual ~ShellStatus();

	unsigned int	uiGetLogging();
	void			vSetLogging(unsigned int logging);

	unsigned int	uiGetLogAnswers();
	void			vSetLogAnswers(unsigned int loganswers);

private:
	unsigned int		Logging;		//Flag to indicate that the shell is logging the lines entered
	unsigned int		LogAnswers;		//Flag to indicate that the shell is logging the answers as well
};

#endif /* SHELLSTATUS_H_ */
