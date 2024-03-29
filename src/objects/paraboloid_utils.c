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

static int		ft_solve_sqr_(double a, double b, double c, double res[2])
{
	double d;

	res[0] = FLT_MAX;
	res[1] = FLT_MAX;
	if (IS_ZERO(a))
	{
		res[0] = -c / b;
		res[1] = res[0];
		return (1);
	}
	d = pow(b, 2) - 4.0f * a * c;
	if (d < 0)
		return (0);
	d = sqrt(d);
	res[0] = (float)((-b + d) / (2.0f * a));
	res[1] = (float)((-b - d) / (2.0f * a));
	if ((res[0] > res[1] && res[1] >= 0) || res[0] <= 0)
		ft_swap(&res[0], &res[1], sizeof(double));
	return (1);
}

static float	get_closer_pnt(
					const double *t, const t_vector *hit,
					t_coll *coll, t_object *obj)
{
	coll->o = obj;
	coll->tex_o = obj;
	if ((t[0] < t[1] || t[1] <= 0) && t[0] >= 0 && t[0] != FLT_MAX)
	{
		//printf("cides\n");
		coll->ucoll_pnt = hit[0];
		coll->norm = ft_3_tounitvector(
			ft_3_norm_transform(
				&(obj->inverse),
				coll->ucoll_pnt - ((t_vector){0, coll->ucoll_pnt[1] + 1, 0})));

		//if (coll->norm[1] < 0) ft_3_vector_print("norm: ", coll->norm);

		return ((float)t[0]);
	}
	if (t[1] >= 0 && t[0] != FLT_MAX)
	{
		//printf("caps\n");
		coll->ucoll_pnt = hit[1];
		coll->norm = ft_3_tounitvector(
			ft_3_norm_transform(&(obj->inverse), (t_vector) {0, -1, 0}));
		return ((float)t[1]);
	}
	return (FLT_MAX);
}

static float	get_caps_coll(t_vector od[2], t_vector *coll, t_prbld *par)
{
	float		t;
	t_vector 	o;

	od[0][1] -= par->maxh;
	t = par->maxh == FLT_MAX ? FLT_MAX : -(od[0][1]) / od[1][1];
	if (t < 0 || t == FLT_MAX)
		return (FLT_MAX);
	*coll = od[0] + ft_3_vector_scale(od[1], t);
//	if (ft_3_vector_dot(*coll, *coll) > par->r * par->r)
	if (ft_3_vector_dot(*coll, *coll) > 4.0f * par->maxh)
	{
		*coll = ft_3_nullpointnew();
		return (FLT_MAX);
	}
	return (t);
}

int				ft_is_reachable_prbld(
					void *fig, t_vector origin, t_vector direct)
{
	(void)origin;
	(void)direct;
	(void)fig;
	return (1);
}

static double	get_cides_coll(
					t_vector od[2], double *t, t_vector *coll, t_prbld *par)
{
	t_vector	hit[2];
	float 		m[2];

	hit[0] = od[0] + ft_3_vector_scale(od[1], t[0]);
	hit[1] = od[0] + ft_3_vector_scale(od[1], t[1]);
	if (t[0] >= 0 && IN_RANGE(hit[0][1], 0, par->maxh))
	{
		*coll = hit[0];
		return (t[0]);
	}
	else if (t[1] >= 0 && IN_RANGE(hit[1][1], 0, par->maxh))
	{
		*coll = hit[1];
		return (t[1]);
	}
	return (FLT_MAX);
}

float			ft_collide_prbld(
					t_list **objs, struct s_object *obj,
					t_coll *coll, t_vector untr_od[2])
{
	t_prbld		*par;
	t_vector	hit[2];
	double		res[2];
	t_vector	od[2];
//	float 		k;

	par = (t_prbld *)obj->fig;
	od[0] = ft_3_pnt_transform(&(obj->inverse), untr_od[0]);
	od[1] = ft_3_vec_transform(&(obj->inverse), untr_od[1]);
//	k = par->maxh / (par->r * par->r);
//	if (!ft_solve_sqr_(k * (od[1][0] * od[1][0] + od[1][2] * od[1][2]),
//		2.0f * k * (od[1][0] * od[0][0] + od[1][2] * od[0][2]) - od[1][1],
//		k * (od[0][0] * od[0][0] + od[0][2] * od[0][2]) - od[0][1],
//		&res) || (res[0] < FLT_MIN && res[1] < FLT_MIN))
//	printf(" ori %f,%f,%f, od %f,%f,%f\n", od[0][0], od[0][1], od[0][2],
//			od[1][0], od[1][1], od[1][2]);
	if ((!ft_solve_sqr_(
		ft_3_vector_dot(od[1], od[1]) - od[1][1] * od[1][1],
		2.0f * (ft_3_vector_dot(od[1], od[0]) - od[1][1] * (od[0][1] + 2.f)),
		ft_3_vector_dot(od[0], od[0]) - od[0][1] * (od[0][1] + 4.f),
		res) || (res[0] <= 0 && res[1] <= 0))
		&& (IS_ZERO(od[1][1]) || par->maxh == FLT_MAX))
		return (FLT_MAX);
	res[0] = get_cides_coll(od, res, &hit[0], par);
	res[1] = get_caps_coll(od, &hit[1], par);

	return (get_closer_pnt(res, hit, coll, obj));
}

int			ft_is_inside_prbld(t_object *o, t_vector point)
{
	t_prbld		*par;
	t_vector	r;

	par = (t_prbld *)o->fig;
	point = ft_3_pnt_transform(&(o->inverse), point);
	if (!IN_RANGE(point[1], -(1e-2), par->maxh) && par->maxh != FLT_MAX)
	{
//		printf("OUTSIDE HEI\n");
		return (0);
	}
//	r = point - Y_AXIS;
	r = (t_vector){point[0], point[1] - 1, point[2]};
//	if (ft_3_vector_dot(r, r) <= (point[1] + 1) * (point[1] + 1))
//		printf("INSIDE\n");
//	else
//		printf("OUTSIDE\n");
	return (ft_3_vector_dot(r, r) <= (point[1] + 1) * (point[1] + 1) ? 1 : 0);
}

t_vector	ft_get_norm_prbld(void *fig, t_vector coll)
{
//	t_prbld		*par;
//	float 		h;
//
//	par = (t_prbld *)fig;
//	h = ft_3_vector_dot(par->v, coll - par->o);
//	if (h >= par->maxh - 1e-2)
//		return(ft_3_tounitvector(par->v));
//	else
//		return (ft_3_tounitvector(coll - (par->o + ft_3_vector_scale(par->v, h + par->r))));
	return (ft_3_nullpointnew());
}
