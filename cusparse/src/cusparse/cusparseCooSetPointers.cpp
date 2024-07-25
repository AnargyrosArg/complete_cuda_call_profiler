#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCooSetPointers)(cusparseSpMatDescr_t, void *, void *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCooSetPointers(cusparseSpMatDescr_t spMatDescr, void *cooRows, void *cooColumns, void *cooValues) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCooSetPointers)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCooSetPointers = (cusparseStatus_t (*)(cusparseSpMatDescr_t, void *, void *, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCooSetPointers");
			fprintf(stderr, "wrapper_cusparseCooSetPointers:%p\n", wrapper_cusparseCooSetPointers);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCooSetPointers():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCooSetPointers(spMatDescr, cooRows, cooColumns, cooValues);
		return retval;
	}
}