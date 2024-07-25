#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateConvolutionDescriptor)(cudnnConvolutionDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateConvolutionDescriptor(cudnnConvolutionDescriptor_t *convDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateConvolutionDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateConvolutionDescriptor = (cudnnStatus_t (*)(cudnnConvolutionDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateConvolutionDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateConvolutionDescriptor:%p\n", wrapper_cudnnCreateConvolutionDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateConvolutionDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateConvolutionDescriptor(convDesc);
		return retval;
	}
}

