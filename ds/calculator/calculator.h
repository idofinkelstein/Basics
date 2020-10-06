#ifndef ILRD_CALCULATOR_H
#define ILRD_CALCULATOR_H

#include "f_stack.h"
#include "c_stack.h"

/*---------------------------------------------------------------------------*/
/* Calculate:
*   - calculates the result of an equation represented as a string
* 
* Args:
*   - input - the equation to solve
*
* Return Value: 
*	- returns the result as a floating point number
*
* Comments: 
*	- assuming input is valid, includes only non negative real numbers
*	- operations can include: + - / * and parentheses ()
*	- following arithmetic precedence order
*/

float Calculator(const char *input);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_CALCULATOR_H */
