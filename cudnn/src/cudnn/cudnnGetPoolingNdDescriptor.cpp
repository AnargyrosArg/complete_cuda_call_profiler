#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetPoolingNdDescriptor)(const cudnnPoolingDescriptor_t, int, cudnnPoolingMode_t *, cudnnNanPropagation_t *, int *, int *, int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetPoolingNdDescriptor(const cudnnPoolingDescriptor_t poolingDesc, int nbDimsRequested, cudnnPoolingMode_t *mode, cudnnNanPropagation_t *maxpoolingNanOpt, int *nbDims, int windowDimA[], int paddingA[], int strideA[]) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetPoolingNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetPoolingNdDescriptor = (cudnnStatus_t (*)(const cudnnPoolingDescriptor_t, int, cudnnPoolingMode_t *, cudnnNanPropagation_t *, int *, int *, int *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetPoolingNdDescriptor");
			fprintf(stderr, "wrapper_cudnnGetPoolingNdDescriptor:%p\n", wrapper_cudnnGetPoolingNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetPoolingNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetPoolingNdDescriptor(poolingDesc, nbDimsRequested, mode, maxpoolingNanOpt, nbDims, windowDimA, paddingA, strideA);
		return retval;
	}
}

