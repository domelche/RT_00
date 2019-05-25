/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:12:51 by vbespalk          #+#    #+#             */
/*   Updated: 2019/02/19 18:12:54 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ft_init_v(t_vector v[4][2], t_object *obj, t_vector uod[2])
{
	v[0][0] = ft_3_pnt_transform(&(obj->inverse), uod[0]);
	v[0][1] = ft_3_vec_transform(&(obj->inverse), uod[1]);
	v[1][0] = uod[0];
	v[1][1] = uod[1];
}

float			ft_collide_prbld(
					t_list **objs, struct s_object *obj,
					t_coll *coll, t_vector untr_od[2])
{
	int			i;
	t_vector	v[4][2];
	double		res[2];

	ft_init_v(v, obj, untr_od);
	if ((!ft_solve_sq(
		ft_3_vector_dot(v[0][1], v[0][1]) - v[0][1][1] * v[0][1][1],
		2.0f * (ft_3_vector_dot(
			v[0][1], v[0][0]) - v[0][1][1] * (v[0][0][1] + 2.f)),
		ft_3_vector_dot(v[0][0], v[0][0]) - v[0][0][1] * (v[0][0][1] + 4.f),
		res) || (res[0] <= 0 && res[1] <= 0))
		&& (IS_ZERO(v[0][1][1]) || ((t_prbld *)obj->fig)->maxh == FLT_MAX))
		return (FLT_MAX);
	res[0] = ft_get_prbld_cides_coll(objs, v, res, obj);
	res[1] = ft_get_prbld_caps_coll(objs, v, obj);
	if (res[0] == FLT_MAX && res[1] == FLT_MAX)
		return (FLT_MAX);
	i = (res[0] < res[1]) ? 0 : 1;
	coll->ucoll_pnt = v[2][i];
	coll->coll_pnt = untr_od[0] + ft_3_vector_scale(untr_od[1], (float)res[i]);
	if (obj->is_neg)
		coll->coll_pnt += ft_3_vector_scale(coll->norm, SHIFT);
	coll->norm = v[3][i];
	coll->tex_o = obj;
	res[i] < FLT_MAX ? ft_choose_object(objs, obj, coll) : 1;
	return ((float)res[i]);
}

int				ft_is_inside_prbld(t_object *o, t_vector point)
{
	t_prbld		*par;
	t_vector	r;

	par = (t_prbld *)o->fig;
	point = ft_3_pnt_transform(&(o->inverse), point);
	if (!IN_RANGE(point[1], -SHIFT, par->maxh) && par->maxh != FLT_MAX)
		return (0);
	r = (t_vector){point[0], point[1] - 1, point[2]};
	return (ft_3_vector_dot(r, r) <= (point[1] + 1) * (point[1] + 1) ? 1 : 0);
}

t_vector		ft_get_norm_prbld(void *fig, t_matrix *inv_m, t_vector coll)
{
	(void)fig;
	return (ft_3_tounitvector(ft_3_norm_transform(inv_m,
		ft_3_tounitvector(coll - ((t_vector){0, coll[1] + 2, 0})))));
}
