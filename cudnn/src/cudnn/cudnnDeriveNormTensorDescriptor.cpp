#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDeriveNormTensorDescriptor)(cudnnTensorDescriptor_t, cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, cudnnNormMode_t, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDeriveNormTensorDescriptor(cudnnTensorDescriptor_t derivedNormScaleBiasDesc, cudnnTensorDescriptor_t derivedNormMeanVarDesc, const cudnnTensorDescriptor_t xDesc, cudnnNormMode_t mode, int groupCnt{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDeriveNormTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDeriveNormTensorDescriptor = (cudnnStatus_t (*)(cudnnTensorDescriptor_t, cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, cudnnNormMode_t, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDeriveNormTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnDeriveNormTensorDescriptor:%p\n", wrapper_cudnnDeriveNormTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDeriveNormTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDeriveNormTensorDescriptor(derivedNormScaleBiasDesc, derivedNormMeanVarDesc, xDesc, mode, groupCnt);
		return retval;
	}
}

