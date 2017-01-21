#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "guilib.h"
#include "struct.h"
#include "strlib.h"

#include "mapping.h"
#include "dumbMd.h"
#include "manualMd.h"
#include "randMd.h"
#include "astarMd.h"

int getMoveOff(Map* L,int P,t_move* move)
{
	switch(L->players[P]->mode)
	{
		case 0:
			move->type = DO_NOTHING;
			move->value = 0;
		break;
		case 1:
			addStr(L->infoP2[0],"  MANUAL","  (MANUAL)");
		break;
		case 2:
			gene_randmove(L,move,P);
		break;
		case 3:
			gene_randmove(L,move,P);
		break;
		case 4://A*
			astarMv(L,P,move);
		break;
		case 5:
			addStr(L->infoP2[0],"No  Other player offline","");
		break;
		case 6:
			addStr(L->infoP2[0]," Contest mode"," ");
		break;
		
	}
	return MOVE_OK;
}


int sendMoveOff(Map* L,int P, t_move* move)
{
	return 1;
}

