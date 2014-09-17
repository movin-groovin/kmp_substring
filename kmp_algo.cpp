
#include <iostream>
#include <string>
#include <cassert>

#include <gnu/libc-version.h>


namespace NmUtil {

void printLibcInfo (std::ostream & cout) {
	cout << "Version: " << gnu_get_libc_version () << '\n';
	cout << "Release: " << gnu_get_libc_release () << '\n';
	
	return;
}

}


int main (int argc, char *argv []) {
	;
	
	NmUtil::printLibcInfo (std::cout);
	
	return 0;
}













