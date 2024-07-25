#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindRNNBackwardWeightsAlgorithmEx)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t *, const void *, const float, const int, int *, cudnnAlgorithmPerformance_t *, const void *, size_t, const cudnnFilterDescriptor_t, void *, const void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindRNNBackwardWeightsAlgorithmEx(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const int seqLength, const cudnnTensorDescriptor_t *xDesc, const void *x, const cudnnTensorDescriptor_t hxDesc, const void *hx, const cudnnTensorDescriptor_t *yDesc, const void *y, const float findIntensity, const int requestedAlgoCount, int *returnedAlgoCount, cudnnAlgorithmPerformance_t *perfResults, const void *workspace, size_t workSpaceSizeInBytes, const cudnnFilterDescriptor_t dwDesc, void *dw, const void *reserveSpace, size_t reserveSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindRNNBackwardWeightsAlgorithmEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindRNNBackwardWeightsAlgorithmEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t *, const void *, const float, const int, int *, cudnnAlgorithmPerformance_t *, const void *, size_t, const cudnnFilterDescriptor_t, void *, const void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindRNNBackwardWeightsAlgorithmEx");
			fprintf(stderr, "wrapper_cudnnFindRNNBackwardWeightsAlgorithmEx:%p\n", wrapper_cudnnFindRNNBackwardWeightsAlgorithmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindRNNBackwardWeightsAlgorithmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindRNNBackwardWeightsAlgorithmEx(handle, rnnDesc, seqLength, xDesc, x, hxDesc, hx, yDesc, y, findIntensity, requestedAlgoCount, returnedAlgoCount, perfResults, workspace, workSpaceSizeInBytes, dwDesc, dw, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

