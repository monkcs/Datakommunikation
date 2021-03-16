#include "prog3.h"
#include "string.h"

#include <stdbool.h>

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
	int costs[4][4];
};

struct distance_table dt3 = {{{7, 999, 999, 999}, {999, 999, 999, 999}, {999, 999, 2, 999}, {999, 999, 999, 0}}};

void printdt3(struct distance_table* dtptr)
{
	printf("             via     \n");
	printf("   D3 |    0     2 \n");
	printf("  ----|-----------\n");
	printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
	printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
	printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}

void rtupdate3(struct rtpkt* rcvdpkt)
{
	const int via = rcvdpkt->sourceid;

	for (size_t destination = 0; destination < 4; destination++)
	{
		if (dt3.costs[destination][via] > (dt3.costs[via][via] + rcvdpkt->mincost[destination]))
		{
			dt3.costs[destination][via] = dt3.costs[via][via] + rcvdpkt->mincost[destination];

			rtinit3();
		}
	}
}

void rtinit3()
{
	int shortest[4] = {999, 999, 999, 999};

	for (size_t node = 0; node < 4; node++)
	{
		for (size_t via = 0; via < 4; via++)
		{
			if (dt3.costs[node][via] < shortest[node])
			{
				shortest[node] = dt3.costs[node][via];
			}
		}
	}

	struct rtpkt packet0 = {3, 0};
	memcpy(packet0.mincost, shortest, sizeof(shortest));

	struct rtpkt packet2 = {3, 2};
	memcpy(packet2.mincost, shortest, sizeof(shortest));

	tolayer2(packet0);
	tolayer2(packet2);
}

void print3() { printdt3(&dt3); }
