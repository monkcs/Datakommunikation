#include "checksum.h"

#include "Stud.h"

#include <stdbool.h>

void certify(struct pkt* const package)
{
	package->checksum = 0;

	int checksum = 0;
	for (size_t i = 0; i < sizeof(*package); i++)
	{
		checksum += ((char*)package)[i];
	}

	package->checksum = checksum;
}

bool verify(struct pkt* const package)
{
	const int calculated = package->checksum;

	certify(package);

	return calculated == package->checksum;
}