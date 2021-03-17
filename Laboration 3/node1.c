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

struct distance_table dt1 = {{{1, 999, 999, 999}, {999, 0, 999, 999}, {999, 999, 1, 999}, {999, 999, 999, 999}}};

void printdt1(struct distance_table* dtptr)
{
	puts("");
	printf("             via   \n");
	printf("   D1 |    0     2 \n");
	printf("  ----|-----------\n");
	printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
	printf("dest 2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
	printf("     3|  %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][2]);
}

void rtupdate1(struct rtpkt* rcvdpkt)
{
	const int via = rcvdpkt->sourceid;

	for (size_t destination = 0; destination < 4; destination++)
	{
		if (dt1.costs[destination][via] > (dt1.costs[via][via] + rcvdpkt->mincost[destination]))
		{
			dt1.costs[destination][via] = dt1.costs[via][via] + rcvdpkt->mincost[destination];

			rtinit1();
		}
	}
}

void rtinit1()
{
	int shortest[4] = {999, 999, 999, 999};

	for (size_t node = 0; node < 4; node++)
	{
		for (size_t via = 0; via < 4; via++)
		{
			if (dt1.costs[node][via] < shortest[node])
			{
				shortest[node] = dt1.costs[node][via];
			}
		}
	}

	struct rtpkt packet0 = {1, 0};
	memcpy(packet0.mincost, shortest, sizeof(shortest));

	struct rtpkt packet2 = {1, 2};
	memcpy(packet2.mincost, shortest, sizeof(shortest));

	tolayer2(packet0);
	tolayer2(packet2);
}

void linkhandler1(int linkid, int newcost) { }

void print1() { printdt1(&dt1); }
