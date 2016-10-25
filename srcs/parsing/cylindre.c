/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:50:13 by qduperon          #+#    #+#             */
/*   Updated: 2016/10/25 12:01:37 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

t_obj		*ft_get_cylind(int fd, t_vec rot)
{
	char	*line;
	double	radius;
	int		ret;
	t_color	color;
	t_vec	pos;

	while ((ret = get_next_line(fd, &line)) > 0 && ft_strcmp(line, "-------"))
	{
		if (ft_strstr(line, "pos:"))
			pos = ft_vector(fd);
		if (ft_strstr(line, "radius:"))
		{
			ret = get_next_line(fd, &line);
			radius = ft_atodouble(&line);
		}
		if (ft_strstr(line, "color:"))
			color = ft_color(fd);
		if (ft_strstr(line, "rot:"))
			rot = ft_vector(fd);
	}
	if (ret == -1)
		exit(-1);
	return (ft_new_obj4(radius, pos, rot, color));
}

t_obj		*ft_get_cylinds(int fd)
{
	char		*line;
	int			ret;
	t_obj		*obj;
	t_vec		rot;

	obj = NULL;
	rot = new_vec(0.0,0.0,0.0);
	while ((ret = get_next_line(fd, &line)) > 0 && ft_strcmp("-------", line))
	{
		if (ft_strstr(line, "new:"))
		{
			if (obj == NULL)
				obj = ft_get_cylind(fd, rot);
			else
				ft_add_obj(obj, ft_get_cylind(fd, rot));
		}
		if (ret == -1)
			exit(-1);
	}
	return (obj);
}
