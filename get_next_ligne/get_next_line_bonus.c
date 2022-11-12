/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majmani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:06:03 by majmani           #+#    #+#             */
/*   Updated: 2022/11/09 18:06:06 by majmani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *str)
{
	char	*s;
	int		r;

	r = 1;
	s = malloc((size_t)BUFFER_SIZE + 1);
	if (s == NULL)
		return (0);
	while (!ft_strchr(str, '\n') && r != 0)
	{
		r = read(fd, s, BUFFER_SIZE);
		if (r == -1)
		{
			free(str);
			free(s);
			return (NULL);
		}
		s[r] = '\0';
		str = ft_strjoin(str, s);
	}
	free(s);
	return (str);
}

char	*before(char *s)
{
	char	*sh;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		sh = malloc(i + 1);
	else
		sh = malloc(i + 2);
	if (sh == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		sh[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		sh[i++] = '\n';
	sh[i] = '\0';
	return (sh);
}

char	*after(char *s)
{
	char	*sh;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	sh = malloc(ft_strlen(s) - i + 1);
	if (sh == NULL)
		return (NULL);
	while (s[++i] != '\0')
		sh[j++] = s[i];
	sh[j] = '\0';
	free(s);
	return (sh);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*l;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	str[fd] = ft_read(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	l = before(str[fd]);
	str[fd] = after(str[fd]);
	if (l[0] == '\0')
	{
		free(l);
		return (NULL);
	}
	return (l);
}
