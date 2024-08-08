#include <dlfcn.h>
#include <iostream>
#include <unistd.h>
#include <cstring>


extern "C" { 
    void* __libc_dlsym (void *, const char *);
    void* __libc_dlopen_mode (const char*,int); 
}

void* (*original_dlsym)(void*,const char*) = NULL;


extern "C"{
    int dladdr1(const void *addr, Dl_info *info, void **extra_info, int flags){
        // fprintf(stderr,"dladdr1 called for addr:%p and flags %d",addr,flags);
        int (*original_dladdr1)(const void *, Dl_info *, void **, int );
        original_dladdr1 = (int (*)(const void *, Dl_info *, void **, int )) original_dlsym(__libc_dlopen_mode("libdl.so.2",RTLD_LAZY) , "dladdr1");
        int ret;
        ret = original_dladdr1(addr,info,extra_info,flags);
        // fprintf(stderr," fname: %s , sname:%s\n",info->dli_fname,info->dli_sname);
        // fprintf(stderr,"*extra_info is %p\n",*extra_info);
        return ret;
    } 


    void* dlsym(void *handle, const char *symbol)
    {
        #ifdef PRINT_TRACE
        fprintf(stderr,"dlsym called for symbol %s and handle %p\n",symbol,handle);
        #endif
        if(original_dlsym == NULL){
            original_dlsym = (void* (*)(void*, const char*)) __libc_dlsym(__libc_dlopen_mode("libdl.so.2",RTLD_LAZY), "dlsym");
        }

        void* retval = (original_dlsym(handle, symbol));
        char* __dlerror;
        __dlerror = dlerror();
        if (__dlerror){
            fprintf(stderr,"dlsym error:%s\n",__dlerror);
        }
        return retval;
    }



    void *dlvsym(void *handle,const char *symbol,const char *version){
        #ifdef PRINT_TRACE
        fprintf(stderr,"dlvsym called for symbol %s and handle %p and version %s\n",symbol,handle,version);
        #endif
        void* (*original_dlvsym)(void *,const char *,const char *);
        original_dlvsym = (void *(*)(void *,const char *,const char *)) original_dlsym(__libc_dlopen_mode("libdl.so.2",RTLD_LAZY), "dlvsym");
        return original_dlvsym(handle,symbol,version);
    }


    int dlclose(void *handle){
        int (*original_dlclose)( void*);
        original_dlclose = (int (*)( void*))original_dlsym(__libc_dlopen_mode("libdl.so.2",RTLD_LAZY),"dlclose");        
        #ifdef PRINT_TRACE
        fprintf(stderr,"dlclose for handle %p\n",handle);
        #endif
        return original_dlclose(handle);
    }   


}
