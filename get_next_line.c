#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	int		rd;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	rd = 1;
	while (rd > 0 && !ft_strchr(stash, '\n'))
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[rd] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (stash);
}

static char	*get_line(char *stash)
{
	char	*line;
	int		len;

	if (!stash || !stash[0])
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, len + 1);
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*rest;
	int		i;
	int		len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	len = ft_strlen(stash + i);
	if (!len)
	{
		free(stash);
		return (NULL);
	}
	rest = malloc((len + 1) * sizeof(char));
	if (!rest)
	{
		free(stash);
		return (NULL);
	}
	ft_strlcpy(rest, stash + i, len + 1);
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!stash[fd])
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
