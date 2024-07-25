#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetSpatialTransformerNdDescriptor)(cudnnSpatialTransformerDescriptor_t, cudnnSamplerType_t, cudnnDataType_t, const int, const int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetSpatialTransformerNdDescriptor(cudnnSpatialTransformerDescriptor_t stDesc, cudnnSamplerType_t samplerType, cudnnDataType_t dataType, const int nbDims, const int dimA[]) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetSpatialTransformerNdDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetSpatialTransformerNdDescriptor = (cudnnStatus_t (*)(cudnnSpatialTransformerDescriptor_t, cudnnSamplerType_t, cudnnDataType_t, const int, const int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetSpatialTransformerNdDescriptor");
			fprintf(stderr, "wrapper_cudnnSetSpatialTransformerNdDescriptor:%p\n", wrapper_cudnnSetSpatialTransformerNdDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetSpatialTransformerNdDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetSpatialTransformerNdDescriptor(stDesc, samplerType, dataType, nbDims, dimA);
		return retval;
	}
}

