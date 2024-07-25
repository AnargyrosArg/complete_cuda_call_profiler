#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuArrayGetSparseProperties)(CUDA_ARRAY_SPARSE_PROPERTIES *, CUarray);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuArrayGetSparseProperties(CUDA_ARRAY_SPARSE_PROPERTIES *sparseProperties, CUarray array) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArrayGetSparseProperties():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuArrayGetSparseProperties)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuArrayGetSparseProperties = (CUresult (*)(CUDA_ARRAY_SPARSE_PROPERTIES *, CUarray)) __libc_dlsym(libcuda_handle, "cuArrayGetSparseProperties");
			fprintf(stderr, "cuArrayGetSparseProperties:%p\n", original_cuArrayGetSparseProperties);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArrayGetSparseProperties():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuArrayGetSparseProperties(sparseProperties, array);
		return retval;
	}
}

