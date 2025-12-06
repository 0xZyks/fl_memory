/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heaps_utils_prototypes.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:33:54 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 16:36:26 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAPS_UTILS_H
# define HEAPS_UTILS_H

# include "../fheaps.h"

const heap_vtbl	*get_raw_vtable(void);
const heap_vtbl	*get_ptr_vtable(void);
const heap_vtbl	*get_t04_vtable(void);
const heap_vtbl	*get_t08_vtable(void);
const heap_vtbl	*get_t16_vtable(void);
const heap_vtbl	*get_t24_vtable(void);
const heap_vtbl	*get_t32_vtable(void);
const heap_vtbl	*get_t64_vtable(void);

#endif // !HEAPS_UTILS_H
