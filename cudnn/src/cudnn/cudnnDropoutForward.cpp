#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDropoutForward)(cudnnHandle_t, const cudnnDropoutDescriptor_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDropoutForward(cudnnHandle_t handle, const cudnnDropoutDescriptor_t dropoutDesc, const cudnnTensorDescriptor_t xdesc, const void *x, const cudnnTensorDescriptor_t ydesc, void *y, void *reserveSpace, size_t reserveSpaceSizeInBytes{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDropoutForward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDropoutForward = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnDropoutDescriptor_t, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDropoutForward");
			fprintf(stderr, "wrapper_cudnnDropoutForward:%p\n", wrapper_cudnnDropoutForward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDropoutForward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDropoutForward(handle, dropoutDesc, xdesc, x, ydesc, y, reserveSpace, reserveSpaceSizeInBytes);
		return retval;
	}
}

