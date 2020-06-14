/* Ido Finkelstein */

#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

/* sets all the bits to 1. */
void SetAll(size_t *bit_array);

/* unsets all the bits. */
void ResetAll(size_t *bit_array);

/* Sets the bit passed as an argument to 1. The bit must be in
   range from 0 to 63. If the bit is already on, it will remain
   unchanged. */
void SetOn(size_t *bit_array, unsigned char bit_position);

/* Unsets the bit passed as an argument. The bit must be in
   range from 0 to 63, or 0 to 31, depand on the system, otherwise
   undefined behaivor is expected.
   If the bit is already off, it will remain unchanged */
void SetOff(size_t *bit_array, unsigned char bit_position);

/* Changes the state of the bit passed as an argument according to parameter
   state, only positive values allowed. State should be 0 for unseting the bit
   or 1 for setting the bit, any other value will be treated as 1. The bit must
   be in range from 0 to 63, or 0 to 31, depand on the system, otherwise
   undefined behaivor is expected. */ 
void SetBit(size_t *bit_array, unsigned char bit_position,unsigned char state);

/* Returns the value of the bit passed as an parameter. The bit
   must be in range from 0 to 63, or 0 to 31, depand on the
   system, otherwise undefined behaivor is expected.*/
char GetVal(size_t *bit_array, unsigned char bit_position);

/* Changes the state of the bit passed as an argument. The bit
   must be in range from 0 to 63, or 0 to 31, depand on the
   system, otherwise undefined behaivor is expected. */ 
void Flip(size_t *bit_array, unsigned char bit_position);

/* Creates a mirror image of the bits in the given array */
void Mirror(size_t *bit_array);

/* Rotates the array n times right, n must be equal or greater then zero. */
void RotR(size_t *bit_array, unsigned char n);

/* Rotates the array n times left, n must be equal or greater than zero. */
void RotR(size_t *bit_array, unsigned char n);

/* Counts number of set bits in the given array */
char CountOn(size_t *bit_array);

/* Counts number of unset bits in the given array */
char CountOff(size_t *bit_array);


#endif /* __BIT_ARRAY_H__ */
