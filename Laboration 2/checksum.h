#pragma once

/* The checksum method is the same as the algorithm used in TCP.*/

#include "Stud.h"

#include <stdbool.h>

/* Certify the packet with a checksum */
void certify(struct pkt* const package);

/* Verify if the checksum is valid */
bool verify(struct pkt* const package);