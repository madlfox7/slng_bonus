#include "so_long.h"


char	*ft_strdup_itoa(const char *str)
{
	
	char	*dup;
	int		i;

	i = 0;
	
	dup = (char *)malloc(sizeof(char) *  ft_strlen_v(str) + 1);
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

int	count_digits(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		len = 1;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*handle_zero(int n)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	str[0] = n + '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	len;

	if (n == 0)
		return (handle_zero(0));
	if (n == -2147483648)
		return (ft_strdup_itoa("-2147483648"));
	len = count_digits(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

void print_2d_matrix(char **matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_matrix(const t_data *data) //delete later
{
    if (data == NULL || data->map_copy == NULL)
    {
        printf("Matrix is not initialized.\n");
        return;
    }

    for (int i = 0; i < data->height; i++)
    {
        for (int j = 0; j < data->width; j++)
        {
            printf("%c", data->map_copy[i][j]);
        }
        printf("\n");
    }
}


void free_map(t_data *data)
{
    if (data->map_copy == NULL)
        return;

    for (int i = 0; i < data->height; i++) {
        free(data->map_copy[i]);
    }
    free(data->map_copy);
    data->map_copy = NULL; // to avoid 2* freeing
    //copy map free
     if (data->mapp == NULL)
        return;

    for (int i = 0; i < data->height; i++) {
        free(data->mapp[i]);
    }
    free(data->mapp);
    data->mapp = NULL; // to avoid 2* freeing

}

void free_data(t_data *data)
{
    free_map(data);
    free(data); 
}




void get_map1(char *filename, t_data *data)
{
    char *str = NULL;
    int fd;
    char *line;
    char *res;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
      //  perror("Error opening file\n");
        printf("Error\nNo such file or directory\n");
        exit(1);
    }

    line = get_next_line(fd);
    if (!line)
    {
        printf("Error\nEmpty file");
        exit(1);
    }

    str = ft_calloc(1, 1);
    while (line)
    {
        str = ft_strjoin2(str, line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);

   // printf("Raw map data:\n");
    //printf("%s\n", str);
   // printf("=============\n");

    res = ft_strtrim(str, "\n");
    nl_in_between(res);

    // Print the processed map data
   // print_processed_map(res);

    trim(data, res, &(data->height), &(data->width));
    free(str);
    free(res);
}


int valid_char(char c)
{
    if (c == '0' || c == '1' || c == 'E' || c == 'P' || c == 'C' || c == 'T')
        return 1;
    return 0;
}

int valid(t_data *data)
{

    for (int i = 0; i < data->height; i++)
    {
        for (int j = 0; j < data->width; j++)
        {
            if (!valid_char(data->map_copy[i][j]) )
            {
                return 0;
            }
        }
    }
    return 1;
}



int object_counter(t_data *data, int *player_count, int *exit_count, int *collectable)
{
   int empty_space = 0;
   
      for (int i = 0; i < data->height; i++)
    {
        for (int j = 0; j < data->width; j++)
        {
            if (data->map_copy[i][j] == 'P')
            {
                (*player_count)++;
            }
            if (data->map_copy[i][j] == 'E')
            {
                (*exit_count)++;
            }
            if (data->map_copy[i][j] == 'C')
            {
                (*collectable)++;
            }
            if (data->map_copy[i][j] == '0')
                empty_space++;
        }
    }
   if (*player_count != 1 || *exit_count != 1 || *collectable == 0 || !empty_space)
   {
       if (!empty_space)
            printf("Error : no space to move\n");
       return 1;
   }
   return 0;
}


void borders(t_data *data)
{
    
    if (data->width < 3 || data->height < 3)
        exit(1); ///?????
    for (int i = 0; i < data->height; i++)
    {
          for (int j = 0; j < data->width; j++)
          {
                if ((i == 0 || i == (data->height - 1)) && data->map_copy[i][j] != '1')
                {
                    printf("Map must be surrounded by walls\n");
                    exit(1);
                }
                else if ((j == 0 || j == data->width - 1 ) && data->map_copy[i][j] != '1')
                {
                       printf("Map must be surrounded by walls\n");
                    exit(1);
                }
          }
          
    }
}

///////////////////////////


int flood_fill(t_data *data, int x, int y, int *exit_is_accessable)
{
    static int count_of_collect_reached;
    
    if (data->map_copy[y][x] == 'C')
    {
        count_of_collect_reached++;
    }
      if (data->map_copy[y][x] == 'E')
    {
        *exit_is_accessable = 1;
       // printf("collect found in %d %d\n", y, x);
    }
   // printf("count C %d\n", count_of_collect_reached);
    if (x < 0 || y < 0 || x >= data->width || y >= data->height)
        return count_of_collect_reached;
    if (data->map_copy[y][x] != '0' && data->map_copy[y][x] != 'P' && data->map_copy[y][x] != 'C')
        return count_of_collect_reached;
    if (data->map_copy[y][x] == 'V')
        return count_of_collect_reached;
  
    data->map_copy[y][x] = 'V';
  //  printf("\n\n__count = %d\n", *collect_count);
    flood_fill(data, x + 1, y, exit_is_accessable); 
    flood_fill(data, x - 1, y, exit_is_accessable); 
    flood_fill(data, x, y + 1, exit_is_accessable); 
    flood_fill(data, x, y - 1, exit_is_accessable); 
     return count_of_collect_reached;
}

void get_collect_count(t_data *data, int *collect_count)
{
    //int x = 0;
   // int y = 0;
    
     for (int y = 0; y < data->height; y++)
    {
        for (int x = 0; x < data->width; x++)
        {
             if (data->map_copy[y][x] == 'C')
             {
                 (*collect_count)++;
             }
        }
    }
    if (!(*collect_count))
    {
        printf("No collectables found\n");
        exit(1);
    }
}


int is_map_valid(t_data *data)
{
    int player_x = -1;
    int player_y = -1;
    int player_found = 0;
    int exit_found = 0;
    int collect_count = 0;
    int exit_is_accessable = 0;
    
    
    for (int y = 0; y < data->height; y++)
    {
        for (int x = 0; x < data->width; x++)
        {
            if (data->map_copy[y][x] == 'P')
            {
                if (player_found)
                {
                    printf("Error: Multiple players (P) found!\n");
                    return 0;
                }
                player_x = x;
                player_y = y;
                player_found = 1;
            }
            else if (data->map_copy[y][x] == 'E')
            {
                if (exit_found)
                {
                    printf("Error: Multiple exits (E) found!\n");
                    return 0;
                }
                exit_found = 1;
            }
        }
    }
    get_collect_count(data, &collect_count);
   // printf("\ncollect count = %d\n", collect_count);
   
    if (!player_found)
    {
        printf("Error: Player (P) not found!\n");
        return 0;
    }

    if (!exit_found)
    {
        printf("Error: Exit (E) not found!\n");
        return 0;
    }
    if (flood_fill(data, player_x, player_y, &exit_is_accessable) != collect_count || !exit_is_accessable)
    {
        printf("Invalid map, collectables are not accessible or exit is blocked\n");
        exit(1);
    }
  
    for (int y = 0; y < data->height; y++)
    {
        for (int x = 0; x < data->width; x++)
        {
            if (data->map_copy[y][x] == 'V')
            {
                data->map_copy[y][x] = '0';
            }
        }
    }
    //printf("The map is valid and playable!\n");
    return 1;
}

//////////////////////////////////////////
void  map_validation(t_data *data)
{
    if (!valid(data))
    {
        printf("Error: invalid character in the line\n");
        exit(1);
    }
    /*if (data->height > 16 || data->width > 32)
    {
        printf("The map is too big for this screen. Programm stopped\n");
        exit(0);
    }*/
    borders(data);
   if (!is_map_valid(data))
   {
       exit(1);
   }
}
void	load_image(t_data *data)
{

   int size_h = (data->win_h) / 64;
   int size_w = (data->win_w) / 64;
   data->player_frames[0][0] = mlx_xpm_file_to_image(data->mlx, "assets/f1.xpm", &size_h, &size_w);
   data->player_frames[0][1] = mlx_xpm_file_to_image(data->mlx, "assets/f2.xpm", &size_h, &size_w);
   data->player_frames[1][0] = mlx_xpm_file_to_image(data->mlx, "assets/b1.xpm", &size_h, &size_w);
   data->player_frames[1][1] = mlx_xpm_file_to_image(data->mlx, "assets/b2.xpm", &size_h, &size_w);
   data->player_frames[2][0] = mlx_xpm_file_to_image(data->mlx, "assets/l1_1.xpm", &size_h, &size_w);
   data->player_frames[2][1] = mlx_xpm_file_to_image(data->mlx, "assets/l2.xpm", &size_h, &size_w);
   data->player_frames[3][0] = mlx_xpm_file_to_image(data->mlx, "assets/r1.xpm", &size_h, &size_w);
   data->player_frames[3][1] = mlx_xpm_file_to_image(data->mlx, "assets/r2.xpm", &size_h, &size_w);
	if (!data->player_frames[0][0] || !data->player_frames[0][1] || !data->player_frames[1][0] || !data->player_frames[1][1] || !data->player_frames[2][0] || !data->player_frames[2][1] || !data->player_frames[3][0] || !data->player_frames[3][1])
    {
        printf("Error: Failed to load images.\n");
        exit(1);
    }
     data->player = mlx_xpm_file_to_image(data->mlx, "assets/pl.xpm", &size_h, &size_w);
    data->wall = mlx_xpm_file_to_image(data->mlx, "assets/wall_1.xpm", &size_h, &size_w);
    data->free_space = mlx_xpm_file_to_image(data->mlx, "assets/floor.xpm", &size_h, &size_w);
    data->collectable =  mlx_xpm_file_to_image(data->mlx, "assets/collectable.xpm", &size_h, &size_w);
    data->exit =  mlx_xpm_file_to_image(data->mlx, "assets/exit.xpm", &size_h, &size_w);
    data->enemy =  mlx_xpm_file_to_image(data->mlx, "assets/enemy.xpm", &size_h, &size_w);
 if (!data->player || !data->wall || !data->free_space || !data->collectable || !data->exit || !data->enemy)
    {
        printf("Error: Failed to load images.\n");
        exit(1);
    }
    data->moves = 0;
}
void ft_image(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
   // printf("___data height %d\n", data->height);
    while (i < data->height)
    {
       // printf("___data height %d\n", data->height);
        j = 0;
        while (j < data->width)
        {
            if (data->mapp[i][j] == '1')
            {
                mlx_put_image_to_window(data->mlx, data->win, data->wall, j * 64, i * 64);
            }
            else if (data->mapp[i][j] == 'P')
            {
		int frame_index = 0;
		if (data->current_direction == BACK)
		{
		frame_index = 1;
		}
	 	else if (data->current_direction == LEFT)
		{
		frame_index = 2;
		}	
		else if (data->current_direction == RIGHT)
		{
			frame_index = 3;
		}
	  mlx_put_image_to_window(data->mlx, data->win, data->player_frames[frame_index][data->animation_frame - 1], j * 64, i * 64);
            }
             else if (data->mapp[i][j] == '0')
            {
                mlx_put_image_to_window(data->mlx, data->win, data->free_space, j * 64, i * 64);
            }
              else if (data->mapp[i][j] == 'C')
            {
                mlx_put_image_to_window(data->mlx, data->win, data->collectable, j * 64, i * 64);
            }
          else if (data->mapp[i][j] == 'E')
            {
                mlx_put_image_to_window(data->mlx, data->win, data->exit, j * 64, i * 64);
            }
              else if (data->mapp[i][j] == 'T')
            {
                mlx_put_image_to_window(data->mlx, data->win, data->enemy, j * 64, i * 64);
            }
            j++;
        }
        i++;
    }
 }

void find_player_coordinates(t_data *data)
{
    int i = 0;
    int j = 0;
    data->player_x = 0;
    data->player_y = 0;

     while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
          if (data->mapp[i][j] == 'P')
			{
				data->player_x = i;
				data->player_y = j;
				break ;
			}
            j++;
        }
        i++;
    }
}

//check win condition 

int win_case(t_data *data)
{
	int	i;
	int	j;
	int	coll_count;

	i = 0;
	coll_count = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->mapp[i][j] == 'C')
				coll_count++;
            j++;
		}
        i++;
	}
	if (coll_count == 0)
		return (1);
	return (0);
}


