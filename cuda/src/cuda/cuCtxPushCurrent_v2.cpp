#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxPushCurrent_v2)(CUcontext);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxPushCurrent_v2(CUcontext ctx) {
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
				fprintf(stderr, "dlsym error for fntion cuCtxPushCurrent_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxPushCurrent_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxPushCurrent_v2 = (CUresult (*)(CUcontext)) __libc_dlsym(libcuda_handle, "cuCtxPushCurrent_v2");
			fprintf(stderr, "cuCtxPushCurrent_v2:%p\n", original_cuCtxPushCurrent_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxPushCurrent_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxPushCurrent_v2(ctx);
		return retval;
	}
}

