#include "so_long.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strchr_v(const char	*str, int c)
{
	char	*s;
	size_t	i;
	size_t	found;

	s = (char *)str;
	found = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	else if (found)
		return ((char *)&s[i]);
	else
		return (NULL);
}

size_t	ft_strlen_v(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

void	check_filename(char *filename)
{
	size_t	arg_len;
	char	*extension;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nNo such file or directory\n");
		close(fd);
		exit(1);
	}
	close(fd);
	arg_len = ft_strlen_v(filename);
	if (arg_len < 5)
	{
		printf("Error\nInvalid map extension: file must end with '.ber'\n");
		exit(1);
	}
	extension = &filename[arg_len - 4];
	if (ft_strncmp(extension, ".ber", ft_strlen_v(extension)) != 0)
	{
		printf("Error\nInvalid map extension: file must end with '.ber'\n");
		exit(1);
	}
}
