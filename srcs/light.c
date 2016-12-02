/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:16:04 by pmartine          #+#    #+#             */
/*   Updated: 2016/12/02 18:40:03 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double      min_max(double numb, double min, double max)
{
	if (numb < min)
		numb = min;
	if (numb > max)
		numb = max;
	return (numb);
}

/*double	calc_spec(t_env *env, t_obj *obj)
{
	float	spec;
	float	tmp;
	t_vec	ref;

	spec = 0.0;
	ref = scale_vect(&mlx->norm, (2.0 * ft_vectordot(env->norm, dist)));
	ref = sub_vect(dist, ref);
	if ((tmp = dot_vect(ref, env->ray_dir)) > 0.0)
	{
		spec = pow(tmp, 30.0) * 1.0;
		spec = min_max(spec, 0.0, 1.0);
	}
	return (spec);
}
*/
double   calc_lamb(t_env *env, t_obj *obj)
{
	t_vec   dist;
	t_vec   cam;
	t_vec   norm;
	double  lambert;

	cam = add_vect(env->ray_pos, scale_vect(env->ray_dir, env->d));
	norm = normale(obj ,env ,cam);
	dist = sub_vect(env->spots->pos, cam);
	dist = norm_vect(dist);
	lambert = 0;
	lambert += dot_vect(dist, norm) * 0.9;
	lambert = min_max(lambert, 0.15, 1.0) ;
	return (lambert);
}