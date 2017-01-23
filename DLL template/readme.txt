The basic tree structure must be:

Proyect_Path
	|
	|---headers: 
	|		Here put 'Shell Headers File' (files in ShellIncludes/headers).
	|		You can use this folder to include your or third-party headers file.
	|
	|---lib:
	|		Here put libF2Ashell.a (file in ShellIncludes/lib).
	|		You can use this folder to include your or third-party libraries.
	...
	
Verify this:
Proyect_Path
	|
	|---headers/ 
	|		ShellDefines.h
	|		ShellDomain.h
	|		ShellLink.h
	|		ShellParam.h
	|		ShellParamToPorts.h
	|		ShellPort.h
	|		ShellStatus.h
	|		ShellUser.h
	|		...
	|
	|---lib/
	|		libF2Ashell.a
	|		
	...	

------------------------------------------------------------------------	
The only file you must to include directly is 'ShellLink.h'.
Examples:
	//If you are using a 'main.h' in headers folder
	#include	"ShellLink.h"
	
	//If you are including from 'main.h' or 'main.c' from Proyect_Path
	#include	"headers/ShellLink.h"
	
------------------------------------------------------------------------
The linker must be configurated to take Proyect_Path/lib as one more 
path to search libraries. 
In ECLIPSE go to: Properties/C/C++ Build/Settings/MinGW Linker C++/Libraries/
In 'Libraries (-l)' you must put: F2Ashell
In 'Libraries Search Path (-L)' you must put: Proyect_Path/lib


