#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindConvolutionForwardAlgorithmEx)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, void *, const int, int *, cudnnConvolutionFwdAlgoPerf_t *, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindConvolutionForwardAlgorithmEx(cudnnHandle_t handle, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnFilterDescriptor_t wDesc, const void *w, const cudnnConvolutionDescriptor_t convDesc, const cudnnTensorDescriptor_t yDesc, void *y, const int requestedAlgoCount, int *returnedAlgoCount, cudnnConvolutionFwdAlgoPerf_t *perfResults, void *workSpace, size_t workSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindConvolutionForwardAlgorithmEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindConvolutionForwardAlgorithmEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, void *, const int, int *, cudnnConvolutionFwdAlgoPerf_t *, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindConvolutionForwardAlgorithmEx");
			fprintf(stderr, "wrapper_cudnnFindConvolutionForwardAlgorithmEx:%p\n", wrapper_cudnnFindConvolutionForwardAlgorithmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindConvolutionForwardAlgorithmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindConvolutionForwardAlgorithmEx(handle, xDesc, x, wDesc, w, convDesc, yDesc, y, requestedAlgoCount, returnedAlgoCount, perfResults, workSpace, workSpaceSizeInBytes);
		return retval;
	}
}

