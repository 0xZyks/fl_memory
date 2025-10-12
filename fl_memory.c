#include "fl_memory.h"
#include "prototypes.h"
#include <stdio.h>

fl_central	*fl_get_central(void)
{
	static fl_central	central;
	static int			initialized = 0;

	if (!initialized)
	{
		for (unsigned long i = 0; i < MAX_HEAP_COUNT; i++)
		{
			central.HEAPS[i].initialized = 0;
			central.HEAPS[i].end_splitter = '\0';
		}
		initialized = 1;
	}

	return (&central);
}

fl_memory	*get_fl_mem(int id)
{
	if (id > MAX_HEAP_COUNT || id < 0)
		return ((void *)0);

	fl_central	*central = fl_get_central();
	fl_memory	*memory = &central->HEAPS[id];

	if (!memory->initialized)
		memory->initialized = 1;

	return (memory);
}

fl_mem_page	*get_fl_page(fl_memory *mem, int id)
{
	if (id < 0 || id > PAGE_COUNT)
		return ((void *)0);

	fl_mem_page	*page = &mem->PAGE[id];

	if (!page->initialized)
	{
		page->initialized = 1;
		page->id = id;
		page->size = 0;
		page->curr_capacity = PAGE_SIZE;
		page->last_offset = 0;
		page->completion = PAGE_COMPLETION(page->size, PAGE_SIZE);
		page->end_splitter = mem->end_splitter;
		page->is_free = 1;
		page->free_count = 0;
	}

	return (&mem->PAGE[id]);
}

fl_mem_page	*get_alloc_page(fl_memory *mem, int size)
{
	if (size <= 0 || size > PAGE_SIZE)
		return ((void *)0);

	for (int i = 0; i < PAGE_COUNT; i++)
	{
		fl_mem_page	*target = get_fl_page(mem, i);
		if (target->initialized && target->curr_capacity > (size + target->size))
			return (&mem->PAGE[i]);
	}

	return ((void *)0);
}

void	fl_insert_free_block(fl_mem_page *page, fl_free_block block)
{
    if ((unsigned long long)page->free_count >= MAX_FREE_COUNT)
        return;

    int	pos = 0;
    while (pos < page->free_count && page->free_blocks[pos].offset < block.offset)
        pos++;

    if (pos < page->free_count) {
        fl_memmove((unsigned char *)&page->free_blocks[pos + 1],
                (unsigned char *)&page->free_blocks[pos],
                (page->free_count - pos) * sizeof(fl_free_block));
    }

    page->free_blocks[pos] = block;
    page->free_count++;

    int i = 0, write = 0;
    while (i < page->free_count) {
        if (write > 0 && page->free_blocks[write - 1].offset + page->free_blocks[write - 1].size == page->free_blocks[i].offset)
            page->free_blocks[write - 1].size += page->free_blocks[i].size;
        else
            page->free_blocks[write++] = page->free_blocks[i];
        i++;
    }
    page->free_count = write;
}

void		*fl_raw_alloc(int size, fl_mem_page *page)
{
	if (page->last_offset + size >= PAGE_SIZE)
		return ((void *)0);

	int			free_index = -1;
	void		*ptr = ((void *)0);
	
	while (++free_index < page->free_count)
	{
		fl_free_block *block = &page->free_blocks[free_index];
		if (size <= block->size)
		{
			ptr = &page->DATA[block->offset];
			if (block->size > size)
			{
				block->size -= size;
				block->offset += size + 1;
			}
			else
			{
				int rem = free_index - 1;
				while (++rem < page->free_count - 1)
					page->free_blocks[rem] = page->free_blocks[rem - 1];
                page->free_count--;
			}
			break;
		}
	}

	if (!ptr)
	{
		size++;
		ptr = &page->DATA[page->last_offset];
		page->size += size;
		page->last_offset += size;
		page->completion = PAGE_COMPLETION(page->size, PAGE_SIZE);
		page->curr_capacity = PAGE_SIZE - page->size;
	}

	page->DATA[page->last_offset] = page->end_splitter;
	page->is_free = 0;

	return (ptr);
}

fl_pointer	*fl_ptr_alloc(int size, fl_mem_page *page)
{
	if (page->last_offset + size >= PAGE_SIZE)
		return ((void *)0);

	fl_pointer	*fl_ptr;

	fl_ptr = (fl_pointer *)&page->DATA[page->last_offset];
	if (fl_ptr->initialized)
		return (fl_ptr);
	fl_ptr->initialized = 1;
	page->size += size;
	page->last_offset += (size);
	page->DATA[page->last_offset] = page->end_splitter;
	page->completion = PAGE_COMPLETION(page->size, PAGE_SIZE);
	page->curr_capacity = PAGE_SIZE - page->size;
	page->is_free = 0;

	return (fl_ptr);
}

