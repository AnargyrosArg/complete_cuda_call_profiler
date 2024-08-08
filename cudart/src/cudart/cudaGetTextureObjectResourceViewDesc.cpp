
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetTextureObjectResourceViewDesc)(struct cudaResourceViewDesc *, cudaTextureObject_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetTextureObjectResourceViewDesc(struct cudaResourceViewDesc *pResViewDesc, cudaTextureObject_t texObject) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetTextureObjectResourceViewDesc)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetTextureObjectResourceViewDesc = (cudaError_t (*)(struct cudaResourceViewDesc *, cudaTextureObject_t)) dlsym(libcudart_handle, "cudaGetTextureObjectResourceViewDesc");
			fprintf(stderr, "cudaGetTextureObjectResourceViewDesc:%p\n", wrapper_cudaGetTextureObjectResourceViewDesc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetTextureObjectResourceViewDesc():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetTextureObjectResourceViewDesc(pResViewDesc, texObject);
		return retval;
	}
}

