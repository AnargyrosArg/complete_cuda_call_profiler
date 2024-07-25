#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpSM_destroyDescr)(cusparseSpSMDescr_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpSM_destroyDescr(cusparseSpSMDescr_t descr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpSM_destroyDescr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpSM_destroyDescr = (cusparseStatus_t (*)(cusparseSpSMDescr_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpSM_destroyDescr");
			fprintf(stderr, "wrapper_cusparseSpSM_destroyDescr:%p\n", wrapper_cusparseSpSM_destroyDescr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpSM_destroyDescr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpSM_destroyDescr(descr);
		return retval;
	}
}