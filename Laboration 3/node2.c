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

struct distance_table dt2 = {{{3, 999, 999, 999}, {999, 1, 999, 999}, {999, 999, 0, 999}, {999, 999, 999, 2}}};

void printdt2(struct distance_table* dtptr)
{
	printf("                via     \n");
	printf("   D2 |    0     1    3 \n");
	printf("  ----|-----------------\n");
	printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][1], dtptr->costs[0][3]);
	printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][1], dtptr->costs[1][3]);
	printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][1], dtptr->costs[3][3]);
}

void rtupdate2(struct rtpkt* rcvdpkt)
{
	const int via = rcvdpkt->sourceid;

	for (size_t destination = 0; destination < 4; destination++)
	{
		if (dt2.costs[destination][via] > (dt2.costs[via][via] + rcvdpkt->mincost[destination]))
		{
			dt2.costs[destination][via] = dt2.costs[via][via] + rcvdpkt->mincost[destination];

			rtinit2();
		}
	}
}

void rtinit2()
{
	int shortest[4] = {999, 999, 999, 999};

	for (size_t node = 0; node < 4; node++)
	{
		for (size_t via = 0; via < 4; via++)
		{
			if (dt2.costs[node][via] < shortest[node])
			{
				shortest[node] = dt2.costs[node][via];
			}
		}
	}

	struct rtpkt packet1 = {2, 0};
	memcpy(packet1.mincost, shortest, sizeof(shortest));

	struct rtpkt packet2 = {2, 1};
	memcpy(packet2.mincost, shortest, sizeof(shortest));

	struct rtpkt packet3 = {2, 3};
	memcpy(packet3.mincost, shortest, sizeof(shortest));

	tolayer2(packet1);
	tolayer2(packet2);
	tolayer2(packet3);
}

void print2() { printdt2(&dt2); }
