#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDropoutBackward)(cudnnHandle_t, const cudnnDropoutDescriptor_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDropoutBackward(cudnnHandle_t handle, const cudnnDropoutDescriptor_t dropoutDesc, const cudnnTensorDescriptor_t dydesc, const void *dy, const cudnnTensorDescriptor_t dxdesc, void *dx, void *reserveSpace, size_t reserveSpaceSizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDropoutBackward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDropoutBackward = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnDropoutDescriptor_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDropoutBackward");
			fprintf(stderr, "wrapper_cudnnDropoutBackward:%p\n", wrapper_cudnnDropoutBackward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDropoutBackward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDropoutBackward(handle, dropoutDesc, dydesc, dy, dxdesc, dx, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

