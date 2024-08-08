#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphicsResourceGetMappedMipmappedArray)(CUmipmappedArray *, CUgraphicsResource);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphicsResourceGetMappedMipmappedArray(CUmipmappedArray *pMipmappedArray, CUgraphicsResource resource) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphicsResourceGetMappedMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphicsResourceGetMappedMipmappedArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphicsResourceGetMappedMipmappedArray = (CUresult (*)(CUmipmappedArray *, CUgraphicsResource)) __libc_dlsym(libcuda_handle, "cuGraphicsResourceGetMappedMipmappedArray");
			fprintf(stderr, "cuGraphicsResourceGetMappedMipmappedArray:%p\n", original_cuGraphicsResourceGetMappedMipmappedArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphicsResourceGetMappedMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphicsResourceGetMappedMipmappedArray(pMipmappedArray, resource);
		return retval;
	}
}

