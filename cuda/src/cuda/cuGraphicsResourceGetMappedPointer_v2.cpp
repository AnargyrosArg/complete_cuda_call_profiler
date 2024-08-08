#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphicsResourceGetMappedPointer_v2)(CUdeviceptr *, size_t *, CUgraphicsResource);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphicsResourceGetMappedPointer_v2(CUdeviceptr *pDevPtr, size_t *pSize, CUgraphicsResource resource) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphicsResourceGetMappedPointer_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphicsResourceGetMappedPointer_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphicsResourceGetMappedPointer_v2 = (CUresult (*)(CUdeviceptr *, size_t *, CUgraphicsResource)) __libc_dlsym(libcuda_handle, "cuGraphicsResourceGetMappedPointer_v2");
			fprintf(stderr, "cuGraphicsResourceGetMappedPointer_v2:%p\n", original_cuGraphicsResourceGetMappedPointer_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphicsResourceGetMappedPointer_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphicsResourceGetMappedPointer_v2(pDevPtr, pSize, resource);
		return retval;
	}
}

