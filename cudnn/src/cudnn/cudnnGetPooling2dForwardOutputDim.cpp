#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetPooling2dForwardOutputDim)(const cudnnPoolingDescriptor_t, const cudnnTensorDescriptor_t, int *, int *, int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetPooling2dForwardOutputDim(const cudnnPoolingDescriptor_t poolingDesc, const cudnnTensorDescriptor_t inputTensorDesc, int *n, int *c, int *h, int *w) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetPooling2dForwardOutputDim)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetPooling2dForwardOutputDim = (cudnnStatus_t (*)(const cudnnPoolingDescriptor_t, const cudnnTensorDescriptor_t, int *, int *, int *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetPooling2dForwardOutputDim");
			fprintf(stderr, "wrapper_cudnnGetPooling2dForwardOutputDim:%p\n", wrapper_cudnnGetPooling2dForwardOutputDim);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetPooling2dForwardOutputDim():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetPooling2dForwardOutputDim(poolingDesc, inputTensorDesc, n, c, h, w);
		return retval;
	}
}

