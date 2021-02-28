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

/* A Send */
void A_output(struct msg message)
{
	if (!transit)
	{
		transit = true;

		buffer.seqnum++;
		buffer.acknum++;
		memcpy(buffer.payload, message.data, sizeof(message.data));
		certify(&buffer);

		A_send();
	}
}

/* A Recive */
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

/* called when A's timer goes off */
void A_timerinterrupt() { A_send(); }

void B_timerinterrupt() { }
void B_init() { }
void B_output(struct msg message) { }

/* B Recive */
void B_input(struct pkt packet)
{
	if (verify(&packet))
	{
		tolayer3(1, packet);

		if (packet.seqnum == B_sequence)
		{
			printf("Sequence: %i, payload: ", packet.seqnum);
			for (size_t i = 0; i < 20; i++)
			{
				printf("%c", packet.payload[i]);
			}
			printf("\n");

			tolayer5(1, packet.payload);
			B_sequence++;
		}
	}
}