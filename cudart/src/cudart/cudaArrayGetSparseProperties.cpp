
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaArrayGetSparseProperties)(struct cudaArraySparseProperties *, cudaArray_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaArrayGetSparseProperties(struct cudaArraySparseProperties *sparseProperties, cudaArray_t array) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaArrayGetSparseProperties)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaArrayGetSparseProperties = (cudaError_t (*)(struct cudaArraySparseProperties *, cudaArray_t)) dlsym(libcudart_handle, "cudaArrayGetSparseProperties");
			fprintf(stderr, "cudaArrayGetSparseProperties:%p\n", wrapper_cudaArrayGetSparseProperties);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaArrayGetSparseProperties():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaArrayGetSparseProperties(sparseProperties, array);
		return retval;
	}
}

