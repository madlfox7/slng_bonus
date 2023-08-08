#include "so_long.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start] && ft_strchr_v(set, s1[start]))
		start++;
	end = ft_strlen_v(s1);
	while (end && ft_strchr_v(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}

void	split_clean(char **split_res)
{
	int	i;

	i = 0;
	while (split_res[i])
	{
		free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	nl_in_between(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			printf("Error\nEmpty line\n");
			exit(1);
		}
		i++;
	}
}

int	ft_strlen_excl(const char *str)
{
	int len;

	len	= 0;
	while (str[len] != '\0')
        len++;
    return len;
} //change to ft_strlen

void	get_width(char **res, int *width)
{
	int etalon;
	int current_width;

	etalon	= ft_strlen_excl(res[0]);
    for (int i = 0; res[i] != NULL; i++)
    {
		current_width = ft_strlen_excl(res[i]);
        if (res[i][current_width] != '\0' && res[i][current_width] != '\n')
        {
            printf("Error: Line %d is not properly terminated with '\\n' or '\\0'\n", i);
            exit(1);
        }
        if (current_width != etalon)
        {
            printf("Error\nLine %d. Etalon width: %d, Current width: %d\n", i, etalon, current_width);
            exit(1);
        }
    }
    *width = etalon;
} //change fors


void allocate_map(t_data *data)
{
    data->map_copy = (char**)malloc(data->height * sizeof(char*));
    if (data->map_copy == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < data->height; i++)
    {
        data->map_copy[i] = (char*)malloc(data->width * sizeof(char));
        if (data->map_copy[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; j++)
            {
                free(data->map_copy[j]);
            }
            free(data->map_copy);
            exit(EXIT_FAILURE);
        }
    }
    //copy
     data->mapp = (char**)malloc(data->height * sizeof(char*));
    if (data->mapp == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < data->height; i++)
    {
        data->mapp[i] = (char*)malloc(data->width * sizeof(char));
        if (data->mapp[i] == NULL)
        {
            perror("Memory allocation failed");
            for (int j = 0; j < i; j++)
            {
                free(data->mapp[j]);
            }
            free(data->mapp);
            exit(EXIT_FAILURE);
        }
    }
} //too long one


void init_vals(char **res, t_data *data)
{
       for (int i = 0; i < data->height; i++)
       {
        for (int j = 0; j < data->width; j++)
        {
            data->map_copy[i][j] = res[i][j];
             data->mapp[i][j] = res[i][j];
        }
        // printf("\n");
       }
} //change for to while

void check_lines_len(char **res)
{
    int i = 0;
    
     while (res[i])
    {
        i++;
    }
} //change to ft_strlen

void	trim(t_data *data, char *str, int *height, int *width)
{
	char	**res;
	int		size;

	size = 0;
	res = call_split(str, &size);
	check_lines_len(res);
	*height = size;
	get_width(res, width);
	allocate_map(data);
	init_vals(res, data);
	split_clean(res);
}
