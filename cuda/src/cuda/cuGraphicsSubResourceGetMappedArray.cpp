#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphicsSubResourceGetMappedArray)(CUarray *, CUgraphicsResource, unsigned int, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphicsSubResourceGetMappedArray(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphicsSubResourceGetMappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphicsSubResourceGetMappedArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphicsSubResourceGetMappedArray = (CUresult (*)(CUarray *, CUgraphicsResource, unsigned int, unsigned int)) __libc_dlsym(libcuda_handle, "cuGraphicsSubResourceGetMappedArray");
			fprintf(stderr, "cuGraphicsSubResourceGetMappedArray:%p\n", original_cuGraphicsSubResourceGetMappedArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphicsSubResourceGetMappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphicsSubResourceGetMappedArray(pArray, resource, arrayIndex, mipLevel);
		return retval;
	}
}

