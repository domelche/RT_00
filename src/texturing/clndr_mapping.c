/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clndr_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:59:36 by vbespalk          #+#    #+#             */
/*   Updated: 2019/05/10 17:31:18 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static Uint32	ft_map_caps(t_cylinder *clnd, SDL_Surface *tex,
		t_vector hit, float hei)
{
	return (UINT32_MAX);
}

Uint32			ft_map_clndr(t_object *o, SDL_Surface *tex, t_vector hit)
{
	Uint32		col;
	float		hei;
	float		phi;
	int			xy[2];
	t_cylinder	*clnd;

	clnd = ((t_cylinder *)o->fig);
	if (((t_cylinder *)o->fig)->maxh == FLT_MAX)
		return (o->color.val);
	if (!IN_RANGE(hit[1], -clnd->maxh + 1e-4, clnd->maxh - 1e-4))
		return (ft_map_caps(((t_cylinder *)o->fig), tex, hit, hei));
	hei = (hit[1] + clnd->maxh) / 2.0f;
	phi = atan2f(hit[0], hit[2]);
	if (!(IN_RANGE(phi, 0.0f, 2 * M_PI)))
		phi = phi < 0 ? phi + 2 * (float)M_PI : phi;
	xy[0] = (int)((tex->w - 1) * phi * 0.5f * (float)M_1_PI);
	xy[1] = (int)((tex->h - 1) * (1.0f - hei / ((t_cylinder *)o->fig)->maxh));
	if (!(IN_RANGE(xy[0], 0, tex->w) && IN_RANGE(xy[1], 0, tex->h)))
		return (0xff);
	ft_memcpy(&col, (Uint32 *)tex->pixels + xy[1] * tex->w
					+ xy[0], sizeof(Uint32));
	return (col);
}

Uint32			ft_checker_cyl(t_object *o, t_checkbrd *tex, t_vector coll)
{
	float		uv[2];
	t_cylinder	*clnd;
	float		phi;

	clnd = (t_cylinder *)o->fig;
	phi = atan2f(coll[2], coll[0]);
	if (!(IN_RANGE(phi, 0.0f, 2.0f * M_PI)))
		phi = phi < 0.0f ? phi + 2 * (float)M_PI : phi - 2 * (float)M_PI;
	uv[0] = (1 + phi / (float)M_PI);
	if (!IN_RANGE(coll[1], -clnd->maxh + 1e-4, clnd->maxh - 1e-4)
		&& clnd->maxh != FLT_MAX)
		uv[1] = sqrtf(coll[2] * coll[2] + coll[0] * coll[0]);
	else
		uv[1] = clnd->maxh == FLT_MAX ? (coll[1] + 100) * 0.3f :
			(coll[1] / clnd->maxh + 100) * 0.3f;
	if (!((fmodf(uv[0] * tex->size, 1) > 0.5) ^
			(fmodf(uv[1] * tex->size, 1) > 0.5)))
		return (tex->noise[0] ? o->ft_procedural(o, tex->noise[0], coll) :
			tex->color[0]);
		return (tex->noise[1] ? o->ft_procedural(o, tex->noise[1], coll) :
			tex->color[1]);
}

Uint32			ft_procedural_cyl(t_object *o, t_procedural *tex, t_vector coll)
{
	t_cylinder	*cyl;
	t_vector	point;

	cyl = (t_cylinder *)o->fig;
	point = coll;
	point[1] = cyl->maxh == FLT_MAX ? coll[1] : coll[1] / cyl->maxh;
	return (tex->ft_get_color(tex, NULL, ft_3_vector_scale(point, tex->scale)));
}
