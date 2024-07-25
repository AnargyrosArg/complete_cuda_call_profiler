#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetConvolutionReorderType)(cudnnConvolutionDescriptor_t, cudnnReorderType_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetConvolutionReorderType(cudnnConvolutionDescriptor_t convDesc, cudnnReorderType_t reorderType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetConvolutionReorderType)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetConvolutionReorderType = (cudnnStatus_t (*)(cudnnConvolutionDescriptor_t, cudnnReorderType_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetConvolutionReorderType");
			fprintf(stderr, "wrapper_cudnnSetConvolutionReorderType:%p\n", wrapper_cudnnSetConvolutionReorderType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetConvolutionReorderType():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetConvolutionReorderType(convDesc, reorderType);
		return retval;
	}
}

