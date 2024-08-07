#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuEventQuery)(CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuEventQuery(CUevent hEvent) {
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
				fprintf(stderr, "dlsym error for fntion cuEventQuery():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuEventQuery)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuEventQuery = (CUresult (*)(CUevent)) __libc_dlsym(libcuda_handle, "cuEventQuery");
			fprintf(stderr, "cuEventQuery:%p\n", original_cuEventQuery);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventQuery():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuEventQuery(hEvent);
		return retval;
	}
}

