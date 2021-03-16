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

struct distance_table dt0 = {{{0, 999, 999, 999}, {999, 1, 999, 999}, {999, 999, 3, 999}, {999, 999, 999, 7}}};

void printdt0(struct distance_table* dtptr)
{
	printf("                via     \n");
	printf("   D0 |    1     2    3 \n");
	printf("  ----|-----------------\n");
	printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1], dtptr->costs[1][2], dtptr->costs[1][3]);
	printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1], dtptr->costs[2][2], dtptr->costs[2][3]);
	printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1], dtptr->costs[3][2], dtptr->costs[3][3]);
}

void rtupdate0(struct rtpkt* rcvdpkt)
{
	const int via = rcvdpkt->sourceid;

	for (size_t destination = 0; destination < 4; destination++)
	{
		if (dt0.costs[destination][via] > (dt0.costs[via][via] + rcvdpkt->mincost[destination]))
		{
			dt0.costs[destination][via] = dt0.costs[via][via] + rcvdpkt->mincost[destination];

			rtinit0();
		}
	}
}

void rtinit0()
{
	int shortest[4] = {999, 999, 999, 999};

	for (size_t destination = 0; destination < 4; destination++)
	{
		for (size_t via = 0; via < 4; via++)
		{
			if (dt0.costs[destination][via] < shortest[destination])
			{
				shortest[destination] = dt0.costs[destination][via];
			}
		}
	}

	struct rtpkt packet1 = {0, 1};
	memcpy(packet1.mincost, shortest, sizeof(shortest));

	struct rtpkt packet2 = {0, 2};
	memcpy(packet2.mincost, shortest, sizeof(shortest));

	struct rtpkt packet3 = {0, 3};
	memcpy(packet3.mincost, shortest, sizeof(shortest));

	tolayer2(packet1);
	tolayer2(packet2);
	tolayer2(packet3);
}

void linkhandler0(int linkid, int newcost) { }

void print0() { printdt0(&dt0); }