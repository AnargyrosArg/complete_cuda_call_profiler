#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSpatialTfGridGeneratorForward)(cudnnHandle_t, const cudnnSpatialTransformerDescriptor_t, const void *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSpatialTfGridGeneratorForward(cudnnHandle_t handle, const cudnnSpatialTransformerDescriptor_t stDesc, const void *theta, void *grid) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSpatialTfGridGeneratorForward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSpatialTfGridGeneratorForward = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnSpatialTransformerDescriptor_t, const void *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSpatialTfGridGeneratorForward");
			fprintf(stderr, "wrapper_cudnnSpatialTfGridGeneratorForward:%p\n", wrapper_cudnnSpatialTfGridGeneratorForward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSpatialTfGridGeneratorForward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSpatialTfGridGeneratorForward(handle, stDesc, theta, grid);
		return retval;
	}
}

