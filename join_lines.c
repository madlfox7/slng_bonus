#include "so_long.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *)str + i) = c;
		i++;
	}
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	dst = malloc(count * size);
	if (dst == NULL)
		return (NULL);
	ft_memset((unsigned char *)dst, 0, count * size);
	return (dst);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		s1_i;
	int		s2_i;
	char	*con;

	s1_i = 0;
	s2_i = 0;
	con = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!con)
		return (NULL);
	while (s1 && s1[s1_i] != '\0')
	{
		con[s1_i] = s1[s1_i];
		s1_i++;
	}
	while (s2 && s2[s2_i] != '\0')
	{
		con[s1_i] = s2[s2_i];
		s1_i++;
		s2_i++;
	}
	con[s1_i] = '\0';
	if (s1)
		free (s1);
	return (con);
}
