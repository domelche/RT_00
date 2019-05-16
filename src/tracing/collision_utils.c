
#include "rt.h"

int			ft_inside_type(t_list **objs, t_vector point)
{
	int			res;
	t_list		*node;
	t_object	*o;

	res = 0;
	node = *objs;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o, point))
		{
			if (o->is_neg)
				return (-1);
			res = 1;
		}
		node = node->next;
	}
	return (res);
}

t_object	*ft_get_inner_object(t_list **objs, t_vector point)
{
	t_list		*node;
	t_vector	od[2];
	float		dist[2];
	t_object	*o[2];
	t_coll		coll;

	node = *objs;
	od[0] = point;
	od[1] = (t_vector) { 1.0f, 0.0f, 0.0f };
	dist[0] = FLT_MAX;
	o[1] = NULL;
	while (node)
	{
		o[0] = (t_object *)(node->content);
		o[0]->ft_collide(objs, o[0], &coll, od);
		dist[1] = ft_3_point_point_dist(point, coll.coll_pnt);
		if (dist[1] < dist[0])
		{
			dist[0] = dist[1];
			o[1] = o[0];
		}
		node = node->next;
	}
	return (o[1]);
}

static void	ft_free_list(t_list **head)
{
	t_list	*node;
	t_list	*prev;

	node = *head;
	while (node)
	{
		prev = node;
		node = node->next;
		free(prev);
	}
}

t_object	*ft_inside_obj(
				t_list **objs,
				t_vector point,
				t_object *(*ft_choose)(t_list **objs, t_vector point))
{
	t_list		*res_objs;
	t_list		*node;
	t_object	*o;
	t_object	*res;
	int 		len;
	static int	count = 0;

	res_objs = NULL;
	node = *objs;
	len = 0;
	while (node)
	{
		o = (t_object *)(node->content);
		if (o->ft_is_inside(o, point))
		{
			ft_lstpush(&res_objs, ft_nodenew((void *)o, sizeof(t_object)));
			++len;
		}
		node = node->next;
	}
	res = (len == 0) ? NULL : (t_object *)(res_objs->content);
	if (len > 1)
		res = ft_choose(&res_objs, point);
	ft_free_list(&res_objs);
	return (res);
}

void		ft_choose_object(t_list **objs, t_object *obj, t_coll *coll)
{
	if (obj->is_neg)
	{
//		coll->coll_pnt += ft_3_vector_scale(
//			coll->norm, (coll->norm[3] != 1) ? -SHIFT : SHIFT);
		coll->o = ft_inside_obj(objs, coll->coll_pnt, ft_get_inner_object);
		coll->coll_pnt -= ft_3_vector_scale(coll->norm, SHIFT);
		coll->o->ft_procedural = ft_procedural_sph;
		coll->o->ft_checker = ft_checker_sph;
		coll->o->ft_mapping = ft_map_sphere;
	}
	else
		coll->o = obj;
}
