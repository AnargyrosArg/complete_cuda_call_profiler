#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroySpatialTransformerDescriptor)(cudnnSpatialTransformerDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroySpatialTransformerDescriptor(cudnnSpatialTransformerDescriptor_t stDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroySpatialTransformerDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroySpatialTransformerDescriptor = (cudnnStatus_t (*)(cudnnSpatialTransformerDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroySpatialTransformerDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroySpatialTransformerDescriptor:%p\n", wrapper_cudnnDestroySpatialTransformerDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroySpatialTransformerDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroySpatialTransformerDescriptor(stDesc);
		return retval;
	}
}

