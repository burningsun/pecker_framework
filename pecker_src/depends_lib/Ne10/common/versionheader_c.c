#include "versionheader.h"

unsigned int Ne_Version(unsigned int* major, unsigned int* minor)
{
	if (major)
	{
		*major = VERSION_MAJOR;
	}
	if (minor)
	{
		*minor = VERSION_MINOR;
	}
	return VERSION_REVISION;
}