int write_moves(t_data *data)
{
    char *move_str = ft_itoa(data->moves);
    int text_color = 0xF5F5DC; 

    mlx_string_put(data->mlx, data->win, 20, 24, text_color, move_str);
    free(move_str); 
    return 0;
}

void w_is_pressed(t_data *data)
{
    if  (data->mapp[data->player_x - 1][data->player_y] == 'T')
    {
        printf("Oh no, Techie caught a bug. GAME OVER\n");
        exit(0);
    }
    if (data->mapp[data->player_x - 1][data->player_y] == 'E') // Exit cell
    {
        if (win_case(data))
        {
            printf("Good job! You helped Techie, he will never forget it ◡̈\n");
            exit(0);
        }
        else
        {
            // data->mapp[data->player_x - 1][data->player_y] = 'P';
            // data->mapp[data->player_x][data->player_y] = '0';
            // data->moves++;
            // printf("moves \n%d\n", data->moves);
            return ;
        }
    }
    
    if (data->mapp[data->player_x - 1][data->player_y] != '1') // Empty cell
    {
        data->mapp[data->player_x - 1][data->player_y] = 'P';
        data->mapp[data->player_x][data->player_y] = '0';
        data->moves++;
        //function to put moves on screen 
        write_moves(data);
       // printf("moves \n%d\n", data->moves);
    }
    data->animation_frame = (data->animation_frame == 1) ? 2 : 1;
    data->current_direction = BACK;
}

