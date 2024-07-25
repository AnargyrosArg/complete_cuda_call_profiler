#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSetStream)(cusparseHandle_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSetStream(cusparseHandle_t handle, cudaStream_t streamId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSetStream)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSetStream = (cusparseStatus_t (*)(cusparseHandle_t, cudaStream_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSetStream");
			fprintf(stderr, "wrapper_cusparseSetStream:%p\n", wrapper_cusparseSetStream);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSetStream():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSetStream(handle, streamId);
		return retval;
	}
}