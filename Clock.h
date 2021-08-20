/*
 * Clock.h
 *
 */

#ifndef CLOCK_H_
#define CLOCK_H_

/*
 * Initializes the HFXT Oscillator in the highest power state to allow for 48 MHz operation
 * @param none
 * @return none
 */
void HFXT_Init(void);

/*
 * Initializes the MCLK and SMCLK using the HFXT Oscillator as clock source
 * Sets MCLK frequency to 48 MHz and SMCLK freqency to 12 MHz
 * @param none
 * @return none
 */
void Clock_Init(void);

/*
 * Delay n microseconds
 */
void Clock_Delay1us(uint32_t n);

void delay(unsigned long ulCount);

/*
 * Delay n milliseconds
 */
void Clock_Delay1ms(uint32_t n);



#endif /* CLOCK_H_ */
