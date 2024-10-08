#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateTensorTransformDescriptor)(cudnnTensorTransformDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateTensorTransformDescriptor(cudnnTensorTransformDescriptor_t *transformDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateTensorTransformDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateTensorTransformDescriptor = (cudnnStatus_t (*)(cudnnTensorTransformDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateTensorTransformDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateTensorTransformDescriptor:%p\n", wrapper_cudnnCreateTensorTransformDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateTensorTransformDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateTensorTransformDescriptor(transformDesc);
		return retval;
	}
}

