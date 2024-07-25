#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSetMatIndexBase)(cusparseMatDescr_t, cusparseIndexBase_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSetMatIndexBase(cusparseMatDescr_t descrA, cusparseIndexBase_t base) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSetMatIndexBase)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSetMatIndexBase = (cusparseStatus_t (*)(cusparseMatDescr_t, cusparseIndexBase_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSetMatIndexBase");
			fprintf(stderr, "wrapper_cusparseSetMatIndexBase:%p\n", wrapper_cusparseSetMatIndexBase);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSetMatIndexBase():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSetMatIndexBase(descrA, base);
		return retval;
	}
}