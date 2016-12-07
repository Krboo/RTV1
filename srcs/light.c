/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:16:04 by pmartine          #+#    #+#             */
/*   Updated: 2016/12/07 08:16:24 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		min_max(double numb, double min, double max)
{
	if (numb < min)
		numb = min;
	if (numb > max)
		numb = max;
	return (numb);
}

double		shadow(t_env *e, t_obj *obj, t_vec cam)
{
	t_obj		*node;
	double		dis;
	t_vec		dir;
	t_vec		st;
	t_vec		sto;
	double		yo;

	yo = e->d;
	dir = sub_vect(e->spots->pos, cam);
	e->d = sqrtf(dot_vect(dir, dir));
	dir = norm_vect(dir);
	node = e->obj;
	st = e->cam_pos;
	sto = e->ray_dir;
	e->ray_dir = dir;
	e->cam_pos = cam;
	while (node != NULL)
	{
		if (obj != node)
		{
			if (node->type == 3)
				dis = ft_cylindre(node, e);
			if (node->type == 2)
				dis = ft_cone(node, e);
			if (node->type == 0)
				dis = ft_plan(node, e);
			if (node->type == 1)
				dis = ft_sphere(node, e);
			if (dis > EPSI && dis < e->d)
			{
				e->cam_pos = st;
				e->ray_dir = sto;
				e->d = yo;
				return (-0.15);
			}
		}
		node = node->next;
	}
	e->cam_pos = st;
	e->ray_dir = sto;
	e->d = yo;
	return (0);
}

double		calc_lamb(t_env *env, t_obj *obj)
{
	t_vec	dist;
	t_vec	cam;
	t_vec	norm;
	double	lambert;
	double	tmp;
	double	spec;
	t_vec	ref;

	cam = add_vect(env->cam_pos, scale_vect(env->ray_dir, env->d));
	norm = normale(obj, env, cam);
	dist = sub_vect(env->spots->pos, cam);
	dist = norm_vect(dist);
	lambert = 0.0;
	spec = 0.0;
	ref = scale_vect(norm, (2.0 * dot_vect(norm, dist)));
	ref = sub_vect(dist, ref);
	if ((tmp = dot_vect(ref, env->ray_dir)) > 0.0)
		spec = pow(tmp, 30.0);
	lambert += dot_vect(dist, norm);
	lambert = min_max(lambert, 0.15, 0.9);
	if (obj->type != 0 && spec > EPSI)
		lambert += spec;
	lambert += shadow(env, obj, cam);
	lambert = min_max(lambert, 0.15, 1.5);
	return (lambert);
}
