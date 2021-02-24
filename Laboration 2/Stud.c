#include "Stud.h"

#include "checksum.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* A Send */
void A_output(struct msg message)
{
	struct pkt packet = {.acknum = 0, .seqnum = 0, .checksum = 0};
	memcpy(packet.payload, message.data, sizeof(message.data));

	certify(&packet);

	tolayer3(1, packet);
}

/* B Send */
void B_output(struct msg message) /* need be completed only for extra credit */ { }

/* A Recive */ /* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) { }

/* called when A's timer goes off */
void A_timerinterrupt() { }

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init() { }

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* B Recive */ /* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
	if (verify(&packet))
	{
		tolayer5(1, packet.payload);
	}
	else
	{
		tolayer3(0, packet);
	}
}

/* called when B's timer goes off */
void B_timerinterrupt() { }

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init() { }
