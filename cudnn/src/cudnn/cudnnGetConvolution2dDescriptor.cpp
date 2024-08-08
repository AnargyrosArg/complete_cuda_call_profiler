#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolution2dDescriptor)(const cudnnConvolutionDescriptor_t, int *, int *, int *, int *, int *, int *, cudnnConvolutionMode_t *, cudnnDataType_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolution2dDescriptor(const cudnnConvolutionDescriptor_t convDesc, int *pad_h, int *pad_w, int *u, int *v, int *dilation_h, int *dilation_w, cudnnConvolutionMode_t *mode, cudnnDataType_t *computeType{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolution2dDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolution2dDescriptor = (cudnnStatus_t (*)(const cudnnConvolutionDescriptor_t, int *, int *, int *, int *, int *, int *, cudnnConvolutionMode_t *, cudnnDataType_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolution2dDescriptor");
			fprintf(stderr, "wrapper_cudnnGetConvolution2dDescriptor:%p\n", wrapper_cudnnGetConvolution2dDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolution2dDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolution2dDescriptor(convDesc, pad_h, pad_w, u, v, dilation_h, dilation_w, mode, computeType);
		return retval;
	}
}

