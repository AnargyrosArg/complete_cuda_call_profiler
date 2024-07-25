#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNTempSpaceSizes)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnForwardMode_t, cudnnRNNDataDescriptor_t, size_t *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNTempSpaceSizes(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, cudnnForwardMode_t fMode, cudnnRNNDataDescriptor_t xDesc, size_t *workSpaceSize, size_t *reserveSpaceSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNTempSpaceSizes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNTempSpaceSizes = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnForwardMode_t, cudnnRNNDataDescriptor_t, size_t *, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNTempSpaceSizes");
			fprintf(stderr, "wrapper_cudnnGetRNNTempSpaceSizes:%p\n", wrapper_cudnnGetRNNTempSpaceSizes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNTempSpaceSizes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNTempSpaceSizes(handle, rnnDesc, fMode, xDesc, workSpaceSize, reserveSpaceSize);
		return retval;
	}
}

