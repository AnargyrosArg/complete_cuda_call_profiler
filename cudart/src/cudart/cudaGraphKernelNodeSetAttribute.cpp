
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphKernelNodeSetAttribute)(cudaGraphNode_t, cudaKernelNodeAttrID, const cudaKernelNodeAttrValue *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphKernelNodeSetAttribute(cudaGraphNode_t hNode, cudaKernelNodeAttrID attr, const cudaKernelNodeAttrValue *value) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphKernelNodeSetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphKernelNodeSetAttribute = (cudaError_t (*)(cudaGraphNode_t, cudaKernelNodeAttrID, const cudaKernelNodeAttrValue *)) dlsym(libcudart_handle, "cudaGraphKernelNodeSetAttribute");
			fprintf(stderr, "cudaGraphKernelNodeSetAttribute:%p\n", wrapper_cudaGraphKernelNodeSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphKernelNodeSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphKernelNodeSetAttribute(hNode, attr, value);
		return retval;
	}
}

