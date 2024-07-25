#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuArray3DGetDescriptor_v2)(CUDA_ARRAY3D_DESCRIPTOR *, CUarray);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuArray3DGetDescriptor_v2(CUDA_ARRAY3D_DESCRIPTOR *pArrayDescriptor, CUarray hArray) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArray3DGetDescriptor_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuArray3DGetDescriptor_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuArray3DGetDescriptor_v2 = (CUresult (*)(CUDA_ARRAY3D_DESCRIPTOR *, CUarray)) __libc_dlsym(libcuda_handle, "cuArray3DGetDescriptor_v2");
			fprintf(stderr, "cuArray3DGetDescriptor_v2:%p\n", original_cuArray3DGetDescriptor_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArray3DGetDescriptor_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuArray3DGetDescriptor_v2(pArrayDescriptor, hArray);
		return retval;
	}
}

