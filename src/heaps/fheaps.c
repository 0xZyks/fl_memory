/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fheaps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:54:15 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 15:32:08 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/heaps/fheaps.h"

fl_central	*get_central(void)
{
	static fl_central	central;
	return (&central);
}

fheap	*get_heap(int id)
{
	fl_central	*central = get_central();
	fheap		*heap = &central->heaps[id];

	if (!central->init[id])
	{
		central->init[id] = 1;
		heap->id = id;
		if (id == RAW_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 64);
		if (id == PTR_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 4);
		if (id == T04_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 4);
		if (id == T08_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 8);
		if (id == T16_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 16);
		if (id == T24_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 24);
		if (id == T32_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 32);
		if (id == T64_HEAP)
			heap->base = central->os.reserve(1024 * 1024 * 64);
	}
	return (heap);
}

void	set_vtable(fheap *heap)
{
	if (heap->id == RAW_HEAP)
		get_raw_vtable();
	if (heap->id == PTR_HEAP)
		get_ptr_vtable();
	if (heap->id == T04_HEAP)
		get_t04_vtable();
	if (heap->id == T08_HEAP)
		get_t08_vtable();
	if (heap->id == T16_HEAP)
		get_t16_vtable();
	if (heap->id == T24_HEAP)
		get_t24_vtable();
	if (heap->id == T32_HEAP)
		get_t32_vtable();
	if (heap->id == T64_HEAP)
		get_t64_vtable();
}
