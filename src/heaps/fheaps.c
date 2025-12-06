/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fheaps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:54:15 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 14:02:52 by tsignori         ###   ########.fr       */
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
		if (id == RAW_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 64);
		}
		if (id == PTR_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 4);
		}
		if (id == T04_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 4);
		}
		if (id == T08_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 8);
		}
		if (id == T16_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 16);
		}
		if (id == T24_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 24);
		}
		if (id == T32_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 32);
		}
		if (id == T64_HEAP)
		{
			central->init[id] = 1;
			heap = central->os.reserve(1024 * 1024 * 64);
		}
	}
	return (heap);
}
