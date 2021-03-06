/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 18:57:35 by pmartine          #+#    #+#             */
/*   Updated: 2015/12/01 13:38:51 by pmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	while ((int)*s1 == (int)*s2)
	{
		if (*s1 == '\0')
			return (1);
		s1++;
		s2++;
	}
	return (0);
}
