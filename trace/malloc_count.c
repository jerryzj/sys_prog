#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <dlfcn.h>

static int m_count = 0;
static int f_count = 0;
void *malloc(size_t size){
    char buf[64];
    static void *(*real_malloc)(size_t) = NULL;
    
    if(real_malloc == NULL){
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    ++m_count;
    sprintf(buf,"malloc called %d times\n", m_count);
    write(2, buf, strlen(buf));
    return real_malloc(size);
}
void free(void *ptr){
    char buf[64];
    static void *(*real_free)(void *ptr) = NULL;
    
    if(real_free == NULL){
        real_free = dlsym(RTLD_NEXT, "free");
    }
    ++f_count;
    sprintf(buf, "free called %d times\n", f_count);
    write(2, buf, strlen(buf));
    real_free(ptr);
    return;
}
