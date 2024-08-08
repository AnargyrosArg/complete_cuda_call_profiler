#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnVecSetValues)(cusparseDnVecDescr_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnVecSetValues(cusparseDnVecDescr_t dnVecDescr, void *values) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnVecSetValues)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnVecSetValues = (cusparseStatus_t (*)(cusparseDnVecDescr_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnVecSetValues");
			fprintf(stderr, "wrapper_cusparseDnVecSetValues:%p\n", wrapper_cusparseDnVecSetValues);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnVecSetValues():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnVecSetValues(dnVecDescr, values);
		return retval;
	}
}