/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 14:36:12 by droly             #+#    #+#             */
/*   Updated: 2016/05/06 14:55:44 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words_split(char const *s, char c)
{
	int		nb;
	int		start;
	int		pos;

	pos = 0;
	start = -1;
	nb = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] != c && start == -1)
			start = 0;
		else if (s[pos] == c && start != -1)
		{
			nb++;
			start = -1;
		}
		pos++;
	}
	if (start != -1)
		nb++;
	return (nb);
}

static int	next_pointer_pos(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		next_ptr;
	int		arr_pos;
	int		i;

	if (s == NULL)
		return (NULL);
	if ((array = (char **)malloc((count_words_split(s, c) + 1)
			* sizeof(char *))) == NULL)
		return (NULL);
	arr_pos = 0;
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		++i;
	while (s[i] != '\0')
	{
		next_ptr = next_pointer_pos(&(s[i]), c);
		if ((array[arr_pos++] = ft_strsub(&(s[i]), 0, next_ptr)) == NULL)
			return (NULL);
		i += next_ptr;
		while (s[i] != '\0' && s[i] == c)
			++i;
	}
	array[arr_pos] = NULL;
	return (array);
}
