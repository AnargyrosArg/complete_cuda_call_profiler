#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnMatSetValues)(cusparseDnMatDescr_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnMatSetValues(cusparseDnMatDescr_t dnMatDescr, void *values) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnMatSetValues)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnMatSetValues = (cusparseStatus_t (*)(cusparseDnMatDescr_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnMatSetValues");
			fprintf(stderr, "wrapper_cusparseDnMatSetValues:%p\n", wrapper_cusparseDnMatSetValues);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnMatSetValues():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnMatSetValues(dnMatDescr, values);
		return retval;
	}
}