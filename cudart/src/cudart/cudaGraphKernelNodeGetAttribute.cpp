
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphKernelNodeGetAttribute)(cudaGraphNode_t, cudaKernelNodeAttrID, cudaKernelNodeAttrValue *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphKernelNodeGetAttribute(cudaGraphNode_t hNode, cudaKernelNodeAttrID attr, cudaKernelNodeAttrValue *value_out) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphKernelNodeGetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphKernelNodeGetAttribute = (cudaError_t (*)(cudaGraphNode_t, cudaKernelNodeAttrID, cudaKernelNodeAttrValue *)) dlsym(libcudart_handle, "cudaGraphKernelNodeGetAttribute");
			fprintf(stderr, "cudaGraphKernelNodeGetAttribute:%p\n", wrapper_cudaGraphKernelNodeGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphKernelNodeGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphKernelNodeGetAttribute(hNode, attr, value_out);
		return retval;
	}
}

