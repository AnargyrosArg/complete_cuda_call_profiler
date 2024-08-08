#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetPooling2dDescriptor)(const cudnnPoolingDescriptor_t, cudnnPoolingMode_t *, cudnnNanPropagation_t *, int *, int *, int *, int *, int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetPooling2dDescriptor(const cudnnPoolingDescriptor_t poolingDesc, cudnnPoolingMode_t *mode, cudnnNanPropagation_t *maxpoolingNanOpt, int *windowHeight, int *windowWidth, int *verticalPadding, int *horizontalPadding, int *verticalStride, int *horizontalStride{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetPooling2dDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetPooling2dDescriptor = (cudnnStatus_t (*)(const cudnnPoolingDescriptor_t, cudnnPoolingMode_t *, cudnnNanPropagation_t *, int *, int *, int *, int *, int *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetPooling2dDescriptor");
			fprintf(stderr, "wrapper_cudnnGetPooling2dDescriptor:%p\n", wrapper_cudnnGetPooling2dDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetPooling2dDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetPooling2dDescriptor(poolingDesc, mode, maxpoolingNanOpt, windowHeight, windowWidth, verticalPadding, horizontalPadding, verticalStride, horizontalStride);
		return retval;
	}
}

