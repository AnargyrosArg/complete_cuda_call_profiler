#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpVecSetValues)(cusparseSpVecDescr_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpVecSetValues(cusparseSpVecDescr_t spVecDescr, void *values) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpVecSetValues)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpVecSetValues = (cusparseStatus_t (*)(cusparseSpVecDescr_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpVecSetValues");
			fprintf(stderr, "wrapper_cusparseSpVecSetValues:%p\n", wrapper_cusparseSpVecSetValues);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpVecSetValues():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpVecSetValues(spVecDescr, values);
		return retval;
	}
}