#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamUpdateCaptureDependencies)(CUstream, CUgraphNode *, size_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamUpdateCaptureDependencies(CUstream hStream, CUgraphNode *dependencies, size_t numDependencies, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamUpdateCaptureDependencies():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamUpdateCaptureDependencies)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamUpdateCaptureDependencies = (CUresult (*)(CUstream, CUgraphNode *, size_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamUpdateCaptureDependencies");
			fprintf(stderr, "cuStreamUpdateCaptureDependencies:%p\n", original_cuStreamUpdateCaptureDependencies);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamUpdateCaptureDependencies():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamUpdateCaptureDependencies(hStream, dependencies, numDependencies, flags);
		return retval;
	}
}

