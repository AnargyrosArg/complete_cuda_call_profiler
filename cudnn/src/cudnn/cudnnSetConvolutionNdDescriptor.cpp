#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetConvolutionNdDescriptor)(cudnnConvolutionDescriptor_t, int, const int *, const int *, const int *, cudnnConvolutionMode_t, cudnnDataType_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetConvolutionNdDescriptor(cudnnConvolutionDescriptor_t convDesc, int arrayLength, const int padA[], const int filterStrideA[], const int dilationA[], cudnnConvolutionMode_t mode, cudnnDataType_t computeType{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetConvolutionNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetConvolutionNdDescriptor = (cudnnStatus_t (*)(cudnnConvolutionDescriptor_t, int, const int *, const int *, const int *, cudnnConvolutionMode_t, cudnnDataType_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetConvolutionNdDescriptor");
			fprintf(stderr, "wrapper_cudnnSetConvolutionNdDescriptor:%p\n", wrapper_cudnnSetConvolutionNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetConvolutionNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetConvolutionNdDescriptor(convDesc, arrayLength, padA, filterStrideA, dilationA, mode, computeType);
		return retval;
	}
}

