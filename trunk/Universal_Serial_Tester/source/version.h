#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.04";

	//Software Status
	static const char STATUS[] = "Release Candidate";
	static const char STATUS_SHORT[] = "rc";

	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 0;
	static const long REVISION = 0;

	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1;
	#define RC_FILEVERSION 0,1,0,0
	#define RC_FILEVERSION_STRING "0, 1, 0, 0\0"
	static const char FULLVERSION_STRING[] = "0.1.0.0";

	//SVN Version
	static const char SVN_REVISION[] = "0";
	static const char SVN_DATE[] = "04/13/2011";

	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;


#endif //VERSION_H