void	*fl_malloc(int size)
{
	void		*raw_ptr;
	fl_pointer	*fl_ptr;
	fl_memory	*raw_mem = get_fl_mem(FL_RAW);
	fl_memory	*ptr_mem = get_fl_mem(FL_PTR);
	fl_mem_page	*raw_paging = get_alloc_page(raw_mem, size);
	fl_mem_page	*ptr_paging = get_alloc_page(ptr_mem, sizeof(fl_pointer));

	if (!raw_paging || !ptr_paging)
		return ((void *)0);

	raw_ptr = fl_raw_alloc(size, raw_paging);
	fl_ptr = fl_ptr_alloc(sizeof(fl_pointer), ptr_paging);

	fl_ptr->raw_page_id = raw_paging->id;
	fl_ptr->curr_page_id = ptr_paging->id;
	fl_ptr->data = raw_ptr;
	fl_ptr->offset = raw_paging->last_offset - (size + 1);
	fl_ptr->size = size;

	return (raw_ptr);
}

void	fl_memmove(unsigned char *dst, unsigned char *src, int len)
{
	int	i = -1;

	if (dst < src)
		while (++i < len)
			dst[i] = src[i];
	else
	{
		i = len - 1;
		while (i-- >= 0)
			dst[i] = src[i];
	}
}

fl_pointer	*get_fl_ptr(void *ptr)
{
	if (!ptr)
		return ((void *)0);

	int			offset;
	fl_pointer	*p;
	fl_memory	*mem = get_fl_mem(FL_PTR);
	fl_mem_page	*curr_page;

	for (int i = 0; i < PAGE_COUNT; i++)
	{
		offset = 0;
		curr_page = &mem->PAGE[i];
		while (offset <= curr_page->last_offset)
		{
			p = (fl_pointer *)&curr_page->DATA[offset];
			if (p->data == ptr)
				return (p);
			offset += (int)sizeof(fl_pointer);
		}
	}

	return ((void *)0);
}

void	fl_memset(void* ptr, char data, int size)
{
	int		index = -1;
	char	*src = (char *)ptr;
	while (++index < size)
		src[index] = data;
}

void	fl_free(void *ptr)
{
	//int				offset = 0;
	fl_memory		*raw_mem = get_fl_mem(FL_RAW);
	//fl_memory		*ptr_mem = get_fl_mem(FL_PTR);
	fl_pointer		*fl_ptr = get_fl_ptr(ptr);
	fl_free_block	block;

	if (!fl_ptr) return;
	
	fl_mem_page	*raw_page = get_fl_page(raw_mem, fl_ptr->raw_page_id);
	//fl_mem_page	*ptr_page = get_fl_page(ptr_mem, fl_ptr->curr_page_id);

	fl_memset(ptr, '\0', fl_ptr->size);
	ptr = ((void *)0);
	block.size = fl_ptr->size + 1;
	block.offset = fl_ptr->offset;
	block.page_id = raw_page->id;
	fl_insert_free_block(raw_page, block);

	fl_ptr->initialized = 0;
	fl_ptr->data = (char *)((void *)0);
	fl_ptr->size = 0;
	fl_ptr->offset = 0;
}

void	*fl_realloc(void *ptr, int newsize)
{
    if (newsize <= 0) {
        if (ptr) fl_free(ptr);
        return NULL;
    }
    if (!ptr)
        return fl_malloc(newsize);

    fl_pointer	*p = get_fl_ptr(ptr);
    if (!p || !p->initialized)
        return NULL;

    fl_memory	*raw_mem = get_fl_mem(FL_RAW);
    fl_mem_page	*raw_page = get_fl_page(raw_mem, p->raw_page_id);

    if (newsize <= p->size) {
        int		leftover = p->size - newsize;
        if (leftover > 0) {
            fl_free_block block;
            block.offset = p->offset + newsize + 1;
            block.size = leftover;
            block.page_id = raw_page->id;
            fl_insert_free_block(raw_page, block);
        }
        p->size = newsize;
        return p->data;
    }

    for (int i = 0; i < raw_page->free_count; i++) {
        fl_free_block	*fb = &raw_page->free_blocks[i];
        if (fb->offset == p->offset + p->size + 1) {
            int total = p->size + fb->size;
            if (total >= newsize) {
                int consume = newsize - p->size;
                fb->offset += consume;
                fb->size -= consume;
                p->size = newsize;
                return p->data;
            }
        }
    }

    void	*new_raw = fl_raw_alloc(newsize, raw_page);
    if (!new_raw) {
        fl_mem_page	*alt = get_alloc_page(raw_mem, newsize);
        if (!alt) return NULL;
        new_raw = fl_raw_alloc(newsize, alt);
        p->raw_page_id = alt->id;
        raw_page = alt;
    }

    fl_memmove((unsigned char*)new_raw, (unsigned char*)p->data, p->size);
    p->data = new_raw;
    p->offset = raw_page->last_offset - (newsize + 1); /* align with your system */
    p->size = newsize;

    return p->data;
}

