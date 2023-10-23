/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:12:45 by egomez-g          #+#    #+#             */
/*   Updated: 2023/10/18 13:18:37 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	size_t	sol_len;
	char	*sol;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = (ft_strdup(""));
	sol_len = ft_strlen(s1) + ft_strlen(s2);
	sol = malloc ((sol_len + 1) * sizeof(char));
	if (sol == NULL)
		return (free_all(&s1));
	i = 0;
	while (*(s1 + i))
	{
		sol[i] = s1[i];
		i++;
	}
	j = 0;
	while (*(s2 + j))
		sol[i++] = s2[j++];
	sol[i] = '\0';
	free(s1);
	return (sol);
}

static char	*new_file(char *file)
{
	char	*ptr;
	size_t	len;

	ptr = ft_strchr(file, '\n');
	if (!ptr)
		return (free_all(&file));
	len = ptr - file + 1;
	if (!file[len])
		return (free_all(&file));
	ptr = ft_substr(file, len, ft_strlen(file) - len);
	free_all(&file);
	if (!ptr)
		return (NULL);
	return (ptr);
}

static char	*get_line(char *file)
{
	char	*line;
	size_t	len;

	line = ft_strchr(file, '\n');
	if (!line)
		len = ft_strlen(file);
	else
		len = line - file + 1;
	line = ft_substr(file, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_file(int fd, char *file)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_all(&file));
	buffer[0] = '\0';
	while (bytes_read > 0 && !ft_strchr(file, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			file = ft_strjoin(file, buffer);
		}
	}
	free (buffer);
	if (bytes_read == -1)
		return (free_all(&file));
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file[1024];
	char		*line;

	if (fd < 0 || fd >= 1024)
		return (NULL);
	if (!file[fd] || !ft_strchr(file[fd], '\n'))
		file[fd] = read_file(fd, file[fd]);
	if (!file[fd])
		return (NULL);
	line = get_line(file[fd]);
	if (!line)
		return (free_all(&file[fd]));
	file[fd] = new_file(file[fd]);
	return (line);
}

/*int main(void)
{
	char *xd;
	int hola = open("hola.txt", O_RDONLY);
	int que = open("que.txt", O_RDONLY);
	int tal = open("tal.txt", O_RDONLY);
	xd = get_next_line_bonus(hola);
	printf("%s", xd);
    xd = get_next_line_bonus(que);
    printf("%s", xd);
    xd = get_next_line_bonus(tal);
    printf("%s", xd);
    xd = get_next_line_bonus(hola);
    printf("%s", xd);
    xd = get_next_line_bonus(que);
    printf("%s", xd);
    xd = get_next_line_bonus(tal);
    printf("%s", xd);
	close (hola);
	close (que);
	close (tal);
	return (0);
}*/
