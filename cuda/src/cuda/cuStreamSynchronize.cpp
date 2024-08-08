#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamSynchronize)(CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamSynchronize(CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamSynchronize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamSynchronize)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamSynchronize = (CUresult (*)(CUstream)) __libc_dlsym(libcuda_handle, "cuStreamSynchronize");
			fprintf(stderr, "cuStreamSynchronize:%p\n", original_cuStreamSynchronize);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamSynchronize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamSynchronize(hStream);
		return retval;
	}
}

