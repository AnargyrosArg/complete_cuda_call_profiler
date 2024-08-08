#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindConvolutionBackwardDataAlgorithmEx)(cudnnHandle_t, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, void *, const int, int *, cudnnConvolutionBwdDataAlgoPerf_t *, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindConvolutionBackwardDataAlgorithmEx(cudnnHandle_t handle, const cudnnFilterDescriptor_t wDesc, const void *w, const cudnnTensorDescriptor_t dyDesc, const void *dy, const cudnnConvolutionDescriptor_t convDesc, const cudnnTensorDescriptor_t dxDesc, void *dx, const int requestedAlgoCount, int *returnedAlgoCount, cudnnConvolutionBwdDataAlgoPerf_t *perfResults, void *workSpace, size_t workSpaceSizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindConvolutionBackwardDataAlgorithmEx)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindConvolutionBackwardDataAlgorithmEx = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnFilterDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, void *, const int, int *, cudnnConvolutionBwdDataAlgoPerf_t *, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindConvolutionBackwardDataAlgorithmEx");
			fprintf(stderr, "wrapper_cudnnFindConvolutionBackwardDataAlgorithmEx:%p\n", wrapper_cudnnFindConvolutionBackwardDataAlgorithmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindConvolutionBackwardDataAlgorithmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindConvolutionBackwardDataAlgorithmEx(handle, wDesc, w, dyDesc, dy, convDesc, dxDesc, dx, requestedAlgoCount, returnedAlgoCount, perfResults, workSpace, workSpaceSizeInBytes);
		return retval;
	}
}

