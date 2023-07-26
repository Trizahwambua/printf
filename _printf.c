#include "main.h"
void print_buffer(char buffer[], int *buff_ind);
/**
* _printf - printf func
* @format: param 1
* Return: printed characters
*/
int _printf(const char *format, ...)
{
	int i, ptd = 0, ptd_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	return (-1);
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			ptd_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			i++;
			ptd = handle_print(format, &i, list,
					buffer, flags, width, precision, size);
			if (ptd == -1)
				return (-1);
			ptd_chars += ptd;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (ptd_chars);
}
/**
* print_buffer - outputs the contents of the buffer
* @buffer: - arr of characters
* @buff_ind: - index at which to add nxt the character
*/
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
