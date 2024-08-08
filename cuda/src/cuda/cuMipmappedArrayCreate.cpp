#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMipmappedArrayCreate)(CUmipmappedArray *, const CUDA_ARRAY3D_DESCRIPTOR *, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMipmappedArrayCreate(CUmipmappedArray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels) {
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
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMipmappedArrayCreate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMipmappedArrayCreate = (CUresult (*)(CUmipmappedArray *, const CUDA_ARRAY3D_DESCRIPTOR *, unsigned int)) __libc_dlsym(libcuda_handle, "cuMipmappedArrayCreate");
			fprintf(stderr, "cuMipmappedArrayCreate:%p\n", original_cuMipmappedArrayCreate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMipmappedArrayCreate(pHandle, pMipmappedArrayDesc, numMipmapLevels);
		return retval;
	}
}

