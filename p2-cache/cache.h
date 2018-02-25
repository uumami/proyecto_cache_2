
/*
 * cache.h
 */

/* 

Luis Fernando Cantú Díaz León
Bernardo García Bulle Bueno
Mario Vázquez Corte

*/

#define TRUE 1
#define FALSE 0

/* default cache parameters--can be changed */
#define WORD_SIZE 4
#define WORD_SIZE_OFFSET 2
#define DEFAULT_CACHE_SIZE (8 * 1024)
#define DEFAULT_CACHE_BLOCK_SIZE 16
#define DEFAULT_CACHE_ASSOC 1
#define DEFAULT_CACHE_WRITEBACK TRUE
#define DEFAULT_CACHE_WRITEALLOC TRUE

/* constants for settting cache parameters */
#define CACHE_PARAM_BLOCK_SIZE 0
#define CACHE_PARAM_USIZE 1
#define CACHE_PARAM_ISIZE 2
#define CACHE_PARAM_DSIZE 3
#define CACHE_PARAM_ASSOC 4
#define CACHE_PARAM_WRITEBACK 5
#define CACHE_PARAM_WRITETHROUGH 6
#define CACHE_PARAM_WRITEALLOC 7
#define CACHE_PARAM_NOWRITEALLOC 8


/* structure definitions */
// puede que sea conveniente contar los hits por cache line, o con banderas
typedef struct cache_line_ {
  unsigned tag;
  int dirty;

  struct cache_line_ *LRU_next;
  struct cache_line_ *LRU_prev;
} cache_line, *Pcache_line;


// Probablemente tendremos que modificarla.
// Depende de como se use la mascara de bits (strings o mask)
typedef struct cache_ {
  int size;			/* cache size */
  int associativity;		/* cache associativity */
  int n_sets;			/* number of cache sets */
  
  unsigned tag_mask;		/* tag mask */
  unsigned index_mask;	/* index mask*/
  unsigned offset_mask;	 /* offset mask */  // it is practically useless
  
  int tag_s;		/* tag number of zeroes */
  int index_s;	/* index number of zeroes*/
  int offset_s;	 /* offset number of zeroes */ 

  Pcache_line *LRU_head;	/* head of LRU list for each set */
  Pcache_line *LRU_tail;	/* tail of LRU list for each set */
  int *set_contents;		/* number of valid entries in set */
  int contents;			/* number of valid entries in cache */
} cache, *Pcache;



typedef struct cache_stat_ {
  int accesses;			/* number of memory references to cache memory */
  int misses;			/* number of cache misses */
  int replacements;		/* number of misses that cause replacments */
  int demand_fetches;	/* number of fetches to memory ram */
  int copies_back;		/* number of write backs */
} cache_stat, *Pcache_stat;


/* function prototypes */
void set_cache_param();
void init_cache();
void perform_access();
void flush();
void delete();
void insert();
void dump_settings();
void print_stats();


/* macros */
// Posiblemente lo modifiquemos para agregar macros
#define LOG2(x) ((int) rint((log((double) (x))) / (log(2.0))))