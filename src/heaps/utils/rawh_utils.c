/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawh_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:08:51 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 15:32:06 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heaps/fheaps.h"

void	*raw_alloc(void *heap, f_size size)
{
	void	*ptr;

	return (ptr);
}

void	raw_free(void *heap, void *ptr)
{

}

void	raw_free_heap(void *heap)
{

}

static const heap_vtbl g_raw_vtable = {
	.free_heap = raw_free_heap,
	.alloc = raw_alloc,
	.free = raw_free,
};

const heap_vtbl	*get_raw_vtable(void)
{
	return &g_raw_vtable;
}
