#include <stdlib.h>
#include "libft.h"
  
char	**ft_init_chartable(size_t width, size_t height)
{
    char	**tab;
	size_t	i;
 
    if(!(tab = (char**)ft_memalloc(sizeof(char*) * height)))
		return (NULL);
    if(!(tab[0] = (char*)ft_memalloc(sizeof(char) * width * height)))
		return (NULL);
 	i = 0;
	while (i < height)
	{
		tab[i] = *tab + width * i;
		i++;
	}
    return (tab);
}
