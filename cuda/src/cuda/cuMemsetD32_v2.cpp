#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemsetD32_v2)(CUdeviceptr, unsigned int, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemsetD32_v2(CUdeviceptr dstDevice, unsigned int ui, size_t N) {
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
				fprintf(stderr, "dlsym error for fntion cuMemsetD32_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemsetD32_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemsetD32_v2 = (CUresult (*)(CUdeviceptr, unsigned int, size_t)) __libc_dlsym(libcuda_handle, "cuMemsetD32_v2");
			fprintf(stderr, "cuMemsetD32_v2:%p\n", original_cuMemsetD32_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD32_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemsetD32_v2(dstDevice, ui, N);
		return retval;
	}
}