void s_is_pressed(t_data *data)
{
     if (data->mapp[data->player_x + 1][data->player_y] == 'T')
     {
        printf("Oh no, Techie caught a bug. GAME OVER\n");
        exit(0);
    }
    if (data->mapp[data->player_x + 1][data->player_y] == 'E') // Exit cell
    {
        if (win_case(data))
        {
            printf("Cheers! You did it ◡̈ \nTechie is grateful for your help and wishes you a bug-free coding experience 💻\n");
            exit(0);
        }
        else
        {
        //     data->mapp[data->player_x + 1][data->player_y] = 'P';
        //     data->mapp[data->player_x][data->player_y] = '0';
        //     data->moves++;
        //     printf("moves \n%d\n", data->moves);
        return ;
        }
    }
     
  if (data->mapp[data->player_x + 1][data->player_y] != '1') // Empty cell
    {
        data->mapp[data->player_x + 1][data->player_y] = 'P';
        data->mapp[data->player_x][data->player_y] = '0';
        data->moves++;
         write_moves(data);
     //   printf("moves \n%d\n", data->moves);
    }
//  data->animation_frame = 1;
data->animation_frame = (data->animation_frame == 1) ? 2 : 1;

  data->current_direction = FRONT;
}

void a_is_pressed(t_data *data)
{
     if  (data->mapp[data->player_x][data->player_y - 1] == 'T')
    {
        printf("Oh no, Techie caught a bug. GAME OVER\n");
        exit(0);
    }
    if (data->mapp[data->player_x][data->player_y - 1] == 'E') // Exit cell
    {
        if (win_case(data))
        {
            printf("Cheers! You did it ◡̈\nP.S. Wish you a bug-free coding experience 💻\n");
            exit(0);
        }
        else
        {
           return ;
        }
    }
     
    if (data->mapp[data->player_x][data->player_y - 1] != '1') // Empty cell
    {
        data->mapp[data->player_x][data->player_y - 1] = 'P';
        data->mapp[data->player_x][data->player_y] = '0';
        data->moves++;
         write_moves(data);
       // printf("moves \n%d\n", data->moves);
    }
     data->animation_frame = (data->animation_frame == 1) ? 2 : 1;
     data->current_direction = LEFT;
}


