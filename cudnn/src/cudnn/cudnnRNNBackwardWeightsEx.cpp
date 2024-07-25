#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRNNBackwardWeightsEx)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnRNNDataDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, const void *, void *, size_t, const cudnnFilterDescriptor_t, void *, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRNNBackwardWeightsEx(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const cudnnRNNDataDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t hxDesc, const void *hx, const cudnnRNNDataDescriptor_t yDesc, const void *y, void *workSpace, size_t workSpaceSizeInBytes, const cudnnFilterDescriptor_t dwDesc, void *dw, void *reserveSpace, size_t reserveSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRNNBackwardWeightsEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRNNBackwardWeightsEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const cudnnRNNDataDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnRNNDataDescriptor_t, const void *, void *, size_t, const cudnnFilterDescriptor_t, void *, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRNNBackwardWeightsEx");
			fprintf(stderr, "wrapper_cudnnRNNBackwardWeightsEx:%p\n", wrapper_cudnnRNNBackwardWeightsEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRNNBackwardWeightsEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRNNBackwardWeightsEx(handle, rnnDesc, xDesc, x, hxDesc, hx, yDesc, y, workSpace, workSpaceSizeInBytes, dwDesc, dw, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

