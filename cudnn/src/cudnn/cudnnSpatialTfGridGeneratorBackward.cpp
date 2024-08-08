#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSpatialTfGridGeneratorBackward)(cudnnHandle_t, const cudnnSpatialTransformerDescriptor_t, const void *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSpatialTfGridGeneratorBackward(cudnnHandle_t handle, const cudnnSpatialTransformerDescriptor_t stDesc, const void *dgrid, void *dtheta{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSpatialTfGridGeneratorBackward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSpatialTfGridGeneratorBackward = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnSpatialTransformerDescriptor_t, const void *, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSpatialTfGridGeneratorBackward");
			fprintf(stderr, "wrapper_cudnnSpatialTfGridGeneratorBackward:%p\n", wrapper_cudnnSpatialTfGridGeneratorBackward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSpatialTfGridGeneratorBackward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSpatialTfGridGeneratorBackward(handle, stDesc, dgrid, dtheta);
		return retval;
	}
}

