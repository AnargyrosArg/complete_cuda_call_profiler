#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateMatDescr)(cusparseMatDescr_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateMatDescr(cusparseMatDescr_t *descrA) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateMatDescr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateMatDescr = (cusparseStatus_t (*)(cusparseMatDescr_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateMatDescr");
			fprintf(stderr, "wrapper_cusparseCreateMatDescr:%p\n", wrapper_cusparseCreateMatDescr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateMatDescr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateMatDescr(descrA);
		return retval;
	}
}