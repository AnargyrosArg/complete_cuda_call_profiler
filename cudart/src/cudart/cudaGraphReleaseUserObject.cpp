
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphReleaseUserObject)(cudaGraph_t, cudaUserObject_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphReleaseUserObject(cudaGraph_t graph, cudaUserObject_t object, unsigned int count) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphReleaseUserObject)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphReleaseUserObject = (cudaError_t (*)(cudaGraph_t, cudaUserObject_t, unsigned int)) dlsym(libcudart_handle, "cudaGraphReleaseUserObject");
			fprintf(stderr, "cudaGraphReleaseUserObject:%p\n", wrapper_cudaGraphReleaseUserObject);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphReleaseUserObject():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphReleaseUserObject(graph, object, count);
		return retval;
	}
}

