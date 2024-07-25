#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseGetVersion)(cusparseHandle_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseGetVersion(cusparseHandle_t handle, int *version) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseGetVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseGetVersion = (cusparseStatus_t (*)(cusparseHandle_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseGetVersion");
			fprintf(stderr, "wrapper_cusparseGetVersion:%p\n", wrapper_cusparseGetVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseGetVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseGetVersion(handle, version);
		return retval;
	}
}