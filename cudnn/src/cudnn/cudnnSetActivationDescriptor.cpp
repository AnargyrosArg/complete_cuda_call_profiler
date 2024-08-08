#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetActivationDescriptor)(cudnnActivationDescriptor_t, cudnnActivationMode_t, cudnnNanPropagation_t, double);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetActivationDescriptor(cudnnActivationDescriptor_t activationDesc, cudnnActivationMode_t mode, cudnnNanPropagation_t reluNanOpt, double coef{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetActivationDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetActivationDescriptor = (cudnnStatus_t (*)(cudnnActivationDescriptor_t, cudnnActivationMode_t, cudnnNanPropagation_t, double)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetActivationDescriptor");
			fprintf(stderr, "wrapper_cudnnSetActivationDescriptor:%p\n", wrapper_cudnnSetActivationDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetActivationDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetActivationDescriptor(activationDesc, mode, reluNanOpt, coef);
		return retval;
	}
}

