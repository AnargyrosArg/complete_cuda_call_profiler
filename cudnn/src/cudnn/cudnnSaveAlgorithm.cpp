#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSaveAlgorithm)(cudnnHandle_t, cudnnAlgorithmDescriptor_t, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSaveAlgorithm(cudnnHandle_t handle, cudnnAlgorithmDescriptor_t algoDesc, void *algoSpace, size_t algoSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSaveAlgorithm)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSaveAlgorithm = (cudnnStatus_t (*)(cudnnHandle_t, cudnnAlgorithmDescriptor_t, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSaveAlgorithm");
			fprintf(stderr, "wrapper_cudnnSaveAlgorithm:%p\n", wrapper_cudnnSaveAlgorithm);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSaveAlgorithm():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSaveAlgorithm(handle, algoDesc, algoSpace, algoSpaceSizeInBytes);
		return retval;
	}
}

