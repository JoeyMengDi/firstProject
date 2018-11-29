/** 
**	A Template for developing new terminal shared application
**/

#include <string.h>
#include <stdio.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>
#include "dynamiclib.h"

int TestAdd(int v1 , int v2 , int v3)
{
	return (v1 + v2 + v3);    
}

int TestSub(int v1 , int v2 , int v3)
{
	return (v1 - v2 - v3);
}

int TestMultiple(int v1 , int v2)
{
	return (v1 * v2);
}

int TestDiv(int v1 , int v2)
{
	return (v1 / v2);
}
