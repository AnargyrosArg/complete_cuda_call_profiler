#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamCopyAttributes)(CUstream, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamCopyAttributes(CUstream dst, CUstream src) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamCopyAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamCopyAttributes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamCopyAttributes = (CUresult (*)(CUstream, CUstream)) __libc_dlsym(libcuda_handle, "cuStreamCopyAttributes");
			fprintf(stderr, "cuStreamCopyAttributes:%p\n", original_cuStreamCopyAttributes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamCopyAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamCopyAttributes(dst, src);
		return retval;
	}
}

