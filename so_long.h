#ifndef SO_LONG_H
# define SO_LONG_H

#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#include <stdio.h> //test
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//#include "get_next_line.h"
#include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_data
{
    int width;  //lines of text
    int height; //numbers in a line
    char **map_copy; //matrix of height * width 
    char **mapp;
    int moves;
    int win_h;
    int win_w;
    int enemy_count;
  //  int exit_x;
//    int exit_y;
    int animation_frame;
    int player_x;
    int player_y;
   //getting from the file with gnl and split and atoi and assigning to matrix elements;
    void	*player;
    void	*player_frames[4][2];
	void	*exit;
	int current_direction;
    void    *collectable;
    void    *wall;
    void    *free_space;
    void    *enemy;
    void *mlx; //connection ptr
    void *win; //window ptr
    char **original_map;
} t_data;


//main.c

void print_matrix(const t_data *data); //delete later
void free_map(t_data *data);
void free_data(t_data *data);
void print_processed_map(char *processed_map);
void get_map1(char *filename, t_data *data);
int valid_char(char c);
int valid(t_data *data);
int object_counter(t_data *data, int *player_count, int *exit_count, int *collectable);
void borders(t_data *data);
int flood_fill(t_data *data, int x, int y, int *exit_is_accessable);
int is_map_valid(t_data *data);
void  map_validation(t_data *data);


//file_pars_utils.c
int	ft_strncmp(const char *s1, const char *s2, size_t	n);
char	*ft_strchr_v(const char	*str, int c);
size_t	ft_strlen_v(const char *str);
void check_filename(char *filename);


//get_next_line_utils.c 

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char	*s);

//get_next_line.c

char	*ft_parc_buf(char *buf);
char	*ft_check(char *buf, char *result, int i);
char	*ft_parc1(char *buf);
char *get_next_line(int fd);

//join_lines.c 
void	*ft_memset(void *str, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin2(char *s1, char *s2);

//ft_split.c
size_t	ft_strlen_spl(const char *str);
void	*ft_memcpy(void	*dst, const void	*src, size_t n);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_memory(char **ptr_ss, long index);
long	count_of_words(char const *s, char c);
long	word_len(char const *s, char c, long i);
char	**ft_split(char const *s, char c, int *size, long *i);
char	**call_split(char *res, int *size);


//trim_nl.c
char	*ft_strtrim(char const *s1, char const *set);
void	split_clean(char **split_res);
void nl_in_between(char *str);
int ft_strlen_excl(const char *str);
void get_width(char **res, int *width);
void allocate_map(t_data *data);
void init_vals(char **res, t_data *data);
void check_lines_len(char **res);
void trim(t_data *data, char *str, int *height, int *width);


#endif
