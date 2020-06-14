
/* 
BitArray is an array of 32 / 64 bits. 

Operations on bits: 
-	Set ON / OFF - idividually by index, or all at once
-	Flipped - change ON to OFF and vice versa, for each bit individually
-	Rotated left / right by a given number of bits
-	Get each bit's value (0 / 1)

Operations on array:
-	Mirroring the whole array
-	Count number of ON / OFF bits in array
-	Export to string
 	 
API supports both 32bit and 64bit systems. Array has number of bits as in the 
WORD in the machine: on 64bit systems, array will be 64 bits long. 
On 32bit systems, will be 32 bits long.

   Bit Array API
   Ver: 1.0  API team Approval
   Ver: 1.1  Update Comments 
   Ver: 1.2  API Approved 
*/

#ifndef ILRD_BIT_ARRAY_H
#define ILRD_BIT_ARRAY_H

#include <stddef.h>	/* size_t */

typedef size_t bit_array_t; 

/* BitArrSetAll
sets all bits in the arr

bit_arr - the bit array

return - the modified bit array
 */
bit_array_t BitArrSetAll(bit_array_t arr);

/* BitArrResetAll
unsets all bits in the arr

bit_arr - the bit array

return - the modified bit array
 */
bit_array_t BitArrResetAll(bit_array_t arr); 

/* BitArrSetOn
set a bit in the given index, 
if index is bigger than size of word it is undefined behavior

bit_arr - the bit array
index - the index in which we want to set the bit

return - the modified bit array
 */
bit_array_t BitArrSetOn(bit_array_t arr, size_t index);

/* BitArrSetOff
unset a bit in the given index, 
if index is bigger than size of word it is undefined behavior

bit_arr - the bit array
index - the index in which we want to unset the bit

return - the modified bit array
 */
bit_array_t BitArrSetOff(bit_array_t arr, size_t index);

/* BitArrSetBit
set a bit in the index to the given value,
if index is bigger than size of word it is undefined behavior

bit_arr - the bit array
index - the index in which we want to change the value of the bit
boolean_value - the value to which we want to change the bit

return - the modified bit array
 */
bit_array_t BitArrSetBit(bit_array_t arr, size_t index, int boolean_value);

/* BitArrFlip
in the given index- changes unset bit to set and vice versa,
if index is bigger than size of word it is undefined behavior

bit_arr - the bit array
index - the index in which we want to flip the value of the bit

return - the modified bit array
 */
bit_array_t BitArrFlip(bit_array_t arr, size_t index);

/* BitArrIsOn
returns 1 if the bit in the given index is set on, 0 if it is off
if index is bigger than size of word it is undefined behavior

bit_arr - the bit array
index - the index in which we check if bit is on

return - 1 if bit is on, 0 if bit is off
 */
int BitArrIsOn(bit_array_t arr, size_t index);

/* BitArrIsOff
returns 1 if the bit in the given index is set off, 0 if it is on
if index is bigger than size of word it is undefined behavior

bit_arr - the bit array
index - the index in which we check if bit is off

return - 1 if bit is off, 0 if bit is on
 */
int BitArrIsOff(bit_array_t arr, size_t index);

/* BitArrRotR
rotates all bits num times to the right

bit_arr - the bit array
num_to_shift - num of times we want to rotate the bit array to the right 

return - the modified bit array
 */
bit_array_t BitArrRotR(bit_array_t arr, size_t num_to_shift);

/* BitArrRotL
rotates all bits num times to the left

bit_arr - the bit array
num_to_shift - num of times we want to rotate the bit array to the left  

return - the modified bit array
 */
bit_array_t BitArrRotL(bit_array_t arr, size_t num_to_shift);

/* BitArrCountOn
counts all the set bits

bit_arr - the bit array

return - the number of set bits in the bit array
 */
size_t BitArrCountOn(bit_array_t arr);

/* BitArrCountOnLUT
counts all the set bits using LUT

bit_arr - the bit array

return - the number of set bits in the bit array
 */
size_t BitArrCountOnLUT(bit_array_t arr);


/* BitArrCountOff
counts all the unset bits

bit_arr - the bit array

return - the number of unset bits in the bit array
 */  
size_t BitArrCountOff(bit_array_t arr);

/* BitArrMirror
changes bit_arr to a mirror of itself

bit_arr - the bit array

return - the modified bit array
 */
bit_array_t BitArrMirror(bit_array_t arr);

/* BitArrMirrorLUT
changes bit_arr to a mirror of itself using LUT

bit_arr - the bit array

return - the modified bit array
 */
bit_array_t BitArrMirrorLUT(bit_array_t arr);

/* BitArrToString
returns bit_arr as a string representation

bit_arr - the bit array
dest - the destination to which we want to write the string

return - string representation of the bit array
 */
char *BitArrToString(bit_array_t arr, char *dest);

#endif /* ILRD_BIT_ARRAY_H */