void d_is_pressed(t_data *data)
{
      if  (data->mapp[data->player_x][data->player_y + 1] == 'T')
    {
        printf("Oh no, Techie caught a bug. GAME OVER\n");
        exit(0);
    }
    if (data->mapp[data->player_x][data->player_y + 1] == 'E') // Exit cell
    {
        if (win_case(data))
        {
            printf("Cheers! You helped Techie get to the computer and start working ◡̈\n P. S. Wish you a bug-free coding experience 💻\n");
            exit(0);
        }
        else
        {
           return ;
        }
    }
    if (data->mapp[data->player_x][data->player_y + 1] != '1') // Empty cell
    {
        data->mapp[data->player_x][data->player_y + 1] = 'P';
        data->mapp[data->player_x][data->player_y] = '0';
        data->moves++;
        //int		mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string);
     write_moves(data);
      // printf("moves \n%d\n", data->moves);
    }
    data->animation_frame = (data->animation_frame == 1) ? 2 : 1;
	data->current_direction = RIGHT;
}


int handle_key(int keycode, t_data *data)
{
    find_player_coordinates(data);

    if (keycode == XK_Escape)
    {
        printf("Techie is tired and decided to go on vacation, work will wait ✈️\n");
        exit(0);  
    } //ESC
    else if (keycode == XK_w && data->mapp[data->player_x - 1][data->player_y] != '1') //not wall w is pressed
    {	
    	data->current_direction = FRONT;	    
	    w_is_pressed(data);
    }
    else if (keycode == XK_s && data->mapp[data->player_x + 1][data->player_y] != '1')
    {	   
	    data->current_direction = BACK;
	    s_is_pressed(data);
    }
    else if (keycode == XK_a && data->mapp[data->player_x][data->player_y - 1] != '1')
    {
	    data->current_direction = LEFT;
    	    a_is_pressed(data);
    }
    else if (keycode == XK_d && data->mapp[data->player_x][data->player_y + 1] != '1')
    {
	    data->current_direction = RIGHT;
    	    d_is_pressed(data);
    }

 mlx_clear_window(data->mlx, data->win);
ft_image(data);
	 return (0); //because of mlx, if worked correctly
}
int close_with_x(t_data *data)
{
    printf("Techie decided to go on a vacation. Work will wait ✈️\n");
	mlx_destroy_window(data->mlx, data->win);
    exit(0);
}

