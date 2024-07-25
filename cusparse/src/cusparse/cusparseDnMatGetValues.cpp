#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnMatGetValues)(cusparseDnMatDescr_t, void **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnMatGetValues(cusparseDnMatDescr_t dnMatDescr, void **values) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnMatGetValues)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnMatGetValues = (cusparseStatus_t (*)(cusparseDnMatDescr_t, void **)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnMatGetValues");
			fprintf(stderr, "wrapper_cusparseDnMatGetValues:%p\n", wrapper_cusparseDnMatGetValues);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnMatGetValues():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnMatGetValues(dnMatDescr, values);
		return retval;
	}
}