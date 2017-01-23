/*
 * ShellDomain.h
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
#ifndef SHELLDOMAIN_H_
#define SHELLDOMAIN_H_

#include	<string.h>

#include	"../headers/ShellDefines.h"

class ShellDomain {
public:
	ShellDomain();
	virtual ~ShellDomain();

	unsigned int	uiGet_default();
	void			vSet_default(unsigned int _def);

	char 			*pcGetSubDomain();
	shell_rok 		rokSetSubDomain(const char *name);

	char 			*pcGetCommonStrings(unsigned int index);
	shell_rok 		rokSetCommonStrings(unsigned int index, const char *str);

	unsigned int	uiGetCommonData(unsigned int index);
	shell_rok		rokSetCommonData(unsigned int index, unsigned int data);

private:
	unsigned int		_default;														//domain's generic variable
	char				SubDomain[shell_NameMaxSize];									//Sub-Domain name
	char				CommonStrings[shell_domain_nbrCommonStrings][shell_SizeLine];	//General purpose strings
	unsigned int		CommonData[shell_domain_nbrCommonData];							//General purpose integers
};

#endif /* SHELLDOMAIN_H_ */
