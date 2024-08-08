#include <cudnn_backend.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBackendSetAttribute)(cudnnBackendDescriptor_t, cudnnBackendAttributeName_t, cudnnBackendAttributeType_t, int64_t, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBackendSetAttribute(cudnnBackendDescriptor_t descriptor, cudnnBackendAttributeName_t attributeName, cudnnBackendAttributeType_t attributeType, int64_t elementCount, const void *arrayOfElements{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBackendSetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBackendSetAttribute = (cudnnStatus_t (*)(cudnnBackendDescriptor_t, cudnnBackendAttributeName_t, cudnnBackendAttributeType_t, int64_t, const void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBackendSetAttribute");
			fprintf(stderr, "wrapper_cudnnBackendSetAttribute:%p\n", wrapper_cudnnBackendSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBackendSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBackendSetAttribute(descriptor, attributeName, attributeType, elementCount, arrayOfElements);
		return retval;
	}
}

