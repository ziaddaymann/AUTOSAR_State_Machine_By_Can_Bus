 /******************************************************************************
 *
 * Module: Standartd Types 
 *
 * File Name: StandardTypes.h
 *
 * Description: Header file to include all typedef.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/


#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char         boolean;
/* Boolean Data Type */

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)

#define NULL_PTR    ((void*)0)

/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
//typedef unsigned long         uint32_t;         /*           0 .. 4294967295      */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */

typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;



#define STD_HIGH        0x01U       /* Standard HIGH */
#define STD_LOW         0x00U       /* Standard LOW */

#define STD_ACTIVE      0x01U       /* Logical state active */
#define STD_IDLE        0x00U       /* Logical state idle */

#define STD_ON          0x01U       /* Standard ON */
#define STD_OFF         0x00U       /* Standard OFF */

#endif /* STD_TYPES_H */