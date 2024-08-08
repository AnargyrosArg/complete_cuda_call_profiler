#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyConvolutionDescriptor)(cudnnConvolutionDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyConvolutionDescriptor(cudnnConvolutionDescriptor_t convDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyConvolutionDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyConvolutionDescriptor = (cudnnStatus_t (*)(cudnnConvolutionDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyConvolutionDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyConvolutionDescriptor:%p\n", wrapper_cudnnDestroyConvolutionDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyConvolutionDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyConvolutionDescriptor(convDesc);
		return retval;
	}
}

