#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionNdForwardOutputDim)(const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, int, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionNdForwardOutputDim(const cudnnConvolutionDescriptor_t convDesc, const cudnnTensorDescriptor_t inputTensorDesc, const cudnnFilterDescriptor_t filterDesc, int nbDims, int tensorOuputDimA[]){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionNdForwardOutputDim)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionNdForwardOutputDim = (cudnnStatus_t (*)(const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, int, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionNdForwardOutputDim");
			fprintf(stderr, "wrapper_cudnnGetConvolutionNdForwardOutputDim:%p\n", wrapper_cudnnGetConvolutionNdForwardOutputDim);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionNdForwardOutputDim():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionNdForwardOutputDim(convDesc, inputTensorDesc, filterDesc, nbDims, tensorOuputDimA);
		return retval;
	}
}

