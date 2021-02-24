#pragma once

#include "Stud.h"

#include <stdbool.h>

/* Certify the packet with a checksum. The member .checksum needs to
   be zero, otherwise the function will return false. */
bool certify(struct pkt* const package);

/* Verify if the checksum is valid. The member .checksum will be set to
   zero if a sucessfull verification is done. */
bool verify(struct pkt* const package);