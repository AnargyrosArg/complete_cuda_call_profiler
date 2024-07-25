#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnIm2Col)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const cudnnConvolutionDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnIm2Col(cudnnHandle_t handle, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnFilterDescriptor_t wDesc, const cudnnConvolutionDescriptor_t convDesc, void *colBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnIm2Col)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnIm2Col = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const cudnnFilterDescriptor_t, const cudnnConvolutionDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnIm2Col");
			fprintf(stderr, "wrapper_cudnnIm2Col:%p\n", wrapper_cudnnIm2Col);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnIm2Col():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnIm2Col(handle, xDesc, x, wDesc, convDesc, colBuffer);
		return retval;
	}
}

