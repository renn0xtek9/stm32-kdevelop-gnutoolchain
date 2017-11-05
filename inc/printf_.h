/** \file printf.h
 * Simplified printf() and sprintf() implementation - prints formatted string to
 * USART (or whereever). Most common % specifiers are supported. It costs you about
 * 3k FLASH memory - without floating point support it uses only 1k ROM!
 * \author Freddie Chopin, Martin Thomas, Marten Petschke and many others
 * \date 16.2.2012
 */

/******************************************************************************
* chip: STM32F10x
* compiler: arm-none-eabi-gcc 4.6.0
*
* global functions:
* 	int printf_(const char *format, ...)
* 	int sprintf_(char *buffer, const char *format, ...)
*
* STM32 specific functions:
*         init_UART1(void)
*	void putc_UART1 (char);                // blocking put char, used by printf()
*
* local functions:
* 	int putc_strg(int character, printf_file_t *stream)
* 	int vfprintf_(printf_file_t *stream, const char *format, va_list arg)
* 	void long_itoa (long val, int radix, int len, vfprintf_stream *stream)
*
******************************************************************************/

int printf_(const char *format, ...);
int sprintf_(char *buffer, const char *format, ...);

