#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamQuery)(CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamQuery(CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamQuery():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamQuery)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamQuery = (CUresult (*)(CUstream)) __libc_dlsym(libcuda_handle, "cuStreamQuery");
			fprintf(stderr, "cuStreamQuery:%p\n", original_cuStreamQuery);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamQuery():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamQuery(hStream);
		return retval;
	}
}

