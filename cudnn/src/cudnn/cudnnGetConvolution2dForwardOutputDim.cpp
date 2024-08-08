#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolution2dForwardOutputDim)(const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, int *, int *, int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolution2dForwardOutputDim(const cudnnConvolutionDescriptor_t convDesc, const cudnnTensorDescriptor_t inputTensorDesc, const cudnnFilterDescriptor_t filterDesc, int *n, int *c, int *h, int *w{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolution2dForwardOutputDim)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolution2dForwardOutputDim = (cudnnStatus_t (*)(const cudnnConvolutionDescriptor_t, const cudnnTensorDescriptor_t, const cudnnFilterDescriptor_t, int *, int *, int *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolution2dForwardOutputDim");
			fprintf(stderr, "wrapper_cudnnGetConvolution2dForwardOutputDim:%p\n", wrapper_cudnnGetConvolution2dForwardOutputDim);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolution2dForwardOutputDim():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolution2dForwardOutputDim(convDesc, inputTensorDesc, filterDesc, n, c, h, w);
		return retval;
	}
}

