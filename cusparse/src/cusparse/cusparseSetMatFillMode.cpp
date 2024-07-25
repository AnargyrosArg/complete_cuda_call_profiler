#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSetMatFillMode)(cusparseMatDescr_t, cusparseFillMode_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSetMatFillMode(cusparseMatDescr_t descrA, cusparseFillMode_t fillMode) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSetMatFillMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSetMatFillMode = (cusparseStatus_t (*)(cusparseMatDescr_t, cusparseFillMode_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSetMatFillMode");
			fprintf(stderr, "wrapper_cusparseSetMatFillMode:%p\n", wrapper_cusparseSetMatFillMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSetMatFillMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSetMatFillMode(descrA, fillMode);
		return retval;
	}
}