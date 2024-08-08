#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSpatialTfSamplerBackward)(cudnnHandle_t, cudnnSpatialTransformerDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, void *, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const void *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSpatialTfSamplerBackward(cudnnHandle_t handle, cudnnSpatialTransformerDescriptor_t stDesc, const void *alpha, const cudnnTensorDescriptor_t xDesc, const void *x, const void *beta, const cudnnTensorDescriptor_t dxDesc, void *dx, const void *alphaDgrid, const cudnnTensorDescriptor_t dyDesc, const void *dy, const void *grid, const void *betaDgrid, void *dgrid){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSpatialTfSamplerBackward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSpatialTfSamplerBackward = (cudnnStatus_t (*)(cudnnHandle_t, cudnnSpatialTransformerDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, void *, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const void *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSpatialTfSamplerBackward");
			fprintf(stderr, "wrapper_cudnnSpatialTfSamplerBackward:%p\n", wrapper_cudnnSpatialTfSamplerBackward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSpatialTfSamplerBackward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSpatialTfSamplerBackward(handle, stDesc, alpha, xDesc, x, beta, dxDesc, dx, alphaDgrid, dyDesc, dy, grid, betaDgrid, dgrid);
		return retval;
	}
}

