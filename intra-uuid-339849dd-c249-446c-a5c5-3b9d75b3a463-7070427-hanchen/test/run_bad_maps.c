/* parse+validate test runner for bad maps */
#include "../inc/cub3d.h"
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s map1.cub [map2.cub ...]\n", av[0]);
        return 2;
    }
    for (int i = 1; i < ac; i++)
    {
        char *path = av[i];
        t_map *map = parse_map(path);
        if (!map)
        {
            printf("%s: PARSE FAILED\n", path);
            continue;
        }
        int valid = validate_map(map);
        printf("%s: PARSE OK, VALIDATE %s\n", path, valid ? "OK" : "FAIL");
        /* free minimal resources (textures + grid + map) */
        if (map->n_texture) free(map->n_texture);
        if (map->s_texture) free(map->s_texture);
        if (map->e_texture) free(map->e_texture);
        if (map->w_texture) free(map->w_texture);
        if (map->grid)
        {
            for (int r = 0; r < map->height && map->grid[r]; r++)
                free(map->grid[r]);
            free(map->grid);
        }
        free(map);
    }
    return 0;
}
