#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemsetD2D8_v2)(CUdeviceptr, size_t, unsigned char, size_t, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemsetD2D8_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height) {
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
				fprintf(stderr, "dlsym error for fntion cuMemsetD2D8_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemsetD2D8_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemsetD2D8_v2 = (CUresult (*)(CUdeviceptr, size_t, unsigned char, size_t, size_t)) __libc_dlsym(libcuda_handle, "cuMemsetD2D8_v2");
			fprintf(stderr, "cuMemsetD2D8_v2:%p\n", original_cuMemsetD2D8_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD2D8_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemsetD2D8_v2(dstDevice, dstPitch, uc, Width, Height);
		return retval;
	}
}

