#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetProperty)(libraryPropertyType, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetProperty(libraryPropertyType type, int *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetProperty)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetProperty = (cudnnStatus_t (*)(libraryPropertyType, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetProperty");
			fprintf(stderr, "wrapper_cudnnGetProperty:%p\n", wrapper_cudnnGetProperty);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetProperty():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetProperty(type, value);
		return retval;
	}
}

