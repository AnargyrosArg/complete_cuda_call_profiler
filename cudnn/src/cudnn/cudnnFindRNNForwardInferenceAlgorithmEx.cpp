#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindRNNForwardInferenceAlgorithmEx)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t *, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const float, const int, int *, cudnnAlgorithmPerformance_t *, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindRNNForwardInferenceAlgorithmEx(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const int seqLength, const cudnnTensorDescriptor_t *xDesc, const void *x, const cudnnTensorDescriptor_t hxDesc, const void *hx, const cudnnTensorDescriptor_t cxDesc, const void *cx, const cudnnFilterDescriptor_t wDesc, const void *w, const cudnnTensorDescriptor_t *yDesc, void *y, const cudnnTensorDescriptor_t hyDesc, void *hy, const cudnnTensorDescriptor_t cyDesc, void *cy, const float findIntensity, const int requestedAlgoCount, int *returnedAlgoCount, cudnnAlgorithmPerformance_t *perfResults, void *workspace, size_t workSpaceSizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindRNNForwardInferenceAlgorithmEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindRNNForwardInferenceAlgorithmEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t *, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const float, const int, int *, cudnnAlgorithmPerformance_t *, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindRNNForwardInferenceAlgorithmEx");
			fprintf(stderr, "wrapper_cudnnFindRNNForwardInferenceAlgorithmEx:%p\n", wrapper_cudnnFindRNNForwardInferenceAlgorithmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindRNNForwardInferenceAlgorithmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindRNNForwardInferenceAlgorithmEx(handle, rnnDesc, seqLength, xDesc, x, hxDesc, hx, cxDesc, cx, wDesc, w, yDesc, y, hyDesc, hy, cyDesc, cy, findIntensity, requestedAlgoCount, returnedAlgoCount, perfResults, workspace, workSpaceSizeInBytes);
		return retval;
	}
}

