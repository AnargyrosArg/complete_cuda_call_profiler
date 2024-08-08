#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuEventCreate)(CUevent *, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuEventCreate(CUevent *phEvent, unsigned int Flags) {
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
				fprintf(stderr, "dlsym error for fntion cuEventCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuEventCreate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuEventCreate = (CUresult (*)(CUevent *, unsigned int)) __libc_dlsym(libcuda_handle, "cuEventCreate");
			fprintf(stderr, "cuEventCreate:%p\n", original_cuEventCreate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuEventCreate(phEvent, Flags);
		return retval;
	}
}

