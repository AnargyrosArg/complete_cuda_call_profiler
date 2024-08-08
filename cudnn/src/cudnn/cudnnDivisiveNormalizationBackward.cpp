#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDivisiveNormalizationBackward)(cudnnHandle_t, cudnnLRNDescriptor_t, cudnnDivNormMode_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const void *, void *, void *, const void *, const cudnnTensorDescriptor_t, void *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDivisiveNormalizationBackward(cudnnHandle_t handle, cudnnLRNDescriptor_t normDesc, cudnnDivNormMode_t mode, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const void *means, const void *dy, void *temp, void *temp2, const void *beta, const cudnnTensorDescriptor_t dXdMeansDesc, void *dx, void *dMeans){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDivisiveNormalizationBackward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDivisiveNormalizationBackward = (cudnnStatus_t (*)(cudnnHandle_t, cudnnLRNDescriptor_t, cudnnDivNormMode_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const void *, void *, void *, const void *, const cudnnTensorDescriptor_t, void *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDivisiveNormalizationBackward");
			fprintf(stderr, "wrapper_cudnnDivisiveNormalizationBackward:%p\n", wrapper_cudnnDivisiveNormalizationBackward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDivisiveNormalizationBackward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDivisiveNormalizationBackward(handle, normDesc, mode, alpha, xDesc, x, means, dy, temp, temp2, beta, dXdMeansDesc, dx, dMeans);
		return retval;
	}
}

