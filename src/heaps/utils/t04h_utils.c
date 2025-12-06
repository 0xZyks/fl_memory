/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t04h_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:39:14 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 16:43:27 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heaps/fheaps.h"

void	*t04_alloc(void *heap, f_size size)
{
	void	*ptr;

	return (ptr);
}

void	t04_free(void *heap, void *ptr)
{

}

void	t04_free_heap(void *heap)
{

}

static const heap_vtbl g_t04_vtable = {
	.free_heap = t04_free_heap,
	.alloc = t04_alloc,
	.free = t04_free,
};

const heap_vtbl	*get_t04_vtable(void)
{
	return &g_t04_vtable;
}

