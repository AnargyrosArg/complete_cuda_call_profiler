#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSpatialTfSamplerForward)(cudnnHandle_t, cudnnSpatialTransformerDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const void *, cudnnTensorDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSpatialTfSamplerForward(cudnnHandle_t handle, cudnnSpatialTransformerDescriptor_t stDesc, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const void *grid, const void *beta, cudnnTensorDescriptor_t yDesc, void *y){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSpatialTfSamplerForward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSpatialTfSamplerForward = (cudnnStatus_t (*)(cudnnHandle_t, cudnnSpatialTransformerDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const void *, cudnnTensorDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSpatialTfSamplerForward");
			fprintf(stderr, "wrapper_cudnnSpatialTfSamplerForward:%p\n", wrapper_cudnnSpatialTfSamplerForward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSpatialTfSamplerForward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSpatialTfSamplerForward(handle, stDesc, alpha, xDesc, x, grid, beta, yDesc, y);
		return retval;
	}
}

