#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetConvolutionGroupCount)(cudnnConvolutionDescriptor_t, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetConvolutionGroupCount(cudnnConvolutionDescriptor_t convDesc, int groupCount{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetConvolutionGroupCount)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetConvolutionGroupCount = (cudnnStatus_t (*)(cudnnConvolutionDescriptor_t, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetConvolutionGroupCount");
			fprintf(stderr, "wrapper_cudnnSetConvolutionGroupCount:%p\n", wrapper_cudnnSetConvolutionGroupCount);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetConvolutionGroupCount():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetConvolutionGroupCount(convDesc, groupCount);
		return retval;
	}
}

