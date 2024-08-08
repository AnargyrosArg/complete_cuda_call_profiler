#include <cudnn_cnn_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetConvolutionNdDescriptor)(const cudnnConvolutionDescriptor_t, int, int *, int *, int *, int *, cudnnConvolutionMode_t *, cudnnDataType_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetConvolutionNdDescriptor(const cudnnConvolutionDescriptor_t convDesc, int arrayLengthRequested, int *arrayLength, int padA[], int strideA[], int dilationA[], cudnnConvolutionMode_t *mode, cudnnDataType_t *computeType){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetConvolutionNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetConvolutionNdDescriptor = (cudnnStatus_t (*)(const cudnnConvolutionDescriptor_t, int, int *, int *, int *, int *, cudnnConvolutionMode_t *, cudnnDataType_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetConvolutionNdDescriptor");
			fprintf(stderr, "wrapper_cudnnGetConvolutionNdDescriptor:%p\n", wrapper_cudnnGetConvolutionNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetConvolutionNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetConvolutionNdDescriptor(convDesc, arrayLengthRequested, arrayLength, padA, strideA, dilationA, mode, computeType);
		return retval;
	}
}

