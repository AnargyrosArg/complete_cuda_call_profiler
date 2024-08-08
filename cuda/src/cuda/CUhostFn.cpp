/*#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
void (*original_CUhostFn)(void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	void CUhostFn(void *userData) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion CUhostFn():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_CUhostFn)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_CUhostFn = (void (*)(void *)) __libc_dlsym(libcuda_handle, "cuhostFn");
			fprintf(stderr, "cuhostFn:%p\n", original_CUhostFn);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion CUhostFn():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		original_CUhostFn(userData);
	}
}
*/


