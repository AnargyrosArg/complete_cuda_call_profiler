#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphClone)(CUgraph *, CUgraph);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphClone(CUgraph *phGraphClone, CUgraph originalGraph) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphClone():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphClone)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphClone = (CUresult (*)(CUgraph *, CUgraph)) __libc_dlsym(libcuda_handle, "cuGraphClone");
			fprintf(stderr, "cuGraphClone:%p\n", original_cuGraphClone);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphClone():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphClone(phGraphClone, originalGraph);
		return retval;
	}
}

