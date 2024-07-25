#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetAlgorithmSpaceSize)(cudnnHandle_t, cudnnAlgorithmDescriptor_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetAlgorithmSpaceSize(cudnnHandle_t handle, cudnnAlgorithmDescriptor_t algoDesc, size_t *algoSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetAlgorithmSpaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetAlgorithmSpaceSize = (cudnnStatus_t (*)(cudnnHandle_t, cudnnAlgorithmDescriptor_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetAlgorithmSpaceSize");
			fprintf(stderr, "wrapper_cudnnGetAlgorithmSpaceSize:%p\n", wrapper_cudnnGetAlgorithmSpaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetAlgorithmSpaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetAlgorithmSpaceSize(handle, algoDesc, algoSpaceSizeInBytes);
		return retval;
	}
}

