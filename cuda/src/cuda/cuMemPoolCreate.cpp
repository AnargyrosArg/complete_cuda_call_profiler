#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolCreate)(CUmemoryPool *, const CUmemPoolProps *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolCreate(CUmemoryPool *pool, const CUmemPoolProps *poolProps) {
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
				fprintf(stderr, "dlsym error for fntion cuMemPoolCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolCreate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolCreate = (CUresult (*)(CUmemoryPool *, const CUmemPoolProps *)) __libc_dlsym(libcuda_handle, "cuMemPoolCreate");
			fprintf(stderr, "cuMemPoolCreate:%p\n", original_cuMemPoolCreate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolCreate(pool, poolProps);
		return retval;
	}
}

