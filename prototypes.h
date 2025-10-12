#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "fl_memory.h"

fl_central	*get_fl_central(void);
fl_memory	*get_fl_mem(int id);
fl_mem_page	*get_fl_page(fl_memory *mem, int id);
fl_mem_page	*get_alloc_page(fl_memory *mem, int size);
fl_pointer	*get_fl_ptr(void *ptr);
fl_pointer	*fl_ptr_alloc(int size, fl_mem_page *page);
void		*fl_raw_alloc(int size, fl_mem_page *page);
void		*fl_malloc(int size);
void		*fl_realloc(void *ptr, int newsize);
void		fl_memmove(unsigned char *dst, unsigned char *src, int len);
void		fl_free(void *ptr);
void		str_to_ptr(char *ptr, char *str, int size);

#endif
