/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:15:58 by samoore           #+#    #+#             */
/*   Updated: 2024/02/03 14:35:58 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int	trigger;
	int	count;
	int	i;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	trigger = 1;
	while (str[i] && str[i] != '\n')
	{
		if (is_space(str[i]))
			trigger = 1;
		else if (trigger == 1)
		{
			count++;
			trigger = 0;
		}
		i++;
	}
	return (count);
}

char	*copy_word(char *str, int start, int j)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	res = malloc(sizeof(char) * (j - start + 1));
	while (start < j)
		res[i++] = str[start++];
	res[i] = 0;
	return (res);
}

char	**ft_split_space(char *str)
{
	char	**res;
	int		start;
	int		i;
	int		j;

	j = 0;
	if (!str)
		return (NULL);
	i = count_words(str);
	res = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!is_space(str[i]))
		{
			start = i;
			while (str[i] && !is_space(str[i]) && str[i] != '\n')
				i++;
			res[j++] = copy_word(str, start, i);
		}
		else 
			i++;
	}
	free (str);
	res[j] = 0;
	return (res);
}
