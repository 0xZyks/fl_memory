/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t24h_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:43:56 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 16:44:08 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heaps/fheaps.h"

void	*t24_alloc(void *heap, f_size size)
{
	void	*ptr;

	return (ptr);
}

void	t24_free(void *heap, void *ptr)
{

}

void	t24_free_heap(void *heap)
{

}

static const heap_vtbl g_t24_vtable = {
	.free_heap = t24_free_heap,
	.alloc = t24_alloc,
	.free = t24_free,
};

const heap_vtbl	*get_t24_vtable(void)
{
	return &g_t24_vtable;
}

