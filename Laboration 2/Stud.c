#include "Stud.h"

#include "checksum.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* The current package being transmitted by A */
struct pkt buffer;

/* The sequence counter for B */
size_t B_sequence = 1;

/* To signal if A is sending */
bool transit = false;

void A_init()
{
	buffer.seqnum = 0;
	buffer.acknum = 0;
}

void A_send()
{
	tolayer3(0, buffer);
	starttimer(0, 15.0);
}

void A_output(struct msg message)
{
	if (!transit)
	{
		transit = true;

		buffer.seqnum++;
		buffer.acknum++;
		memcpy(buffer.payload, message.data, sizeof(buffer.payload));

		certify(&buffer);

		A_send();
	}
}

void A_input(struct pkt packet)
{
	if (verify(&packet))
	{
		if (packet.acknum == buffer.seqnum)
		{
			transit = false;
			stoptimer(0);
		}
	}
}

void A_timerinterrupt() { A_send(); }

void B_print(const struct pkt* const packet)
{
	printf("Sequence: %i, payload: ", packet->seqnum);

	for (size_t i = 0; i < sizeof(packet->payload); i++)
	{
		printf("%c", packet->payload[i]);
	}
	printf("\n");
}

void B_input(struct pkt packet)
{
	if (verify(&packet))
	{
		tolayer3(1, packet);

		if (packet.seqnum == B_sequence)
		{
			B_print(&packet);
			tolayer5(1, packet.payload);

			B_sequence++;
		}
	}
}

void B_timerinterrupt() { }
void B_init() { }
void B_output(struct msg message) { }