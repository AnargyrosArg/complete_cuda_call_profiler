#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDestroyCsrsm2Info)(csrsm2Info_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDestroyCsrsm2Info(csrsm2Info_t info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDestroyCsrsm2Info)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDestroyCsrsm2Info = (cusparseStatus_t (*)(csrsm2Info_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDestroyCsrsm2Info");
			fprintf(stderr, "wrapper_cusparseDestroyCsrsm2Info:%p\n", wrapper_cusparseDestroyCsrsm2Info);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDestroyCsrsm2Info():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDestroyCsrsm2Info(info);
		return retval;
	}
}