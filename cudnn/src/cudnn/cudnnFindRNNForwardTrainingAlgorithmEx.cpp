#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindRNNForwardTrainingAlgorithmEx)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t *, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const float, const int, int *, cudnnAlgorithmPerformance_t *, void *, size_t, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindRNNForwardTrainingAlgorithmEx(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, const int seqLength, const cudnnTensorDescriptor_t *xDesc, const void *x, const cudnnTensorDescriptor_t hxDesc, const void *hx, const cudnnTensorDescriptor_t cxDesc, const void *cx, const cudnnFilterDescriptor_t wDesc, const void *w, const cudnnTensorDescriptor_t *yDesc, void *y, const cudnnTensorDescriptor_t hyDesc, void *hy, const cudnnTensorDescriptor_t cyDesc, void *cy, const float findIntensity, const int requestedAlgoCount, int *returnedAlgoCount, cudnnAlgorithmPerformance_t *perfResults, void *workspace, size_t workSpaceSizeInBytes, void *reserveSpace, size_t reserveSpaceSizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindRNNForwardTrainingAlgorithmEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindRNNForwardTrainingAlgorithmEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, const int, const cudnnTensorDescriptor_t *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t *, void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, void *, const float, const int, int *, cudnnAlgorithmPerformance_t *, void *, size_t, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindRNNForwardTrainingAlgorithmEx");
			fprintf(stderr, "wrapper_cudnnFindRNNForwardTrainingAlgorithmEx:%p\n", wrapper_cudnnFindRNNForwardTrainingAlgorithmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindRNNForwardTrainingAlgorithmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindRNNForwardTrainingAlgorithmEx(handle, rnnDesc, seqLength, xDesc, x, hxDesc, hx, cxDesc, cx, wDesc, w, yDesc, y, hyDesc, hy, cyDesc, cy, findIntensity, requestedAlgoCount, returnedAlgoCount, perfResults, workspace, workSpaceSizeInBytes, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