void	str_to_ptr(char *ptr, char *str, int size)
{
	int	offset = -1;

	while (++offset < size)
		ptr[offset] = str[offset];
	ptr[offset] = '\0';
}

#include <stdlib.h>
#include <string.h>
#include <time.h>

/* --- helpers debug --- */

void print_free_list(fl_mem_page *page) {
    printf("  [Page %d] free_count=%d, curr_capacity=%d\n",
           page->id, page->free_count, page->curr_capacity);
    for (int i = 0; i < page->free_count; i++) {
        printf("    free_block[%d] offset=%d size=%d (addr=%p)\n",
               i,
               page->free_blocks[i].offset,
               page->free_blocks[i].size,
               (void*)&page->DATA[page->free_blocks[i].offset]);
    }
}

void print_block_extended(const char *label, char *ptr, int size) {
    fl_pointer *p = get_fl_ptr(ptr);
    if (!ptr || !p) {
        printf("%s = NULL\n", label);
        return;
    }
    printf("%s = '%.*s' (addr=%p, size=%d, page_id=%d, offset=%d)\n",
           label, size, ptr, (void*)ptr, size, p->raw_page_id, p->offset);

    /* afficher free-list de la page associée */
    fl_memory *raw_mem = get_fl_mem(FL_RAW);
    fl_mem_page *page = get_fl_page(raw_mem, p->raw_page_id);
    print_free_list(page);
}

/* --- stress test --- */

int main(void) {
    printf("=== Fluid.Memory 10K Stress Test ===\n");
    srand((unsigned int)time(NULL));

    const int N = 120000;
    const int MAX_TRACK = 512;
    char *ptrs[MAX_TRACK];
    int sizes[MAX_TRACK];

    memset(ptrs, 0, sizeof(ptrs));

    clock_t start = clock();   /* start chrono */

    for (int i = 0; i < N; i++) {
        int action = rand() % 3; /* 0=malloc, 1=free, 2=realloc */
        int idx = rand() % MAX_TRACK;

        if (action == 0) { /* malloc */
            if (!ptrs[idx]) {
                int sz = (rand() % 128) + 4; /* entre 4 et 132 bytes */
                ptrs[idx] = fl_malloc(sz);
                sizes[idx] = sz;
                if (ptrs[idx]) {
                    memset(ptrs[idx], 'A' + (idx % 26), sz - 1);
                    ptrs[idx][sz - 1] = '\0';
                    if (i % 1000 == 0) {
                        //printf("\n[Step %d] malloc idx=%d size=%d\n", i, idx, sz);
                        //print_block_extended("ALLOC", ptrs[idx], sz);
                    }
                }
            }
        }
        else if (action == 1) { /* free */
            if (ptrs[idx]) {
                if (i % 1000 == 0) {
                    //printf("\n[Step %d] free idx=%d size=%d\n", i, idx, sizes[idx]);
                    //print_block_extended("FREE_BEFORE", ptrs[idx], sizes[idx]);
                }
                fl_free(ptrs[idx]);
                ptrs[idx] = NULL;
            }
        }
        else { /* realloc */
            if (ptrs[idx]) {
                int newsize = (rand() % 128) + 4;
                if (i % 1000 == 0) {
                    //printf("\n[Step %d] realloc idx=%d old=%d new=%d\n", i, idx, sizes[idx], newsize);
                    //print_block_extended("REALLOC_BEFORE", ptrs[idx], sizes[idx]);
                }
                ptrs[idx] = fl_realloc(ptrs[idx], newsize);
                if (ptrs[idx]) {
                    sizes[idx] = newsize;
                    memset(ptrs[idx], 'a' + (idx % 26), newsize - 1);
                    ptrs[idx][newsize - 1] = '\0';
                    if (i % 1000 == 0) {
                        //print_block_extended("REALLOC_AFTER", ptrs[idx], sizes[idx]);
                    }
                }
            }
        }
    }

    clock_t end = clock();     /* end chrono */
    double elapsed_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    /* final dump of first few non-null */
    printf("\n=== Final state dump ===\n");
    for (int i = 0; i < MAX_TRACK; i++) {
        if (ptrs[i]) {
            //print_block_extended("FINAL", ptrs[i], sizes[i]);
        }
    }

    printf("\n=== Stress test done ===\n");
    printf("Total time: %.3f ms for %d operations\n", elapsed_ms, N);

    return 0;
}
