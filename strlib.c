#include <stdio.h>
#include <stdlib.h>


/*! \file mapping.c
    \brief Mapping related functions.
    \author Maeva Arlandis et Alexis Devillard
    \version 6.2
    \date 10 janvier 2017
*/

int addStr(char *target,char *add1,char *add2)
{
	int i=0;
	while(*add1)
	{
		*target=*add1;
		target++;
		add1++;
		i++;
	}
	while(*add2)
	{
		*target=*add2;
		target++;
		add2++;
		i++;
	}
	*target='\0';
	return i;
}

char *intTostr(int nb)
{
	int i=10,n=1;
	while(nb>i){i*=10;n++;}
	
	char* nbch=(char*)malloc(sizeof(n+1));
	nbch[n]='\0';
	while(n>0)
	{
		nbch[n-1]='0'+ nb%10;
		nb/=10;
		n--;
	}
	return nbch;
}	
	
int strToint(char *nbr)
{
	int n=0,neg=0;
	char c = '0';
	if(*nbr=='-')
	{neg=1;nbr++;}
	while(*nbr)
	{
		n*=10;
		n+=*nbr-c;
		nbr++;
	}
	
	return (neg==0)?n:-n;
}
