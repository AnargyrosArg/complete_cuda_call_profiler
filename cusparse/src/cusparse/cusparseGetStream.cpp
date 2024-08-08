#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseGetStream)(cusparseHandle_t, cudaStream_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseGetStream(cusparseHandle_t handle, cudaStream_t *streamId) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetStream)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetStream = (cusparseStatus_t (*)(cusparseHandle_t, cudaStream_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetStream");
			fprintf(stderr, "wrapper_cusparseGetStream:%p\n", wrapper_cusparseGetStream);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetStream():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseGetStream(handle, streamId);
		return retval;
	}
}