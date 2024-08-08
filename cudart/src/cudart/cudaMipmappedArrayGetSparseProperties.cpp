
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMipmappedArrayGetSparseProperties)(struct cudaArraySparseProperties *, cudaMipmappedArray_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMipmappedArrayGetSparseProperties(struct cudaArraySparseProperties *sparseProperties, cudaMipmappedArray_t mipmap) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMipmappedArrayGetSparseProperties)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMipmappedArrayGetSparseProperties = (cudaError_t (*)(struct cudaArraySparseProperties *, cudaMipmappedArray_t)) dlsym(libcudart_handle, "cudaMipmappedArrayGetSparseProperties");
			fprintf(stderr, "cudaMipmappedArrayGetSparseProperties:%p\n", wrapper_cudaMipmappedArrayGetSparseProperties);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMipmappedArrayGetSparseProperties():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMipmappedArrayGetSparseProperties(sparseProperties, mipmap);
		return retval;
	}
}

