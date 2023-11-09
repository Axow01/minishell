#include "../includes/minishell.h"

static int	number_conv_printerror(int nb)
{
	char	*str;
	int		total;

	total = 0;
	str = ft_itoa(nb);
	total += write(STDERR_FILENO, str, ft_strlen(str));
	mms_free(str);
	return (total);
}

static int	string_conv_printerror(char *str)
{
	return (write(STDERR_FILENO, str, ft_strlen(str)));
}

static int	format_char(char c, va_list *va)
{
	int	total;

	total = 0;
	if (c == 'd')
		total += number_conv_printerror(va_arg(*va, int));
	else if (c == 's')
		total += string_conv_printerror(va_arg(*va, char *));
	else
		total += write(STDOUT_FILENO, &c, 1);
	return (total);
}

int	printf_error(int16_t error_code, char *fmt, ...)
{
	int		total;
	int		i;
	va_list	va;

	total = 0;
	i = 0;
	if (!fmt || !*fmt)
		return (0);
	va_start(va, fmt);
	get_infos()->latest_error_code = error_code;
	while (fmt[i])
	{
		if (fmt[i] == '%')
			total += format_char(fmt[++i], &va);
		else
		{
			write(STDERR_FILENO, &fmt[i], 1);
			total++;
		}
		i++;
	}
	va_end(va);
	return (total);
}
