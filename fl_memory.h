#ifndef FL_MEMORY_H
# define FL_MEMORY_H
# define PAGE_COUNT (64)
# define PAGE_SIZE (1024 * 1024 * 64 / PAGE_COUNT)
# define MAX_HEAP_COUNT (8)
# define PAGE_COMPLETION(size, capacity)  (100 * (size) / (capacity));
# define FL_NEW(type) ((type *)fl_malloc(sizeof(type)));

typedef enum e_fl_heap_id
{
	FL_RAW = 0,
	FL_PTR = 1
} fl_heap;

typedef struct	s_free_block 
{
	int	size;
	int	offset;
	int	page_id;
} fl_free_block;

# define MAX_FREE_COUNT (PAGE_SIZE / sizeof(fl_free_block))

typedef struct	s_memory_pointer
{
	int								raw_page_id;
	int								curr_page_id;
	int								offset;
	int								size;
	int								initialized;
	void							*data;
} fl_pointer;

typedef struct	s_memory_page
{
	int								is_free;
	int								size;
	int								id;
	int								last_offset;
	int								curr_capacity;
	int								initialized;
	int								completion;
	int								free_count;
	char							end_splitter;
	unsigned char					DATA[PAGE_SIZE];
	fl_free_block					free_blocks[MAX_FREE_COUNT];
} fl_mem_page;

typedef struct	s_memory_block
{
	char							end_splitter;
	int								initialized;
	fl_mem_page						PAGE[PAGE_COUNT];
} fl_memory;

typedef struct	s_memory_central
{
	fl_memory						HEAPS[MAX_HEAP_COUNT];
} fl_central;

#endif
