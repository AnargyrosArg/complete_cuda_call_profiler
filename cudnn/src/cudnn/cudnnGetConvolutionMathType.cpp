#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionMathType)(cudnnConvolutionDescriptor_t, cudnnMathType_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionMathType(cudnnConvolutionDescriptor_t convDesc, cudnnMathType_t *mathType{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionMathType)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionMathType = (cudnnStatus_t (*)(cudnnConvolutionDescriptor_t, cudnnMathType_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionMathType");
			fprintf(stderr, "wrapper_cudnnGetConvolutionMathType:%p\n", wrapper_cudnnGetConvolutionMathType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionMathType():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionMathType(convDesc, mathType);
		return retval;
	}
}

