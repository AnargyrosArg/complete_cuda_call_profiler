#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetMultiHeadAttnWeights)(cudnnHandle_t, const cudnnAttnDescriptor_t, cudnnMultiHeadAttnWeightKind_t, size_t, const void *, cudnnTensorDescriptor_t, void **);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetMultiHeadAttnWeights(cudnnHandle_t handle, const cudnnAttnDescriptor_t attnDesc, cudnnMultiHeadAttnWeightKind_t wKind, size_t weightSizeInBytes, const void *weights, cudnnTensorDescriptor_t wDesc, void **wAddr){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetMultiHeadAttnWeights)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetMultiHeadAttnWeights = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnAttnDescriptor_t, cudnnMultiHeadAttnWeightKind_t, size_t, const void *, cudnnTensorDescriptor_t, void **)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetMultiHeadAttnWeights");
			fprintf(stderr, "wrapper_cudnnGetMultiHeadAttnWeights:%p\n", wrapper_cudnnGetMultiHeadAttnWeights);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetMultiHeadAttnWeights():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetMultiHeadAttnWeights(handle, attnDesc, wKind, weightSizeInBytes, weights, wDesc, wAddr);
		return retval;
	}
}

