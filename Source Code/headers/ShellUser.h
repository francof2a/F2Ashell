/*
 * ShellUser.h
 *
 *  Created on: 18/07/2010
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
#ifndef SHELLUSER_H_
#define SHELLUSER_H_

#include	"../headers/ShellDefines.h"
#include	"stdio.h"
#include	"string.h"

#define		UserSizeName	32
#define		UserSizePass	32

class ShellUser {
public:
	ShellUser();
	virtual ~ShellUser();

	char *			pcGetName();
	shell_rok		rokSetName(const char* name);

	char *			pcGetPass();
	shell_rok		rokSetPass(const char* pass);

private:
	char	Name[UserSizeName];		//User's Name entered
	char	Pass[UserSizePass];		//User's Password entered
};

#endif /* SHELLUSER_H_ */
