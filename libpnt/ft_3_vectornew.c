/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3_vectornew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domelche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 11:38:00 by domelche          #+#    #+#             */
/*   Updated: 2018/09/19 11:38:12 by domelche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpnt.h"

t_vector		ft_3_vectornew(t_vector origin, t_vector direct)
{
	return (ft_3_pointnew(
		direct.x - origin.x, direct.y - origin.y, direct.z - origin.z));
}
