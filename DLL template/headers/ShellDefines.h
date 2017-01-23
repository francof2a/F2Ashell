/*
 * ShellDefines.h
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

#ifndef SHELLDEFINES_H_
#define SHELLDEFINES_H_

#define		shell_root_promt		">>"
#define		shell_NameMaxSize		32
#define		shell_SizeLine			256
#define		shell_SizeCmd			32
#define		shell_SizeArg			32
#define		shell_maxnbrArg			8
#define		shell_MaxSizeOneArg		shell_SizeArg * shell_maxnbrArg
#define		shell_version			"1.1.2"
#define		shell_OS_windows
#undef		shell_OS_linux
#define		shell_HelpFilePath		"Dat/help_MasterPort.inf"

typedef		unsigned int			shell_rok;
#define		shell_ok				1
#define		shell_nok				0

#define		shell_domain_nbrCommonStrings	4
#define		shell_domain_nbrCommonData		16

//ToDos
#define		shell_ToDo_exit			1
#define		shell_ToDo_Mount		2
#define		shell_ToDo_script		3

//Colors
#ifndef		shell_colors
#define		shell_colors
#define		BLUE			1
#define		GREEN			2
#define		CYAN			3
#define		RED				4
#define		MAGENTA			5
#define		BROWN			6
#define		LIGHTGRAY		7
#define		DARKGRAY		8
#define		LIGHTBLUE		9
#define		LIGHTGREEN		10
#define		LIGHTCYAN		11
#define		LIGHTRED		12
#define		LIGHTMAGENTA	13
#define		YELLOW			14
#define		WHITE			15

#define		shell_default_color	240
#define		shell_script_color	241
#define		shell_error_color	244
#define		shell_warning_color	246
#define		shell_info_color	242
#define		shell_special_color	241
#define		shell_message_color	248
#define		shell_domain_mdig	248
#define		shell_domain_system	242
#endif

#define		shell_logfile_name	"logshell.txt"

//Ports
#define		shell_NbrPorts			16
#define		shell_PortType_lib		"lib"
#define		shell_PortType_root		"root"
#define		shell_MasterPort
#define		shell_RootPort			0
#define		shell_SystemPort		1

#endif /* SHELLDEFINES_H_ */

