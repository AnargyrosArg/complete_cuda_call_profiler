#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDeriveBNTensorDescriptor)(cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, cudnnBatchNormMode_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDeriveBNTensorDescriptor(cudnnTensorDescriptor_t derivedBnDesc, const cudnnTensorDescriptor_t xDesc, cudnnBatchNormMode_t mode{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDeriveBNTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDeriveBNTensorDescriptor = (cudnnStatus_t (*)(cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, cudnnBatchNormMode_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDeriveBNTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnDeriveBNTensorDescriptor:%p\n", wrapper_cudnnDeriveBNTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDeriveBNTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDeriveBNTensorDescriptor(derivedBnDesc, xDesc, mode);
		return retval;
	}
}

