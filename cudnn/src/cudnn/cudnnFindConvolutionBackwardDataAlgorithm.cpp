#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFindConvolutionBackwardDataAlgorithm)(cudnnHandle_t, const cudnnFilterDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const int, int *, cudnnConvolutionBwdDataAlgoPerf_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFindConvolutionBackwardDataAlgorithm(cudnnHandle_t handle, const cudnnFilterDescriptor_t wDesc, const cudnnTensorDescriptor_t dyDesc, const cudnnConvolutionDescriptor_t convDesc, const cudnnTensorDescriptor_t dxDesc, const int requestedAlgoCount, int *returnedAlgoCount, cudnnConvolutionBwdDataAlgoPerf_t *perfResults){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFindConvolutionBackwardDataAlgorithm)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFindConvolutionBackwardDataAlgorithm = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnFilterDescriptor_t, const cudnnTensorDescriptor_t, const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const int, int *, cudnnConvolutionBwdDataAlgoPerf_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFindConvolutionBackwardDataAlgorithm");
			fprintf(stderr, "wrapper_cudnnFindConvolutionBackwardDataAlgorithm:%p\n", wrapper_cudnnFindConvolutionBackwardDataAlgorithm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFindConvolutionBackwardDataAlgorithm():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFindConvolutionBackwardDataAlgorithm(handle, wDesc, dyDesc, convDesc, dxDesc, requestedAlgoCount, returnedAlgoCount, perfResults);
		return retval;
	}
}

