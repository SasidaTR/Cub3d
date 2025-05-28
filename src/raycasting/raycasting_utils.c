#include "../../include/cub3d.h"
#include <math.h>

// Draw a vertical strip of wall with textures
void draw_vertical_line(t_data *data, t_ray *ray, int x)
{
    int y;
    int color;
    
    if (x < 0 || x >= WIDTH)
        return;
    
    calculate_wall_texture(ray, data);
    
    y = ray->draw_start;
    if (y < 0)
        y = 0;
    
    while (y <= ray->draw_end && y < HEIGHT)
    {
        color = get_texture_color(ray, data);
        
        // Apply shading for side walls        if (ray->side == 1)
            color = (color >> 1) & 0x7F7F7F;
            
        data->addr[y * WIDTH + x] = color;
        y++;
    }
}

// Draw ceiling, wall, and floor for a screen column
void draw_walls(t_data *data, t_ray *ray, int x)
{
    int y;
    int ceiling_color;
    int floor_color;

    if (x < 0 || x >= WIDTH)
        return;
    ceiling_color = 0x87CEEB;
    floor_color   = 0x2E8B57;
    y = 0;
    while (y < ray->draw_start && y < HEIGHT)
    {
        data->addr[y * WIDTH + x] = ceiling_color;
        y++;
    }
    draw_vertical_line(data, ray, x);
    y = ray->draw_end + 1;
    while (y < HEIGHT)
    {
        data->addr[y * WIDTH + x] = floor_color;
        y++;
    }
}
