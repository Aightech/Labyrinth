#ifndef STRLIB_H
#define STRLIB_H
#include "struct.h"
#include "labyrinthAPI.h"

/*! \file strlib.h
    \brief Mapping related functions descriptions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/



int addStr(char * target,char * add1,char * add2);
char *intTostr(int nb);
int strToint(char *nbr);
#endif
