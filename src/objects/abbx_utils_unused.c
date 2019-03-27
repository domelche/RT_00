/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abbx_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:46:28 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/19 15:46:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	bbx_area(t_vector d)
{
	return (2.0f * (d[0] * d[1] + d[0] * d[2] + d[1] * d[2]));
}

float	bbx_volume(t_vector d)
{
	return (d[0] * d[1] * d[2]);
}