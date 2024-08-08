#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatSetValues)(cusparseSpMatDescr_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatSetValues(cusparseSpMatDescr_t spMatDescr, void *values) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatSetValues)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatSetValues = (cusparseStatus_t (*)(cusparseSpMatDescr_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatSetValues");
			fprintf(stderr, "wrapper_cusparseSpMatSetValues:%p\n", wrapper_cusparseSpMatSetValues);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatSetValues():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatSetValues(spMatDescr, values);
		return retval;
	}
}