/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fheaps.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:49:53 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 14:19:14 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FHEAPS_H
# define FHEAPS_H

# define MAX_HEAP_COUNT (8)

# include "../types/fl_types.h"
# include "../sys/fsystem.h"

typedef enum e_fheap_id {
	RAW_HEAP = 0,
	PTR_HEAP = 1,
	T04_HEAP = 2,
	T08_HEAP = 3,
	T16_HEAP = 4,
	T24_HEAP = 5,
	T32_HEAP = 6,
	T64_HEAP = 7,
} fheap_id;

typedef struct s_heap_vtable {
	void	*(*alloc)(void *heap, f_size size);
	void	(*free)(void *heap, void *ptr);
	void	(*free_heap)(void *heap);
} heap_vtbl;

typedef struct s_fheap {
	heap_vtbl	*vptr;
	void		*base;
	f_size		capacity;
	f_size		offset;
	int			id;
} fheap;

typedef struct s_fl_central {
	fl_os_mem	os;
	fheap		heaps[MAX_HEAP_COUNT];
	int			init[MAX_HEAP_COUNT];
} fl_central;
#endif // !FHEAPS_H
