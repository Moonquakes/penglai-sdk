#define DEFAULT_HEAP_ADDR       0x0000002000000000
#define DEFAULT_UNTRUSTED_PTR   0x0000001000000000
#define DEFAULT_UNTRUSTED_SIZE  8*1024
#define OCALL_NR_WRITE                64
#define OCALL_MEMORY_EXTEND            2001
#define OCALL_MEMORY_FREE              2002
#define OCALL_SYSCALL              2003
#define OCALL_CACHE_BINDING    2004
#define OCALL_CACHE_UNBINDING  2005