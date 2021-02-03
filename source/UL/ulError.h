/*
 * ulError.h
 *
 *  Created on: Feb 1, 2021
 *      Author: oleksandr.gonchar
 */

#ifndef UL_ULERROR_H_
#define UL_ULERROR_H_

typedef enum
{
  ulError_OK         =  0,
  ulError_NULL       = -1,
  ulError_OutOfRange = -2
}ulError_code_t;

#endif /* UL_ULERROR_H_ */
