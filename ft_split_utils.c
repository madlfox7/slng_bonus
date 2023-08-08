#include "so_long.h"

#include "so_long.h"

size_t	ft_strlen_spl(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

void	*ft_memcpy(void	*dst, const void	*src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	if (!src && !dst)
		return (NULL);
	if ((n == 0) || (src == dst))
		return (dst);
	d = dst;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *str)
{
	int		str_len;
	char	*dup;
	int		i;

	i = 0;
	str_len = ft_strlen_spl(str);
	dup = (char *)malloc(sizeof(char) * str_len + 1);
	if (dup == NULL)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen_spl(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
