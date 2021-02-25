#include "checksum.h"

#include "Stud.h"

#include <stdbool.h>

bool certify(struct pkt* const package)
{
	if (package->checksum == 0)
	{
		int checksum = 0;

		for (size_t i = 0; i < sizeof(package); i++)
		{
			checksum += ((const char* const)package)[i];
		}

		package->checksum = ~checksum;

		return true;
	}
	else
	{
		return false;
	}
}

bool verify(struct pkt* const package)
{
	const int calculated = package->checksum;
	package->checksum = 0;

	if (certify(package))
	{
		if (calculated == package->checksum)
		{
			package->checksum = 0;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}