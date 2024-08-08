#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateSpatialTransformerDescriptor)(cudnnSpatialTransformerDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateSpatialTransformerDescriptor(cudnnSpatialTransformerDescriptor_t *stDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateSpatialTransformerDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateSpatialTransformerDescriptor = (cudnnStatus_t (*)(cudnnSpatialTransformerDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateSpatialTransformerDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateSpatialTransformerDescriptor:%p\n", wrapper_cudnnCreateSpatialTransformerDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateSpatialTransformerDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateSpatialTransformerDescriptor(stDesc);
		return retval;
	}
}

