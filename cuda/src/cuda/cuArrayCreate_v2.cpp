#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuArrayCreate_v2)(CUarray *, const CUDA_ARRAY_DESCRIPTOR *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuArrayCreate_v2(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR *pAllocateArray) {
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
				fprintf(stderr, "dlsym error for fntion cuArrayCreate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuArrayCreate_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuArrayCreate_v2 = (CUresult (*)(CUarray *, const CUDA_ARRAY_DESCRIPTOR *)) __libc_dlsym(libcuda_handle, "cuArrayCreate_v2");
			fprintf(stderr, "cuArrayCreate_v2:%p\n", original_cuArrayCreate_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArrayCreate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuArrayCreate_v2(pHandle, pAllocateArray);
		return retval;
	}
}

