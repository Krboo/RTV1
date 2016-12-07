/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 14:57:25 by pmartine          #+#    #+#             */
/*   Updated: 2016/12/07 08:30:13 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec		new_vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec		add_vect(t_vec v1, t_vec v2)
{
	t_vec	v3;

	v3.x = v1.x + v2.x;
	v3.y = v1.y + v2.y;
	v3.z = v1.z + v2.z;
	return (v3);
}

t_vec		ft_vector(char *line)
{
	double	x;
	double	y;
	double	z;

	x = ft_atodouble(&line);
	y = ft_atodouble(&line);
	z = ft_atodouble(&line);
	return (new_vec(x, y, z));
}

t_vec		sub_vect(t_vec v1, t_vec v2)
{
	t_vec	v3;

	v3.x = v1.x - v2.x;
	v3.y = v1.y - v2.y;
	v3.z = v1.z - v2.z;
	return (v3);
}

t_vec		scale_vect(t_vec v1, double fact)
{
	t_vec	v2;

	v2.x = v1.x * fact;
	v2.y = v1.y * fact;
	v2.z = v1.z * fact;
	return (v2);
}

double		dot_vect(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec		norm_vect(t_vec v)
{
	double	len;
	t_vec	vec;

	len = 1.0 / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	vec.x = v.x * len;
	vec.y = v.y * len;
	vec.z = v.z * len;
	return (vec);
}

t_vec	cross_vect(t_vec v1, t_vec v2)
{
	t_vec		result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
