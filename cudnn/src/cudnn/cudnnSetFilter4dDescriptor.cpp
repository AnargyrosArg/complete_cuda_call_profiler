#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetFilter4dDescriptor)(cudnnFilterDescriptor_t, cudnnDataType_t, cudnnTensorFormat_t, int, int, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetFilter4dDescriptor(cudnnFilterDescriptor_t filterDesc, cudnnDataType_t dataType, cudnnTensorFormat_t format, int k, int c, int h, int w) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetFilter4dDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetFilter4dDescriptor = (cudnnStatus_t (*)(cudnnFilterDescriptor_t, cudnnDataType_t, cudnnTensorFormat_t, int, int, int, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetFilter4dDescriptor");
			fprintf(stderr, "wrapper_cudnnSetFilter4dDescriptor:%p\n", wrapper_cudnnSetFilter4dDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetFilter4dDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetFilter4dDescriptor(filterDesc, dataType, format, k, c, h, w);
		return retval;
	}
}

