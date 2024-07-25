#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSetMatType)(cusparseMatDescr_t, cusparseMatrixType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSetMatType(cusparseMatDescr_t descrA, cusparseMatrixType_t type) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSetMatType)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSetMatType = (cusparseStatus_t (*)(cusparseMatDescr_t, cusparseMatrixType_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSetMatType");
			fprintf(stderr, "wrapper_cusparseSetMatType:%p\n", wrapper_cusparseSetMatType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSetMatType():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSetMatType(descrA, type);
		return retval;
	}
}