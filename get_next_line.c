#include "so_long.h"
#define BUFFER_SIZE 100000

char	*ft_parc_buf(char *buf)
{
	int		j;
	int		i;
	char	*rem;

	i = 0;
	j = 0;
	if (buf == 0 || *buf == 0)
		return (NULL);
	if (ft_strchr(buf, '\n') != NULL)
	{
		while (buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
			i++;
		rem = (char *)malloc(sizeof(char) * ft_strlen(ft_strchr(buf, '\n')));
		if (!rem)
			return (NULL);
		while (buf[i] != '\0')
			rem[j++] = buf[i++];
		rem[j] = '\0';
		free(buf);
		buf = 0;
		return (rem);
	}
	return (NULL);
}

char	*ft_check(char *buf, char *result, int i)
{
	if (buf[i] == '\n')
	{
		result[i] = '\n';
		result[i + 1] = '\0';
	}
	else
	{
		result[i] = '\0';
		free(buf);
		buf = NULL;
	}
	return (result);
}

char	*ft_parc1(char *buf)
{
	int		i;
	char	*result;

	i = 0;
	if (buf == 0 || *buf == 0)
	{
		if (buf)
			free(buf);
		return (NULL);
	}
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		result[i] = buf[i];
		i++;
	}
	return (ft_check(buf, result, i));
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static int	buf_index;
	static int	bytes_read;
	char		*result;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (1)
	{
		if (buf_index >= bytes_read)
		{
			buf_index = 0;
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			buf[bytes_read] = '\0';
		}
		if (buf[buf_index] == '\n')
		{
			result[i] = '\n';
			result[i + 1] = '\0';
			buf_index++;
			return (result);
		}
		else if (buf[buf_index] == '\0')
		{
			if (i == 0)
			{
				free(result);
				return (NULL);
			}
			result[i] = '\0';
			buf_index++;
			return (result);
		}
		result[i] = buf[buf_index];
		i++;
		buf_index++;
		if (i >= BUFFER_SIZE)
		{
			free(result);
			return (NULL);
		}
	}
	if (i > 0)
	{
		result[i] = '\0';
		return (result);
	}
	free(result);
	return (NULL);
}
