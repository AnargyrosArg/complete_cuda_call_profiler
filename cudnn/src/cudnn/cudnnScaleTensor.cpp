#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnScaleTensor)(cudnnHandle_t, const cudnnTensorDescriptor_t, void *, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnScaleTensor(cudnnHandle_t handle, const cudnnTensorDescriptor_t yDesc, void *y, const void *alpha){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnScaleTensor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnScaleTensor = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, void *, const void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnScaleTensor");
			fprintf(stderr, "wrapper_cudnnScaleTensor:%p\n", wrapper_cudnnScaleTensor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnScaleTensor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnScaleTensor(handle, yDesc, y, alpha);
		return retval;
	}
}

