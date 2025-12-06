/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrh_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:39:04 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 16:43:33 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/heaps/fheaps.h"

void	*ptr_alloc(void *heap, f_size size)
{
	void	*ptr;

	return (ptr);
}

void	ptr_free(void *heap, void *ptr)
{

}

void	ptr_free_heap(void *heap)
{

}

static const heap_vtbl g_ptr_vtable = {
	.free_heap = ptr_free_heap,
	.alloc = ptr_alloc,
	.free = ptr_free,
};

const heap_vtbl	*get_ptr_vtable(void)
{
	return &g_ptr_vtable;
}

