#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionReorderType)(cudnnConvolutionDescriptor_t, cudnnReorderType_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionReorderType(cudnnConvolutionDescriptor_t convDesc, cudnnReorderType_t *reorderType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionReorderType)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionReorderType = (cudnnStatus_t (*)(cudnnConvolutionDescriptor_t, cudnnReorderType_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionReorderType");
			fprintf(stderr, "wrapper_cudnnGetConvolutionReorderType:%p\n", wrapper_cudnnGetConvolutionReorderType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionReorderType():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionReorderType(convDesc, reorderType);
		return retval;
	}
}

