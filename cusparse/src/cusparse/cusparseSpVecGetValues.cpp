#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpVecGetValues)(cusparseSpVecDescr_t, void **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpVecGetValues(cusparseSpVecDescr_t spVecDescr, void **values) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpVecGetValues)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpVecGetValues = (cusparseStatus_t (*)(cusparseSpVecDescr_t, void **)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpVecGetValues");
			fprintf(stderr, "wrapper_cusparseSpVecGetValues:%p\n", wrapper_cusparseSpVecGetValues);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpVecGetValues():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpVecGetValues(spVecDescr, values);
		return retval;
	}
}