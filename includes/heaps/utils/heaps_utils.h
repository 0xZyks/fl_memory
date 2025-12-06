/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heaps_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsignori <tsignori@student.42perpignan.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 15:33:54 by tsignori          #+#    #+#             */
/*   Updated: 2025/12/06 16:53:29 by tsignori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAPS_UTILS_PROTOTYPES_H
# define HEAPS_UTILS_PROTOTYPES_H

# include "../fheaps.h"


const heap_vtbl	*get_raw_vtabl(void);
const heap_vtbl	*get_ptr_vtabl(void);
const heap_vtbl	*get_t04_vtabl(void);
const heap_vtbl	*get_t08_vtabl(void);
const heap_vtbl	*get_t16_vtabl(void);
const heap_vtbl	*get_t24_vtabl(void);
const heap_vtbl	*get_t32_vtabl(void);
const heap_vtbl	*get_t64_vtabl(void);

#endif // !HEAPS_UTILS_PROTOTYPES_H
