#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetFilterSizeInBytes)(const cudnnFilterDescriptor_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetFilterSizeInBytes(const cudnnFilterDescriptor_t filterDesc, size_t *size{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetFilterSizeInBytes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetFilterSizeInBytes = (cudnnStatus_t (*)(const cudnnFilterDescriptor_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetFilterSizeInBytes");
			fprintf(stderr, "wrapper_cudnnGetFilterSizeInBytes:%p\n", wrapper_cudnnGetFilterSizeInBytes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetFilterSizeInBytes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetFilterSizeInBytes(filterDesc, size);
		return retval;
	}
}