/*int animate(t_data *data)
{
	data->animation_frame = (data->animation_frame == 1) ? 2 : 1;
	ft_image(data);
        mlx_clear_window(data->mlx, data->win);

	return 0;
}
*/
void graphics(t_data *data)
{
    data->win_h = (data->height) * 64;
    data->win_w = (data->width) * 64;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->win_w, data->win_h, "so_long");
  //  printf("win_h %d win_w %d\n", data->win_w, data->win_h);
    load_image(data); 
    data->animation_frame = 1;
    data->current_direction = FRONT;
    ft_image(data);
    mlx_hook(data->win, KeyPress, KeyPressMask, handle_key, data);
     mlx_hook(data->win, 17, 0, close_with_x, data);
//     	mlx_loop_hook(data->mlx, animate, data);
        mlx_loop_hook(data->mlx, write_moves, data);

    mlx_loop(data->mlx);
}

int main(int argc, char **argv)
{
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
    {
       printf("Memory allocation error\n");
        exit(1);
    }
    data->width = 0;
    data->height = 0;
    data->map_copy = NULL; 
    if (argc == 2)
    {
        check_filename(argv[1]);
        get_map1(argv[1], data);
    }
    else
    {
       printf("Usage: %s <filename>(or path)\n", argv[0]);
       return 1;
    }
    map_validation(data);
    graphics(data);
    //printf("width %d height %d\n", data->width, data->height);
    free_data(data);
    return 0;
}

