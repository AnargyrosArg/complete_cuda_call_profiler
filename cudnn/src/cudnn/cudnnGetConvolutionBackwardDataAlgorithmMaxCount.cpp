#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount)(cudnnHandle_t, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionBackwardDataAlgorithmMaxCount(cudnnHandle_t handle, int *count){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount = (cudnnStatus_t (*)(cudnnHandle_t, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount");
			fprintf(stderr, "wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount:%p\n", wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionBackwardDataAlgorithmMaxCount():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionBackwardDataAlgorithmMaxCount(handle, count);
		return retval;
	}
}

