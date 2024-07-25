#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphicsUnmapResources)(unsigned int, CUgraphicsResource *, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphicsUnmapResources():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphicsUnmapResources)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphicsUnmapResources = (CUresult (*)(unsigned int, CUgraphicsResource *, CUstream)) __libc_dlsym(libcuda_handle, "cuGraphicsUnmapResources");
			fprintf(stderr, "cuGraphicsUnmapResources:%p\n", original_cuGraphicsUnmapResources);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphicsUnmapResources():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphicsUnmapResources(count, resources, hStream);
		return retval;
	}
}

