/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 17:14:50 by pmartine          #+#    #+#             */
/*   Updated: 2016/10/29 16:53:04 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<../includes/rtv1.h>

static void	ft_put_pixel(t_env	*env, int x, int y, int color)
{
	int		i;
	unsigned int	p;

	i = 0;
	p = x * (env->img->bpp / 8) + y * (env->img->s_line);
	while (i < (env->img->bpp / 8))
	{
		env->img->data[p + i] = color;
		color >>= 8;
		i++;
	}
}

static void create_ray(t_env *e, int x, int y)
{
	t_vec	v1;
	t_vec	v2;

	v1 = new_vec(0,0,0);
	v2.x = x - (W / 2);
	v2.y = y - (H / 2);
	v2.z = -(W / (2 * tan(FOV / 2)));
	v2 = norm_vect(v2);
	e->ray_dir = sub_vect(v2, v1);
	e->ray_pos = v1;
}

static int	lambert_rgb(int r, int g, int b, double lambert)
{
	r *= lambert;
	g *= lambert;
	b*= lambert;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

static double	calc_lamb(t_env	*env, t_vec	pos)
{
	t_vec	vec;
	t_vec	cam;
	t_vec	yo;
	double	lambert;

	cam = scale_vect(env->ray_dir, env->d);
	cam = add_vect(env->ray_pos, cam);
	yo = sub_vect(cam, env->spots->pos);
	yo = norm_vect(yo);
	vec = sub_vect(pos, cam);
	vec = norm_vect(vec);
	lambert = dot_vect(yo, vec);
	lambert = lambert < EPSI ? 0 : lambert;
	return (lambert);
}

void	trace(t_env *env, int x, int y)
{
	t_obj	*node;

	env->d = 20000.0;
	create_ray(env, x , y);
	node = env->obj;
	while (node != NULL)
	{
		if (node->type == 1)
			if (ft_sphere(node, env) == 1)
				ft_put_pixel(env, x, y, lambert_rgb(255,0,0, calc_lamb(env, node->pos)));
		node = node->next;
	}
}

int	draw(t_env	*env)
{
	int		x;
	int		y;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
		trace(env, x, y);
		x++;
		}
		y++;
	}
   	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
   	return (0);
}
