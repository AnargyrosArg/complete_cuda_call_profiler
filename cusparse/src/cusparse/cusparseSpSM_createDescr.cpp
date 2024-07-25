#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpSM_createDescr)(cusparseSpSMDescr_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpSM_createDescr(cusparseSpSMDescr_t *descr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpSM_createDescr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpSM_createDescr = (cusparseStatus_t (*)(cusparseSpSMDescr_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpSM_createDescr");
			fprintf(stderr, "wrapper_cusparseSpSM_createDescr:%p\n", wrapper_cusparseSpSM_createDescr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpSM_createDescr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpSM_createDescr(descr);
		return retval;
	}
}