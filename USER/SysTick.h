#ifndef __SYSTICK_H
#define __SYSTICK_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

/*
 *	These inlines deal with timer wrapping correctly. You are 
 *	strongly encouraged to use them
 *	1. Because people otherwise forget
 *	2. Because if the timer wrap changes in future you won't have to
 *	   alter your driver code.
 *
 * time_after(a,b) returns true if the time a is after time b.
 *
 * Do this with "<0" and ">=0" to only test the sign of the result. A
 * good compiler would generate better code (and a really good compiler
 * wouldn't care). Gcc is currently neither.
 */
#define time_after(a,b)  ( ((long)((b) - (a)) < 0))

void SysTick_Init(void);
unsigned int SysTick_GetTick(void);
#ifdef __cplusplus
 }
#endif


#endif /* __SYSTICK_H */
