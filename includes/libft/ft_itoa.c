/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayaz <zayaz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:08:07 by zayaz             #+#    #+#             */
/*   Updated: 2023/12/14 14:22:22 by zayaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_size(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
	{
		len++;
	}
	else if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	size_t	len;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_size(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i++;
	}
	str[len] = '\0';
	while (i < len--)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
