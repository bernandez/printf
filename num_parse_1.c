#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "holberton.h"
/**
 * set_number - Retrieves a number from the given string
 * @str: The string to retrieve the number from
 * @number: The pointer to the number
 *
 * Return: The number of positions that were moved
 */
int set_number(const char *str, int *number)
{

char digits[11] = {0};
int i, j = 0;

for (i = 0; str && *(str + i) != '\0'; i++)
{
if (j < 10 && is_digit(*(str + i)))
{
digits[j] = *(str + i);
j++;
}
else
{
break;
}
}
*number = cmp_nums(digits, MAX_WIDTH) <= 0 ? str_to_int(digits) : 0;
return (i - 1);
}

/**
 * set_length - Sets the length in a format info struct
 * @cur: The current character
 * @nxt: The next character
 * @fmt_info: The pointer to the destination fmt_info_t struct
 */
void set_length(char cur, char nxt, fmt_info_t *fmt_info)
{
fmt_info->is_long_double = cur == 'L' ? TRUE : FALSE;
fmt_info->is_long_long = cur == 'l' && nxt == 'l' ? TRUE : FALSE;
fmt_info->is_long = cur == 'l' && nxt != 'l' ? TRUE : FALSE;
fmt_info->is_short = cur == 'h' && nxt != 'h' ? TRUE : FALSE;
fmt_info->is_char = cur == 'h' && nxt == 'h' ? TRUE : FALSE;
}

/**
 * set_flags - Sets the flags in a format info struct
 * @cur: The flag character
 * @fmt_info: The pointer to the destination fmt_info_t struct
 */
void set_flags(char cur, fmt_info_t *fmt_info)
{
fmt_info->space = cur == ' ' ? TRUE : fmt_info->space;
fmt_info->left = cur == '-' || fmt_info->left ? TRUE : FALSE;
fmt_info->show_sign = cur == '+' || fmt_info->show_sign ? TRUE : FALSE;
fmt_info->group = cur == '\'' || fmt_info->group ? TRUE : FALSE;
fmt_info->alt = cur == '#' || fmt_info->alt ? TRUE : FALSE;
fmt_info->pad = cur == '0' ? '0' : fmt_info->pad;
}

/**
 * set_precision - Reads a format info data into the given struct
 * @str: The string contained the format tokens
 * @args: The arguments list
 * @fmt_info: The pointer to the destination fmt_info_t struct
 * @i: The pointer to the position in the format string
 * @error_status: The pointer to the error variable
 */
void set_precision(const char *str, va_list args,
fmt_info_t *fmt_info, int *i, int *error_status)
{
fmt_info->is_precision_set = TRUE;
if (*(str + *i) == '*')
fmt_info->prec = va_arg(args, int);
else if (is_digit(*(str + *i)))
*i += set_number(str + *i, &(fmt_info->prec));
else
*error_status = -1;
}

/**
 * read_format_info - Reads a format info data into the given struct
 * @str: The string contained the format tokens
 * @args: The arguments list
 * @fmt_info: The pointer to the destination fmt_info_t struct
 *
 * Return: The number of positions to skip after the format character (%)
 * , this is negative when there's an error
 */
int read_format_info(const char *str, va_list args, fmt_info_t *fmt_info)
{
int i = 0, no_error = 1, order = 0;

init_format_info(fmt_info);
for (; str && *(str + i) != '\0' && !fmt_info->spec && no_error == 1; i++)
{
if (is_specifier(*(str + i)) && order < 5)
{
fmt_info->spec = *(str + i);
break;
}
else if (is_length(*(str + i)) && order < 4)
{
set_length(*(str + i), *(str + i + 1), fmt_info);
i += *(str + i) == *(str + i + 1) ? 1 : 0;
}
else if (is_flag(*(str + i)) && order < 1)
{
set_flags(*(str + i), fmt_info);
}
else if ((is_digit(*(str + i)) || *(str + i) == '*') && order < 2)
{
if (*(str + i) == '*')
fmt_info->width = va_arg(args, int);
else
i += set_number(str + i, &(fmt_info->width));
fmt_info->is_width_set = TRUE;
}
else if (*(str + i) == '.' && order < 3)
{
i++;
set_precision(str, args, fmt_info, &i, &no_error);
}
else
{
no_error = -1;
}
order += !is_flag(*(str + i));
}
return ((i)*(no_error));
}
