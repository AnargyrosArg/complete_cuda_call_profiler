#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDivisiveNormalizationForward)(cudnnHandle_t, cudnnLRNDescriptor_t, cudnnDivNormMode_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, void *, void *, const void *, const cudnnTensorDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDivisiveNormalizationForward(cudnnHandle_t handle, cudnnLRNDescriptor_t normDesc, cudnnDivNormMode_t mode, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const void *means, void *temp, void *temp2, const void *beta, const cudnnTensorDescriptor_t yDesc, void *y){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDivisiveNormalizationForward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDivisiveNormalizationForward = (cudnnStatus_t (*)(cudnnHandle_t, cudnnLRNDescriptor_t, cudnnDivNormMode_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, void *, void *, const void *, const cudnnTensorDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDivisiveNormalizationForward");
			fprintf(stderr, "wrapper_cudnnDivisiveNormalizationForward:%p\n", wrapper_cudnnDivisiveNormalizationForward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDivisiveNormalizationForward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDivisiveNormalizationForward(handle, normDesc, mode, alpha, xDesc, x, means, temp, temp2, beta, yDesc, y);
		return retval;
	}
}

