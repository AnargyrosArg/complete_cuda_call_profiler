#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDestroyExternalMemory)(CUexternalMemory);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDestroyExternalMemory(CUexternalMemory extMem) {
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
				fprintf(stderr, "dlsym error for fntion cuDestroyExternalMemory():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDestroyExternalMemory)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDestroyExternalMemory = (CUresult (*)(CUexternalMemory)) __libc_dlsym(libcuda_handle, "cuDestroyExternalMemory");
			fprintf(stderr, "cuDestroyExternalMemory:%p\n", original_cuDestroyExternalMemory);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDestroyExternalMemory():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDestroyExternalMemory(extMem);
		return retval;
	}
}

