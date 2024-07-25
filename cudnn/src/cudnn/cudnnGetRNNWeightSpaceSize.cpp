#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNWeightSpaceSize)(cudnnHandle_t, cudnnRNNDescriptor_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNWeightSpaceSize(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, size_t *weightSpaceSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNWeightSpaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNWeightSpaceSize = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNWeightSpaceSize");
			fprintf(stderr, "wrapper_cudnnGetRNNWeightSpaceSize:%p\n", wrapper_cudnnGetRNNWeightSpaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNWeightSpaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNWeightSpaceSize(handle, rnnDesc, weightSpaceSize);
		return retval;
	}
}

