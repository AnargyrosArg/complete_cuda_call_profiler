
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphicsSubResourceGetMappedArray)(cudaArray_t *, cudaGraphicsResource_t, unsigned int, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphicsSubResourceGetMappedArray(cudaArray_t *array, cudaGraphicsResource_t resource, unsigned int arrayIndex, unsigned int mipLevel) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphicsSubResourceGetMappedArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphicsSubResourceGetMappedArray = (cudaError_t (*)(cudaArray_t *, cudaGraphicsResource_t, unsigned int, unsigned int)) dlsym(libcudart_handle, "cudaGraphicsSubResourceGetMappedArray");
			fprintf(stderr, "cudaGraphicsSubResourceGetMappedArray:%p\n", wrapper_cudaGraphicsSubResourceGetMappedArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphicsSubResourceGetMappedArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphicsSubResourceGetMappedArray(array, resource, arrayIndex, mipLevel);
		return retval;
	}
}

