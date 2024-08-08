#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexObjectDestroy)(CUtexObject);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexObjectDestroy(CUtexObject texObject) {
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
				fprintf(stderr, "dlsym error for fntion cuTexObjectDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexObjectDestroy)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexObjectDestroy = (CUresult (*)(CUtexObject)) __libc_dlsym(libcuda_handle, "cuTexObjectDestroy");
			fprintf(stderr, "cuTexObjectDestroy:%p\n", original_cuTexObjectDestroy);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexObjectDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexObjectDestroy(texObject);
		return retval;
	}
}

