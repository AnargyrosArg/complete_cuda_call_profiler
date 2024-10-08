#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemGetInfo_v2)(size_t *, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemGetInfo_v2(size_t *free, size_t *total) {
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
				fprintf(stderr, "dlsym error for fntion cuMemGetInfo_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemGetInfo_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemGetInfo_v2 = (CUresult (*)(size_t *, size_t *)) __libc_dlsym(libcuda_handle, "cuMemGetInfo_v2");
			fprintf(stderr, "cuMemGetInfo_v2:%p\n", original_cuMemGetInfo_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetInfo_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemGetInfo_v2(free, total);
		return retval;
	}
}

