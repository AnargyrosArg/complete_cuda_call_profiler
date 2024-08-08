#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMipmappedArrayGetSparseProperties)(CUDA_ARRAY_SPARSE_PROPERTIES *, CUmipmappedArray);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMipmappedArrayGetSparseProperties(CUDA_ARRAY_SPARSE_PROPERTIES *sparseProperties, CUmipmappedArray mipmap) {
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
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayGetSparseProperties():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMipmappedArrayGetSparseProperties)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMipmappedArrayGetSparseProperties = (CUresult (*)(CUDA_ARRAY_SPARSE_PROPERTIES *, CUmipmappedArray)) __libc_dlsym(libcuda_handle, "cuMipmappedArrayGetSparseProperties");
			fprintf(stderr, "cuMipmappedArrayGetSparseProperties:%p\n", original_cuMipmappedArrayGetSparseProperties);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayGetSparseProperties():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMipmappedArrayGetSparseProperties(sparseProperties, mipmap);
		return retval;
	}
}

