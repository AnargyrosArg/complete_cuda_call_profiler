#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseDnVecGetValues)(cusparseDnVecDescr_t, void **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseDnVecGetValues(cusparseDnVecDescr_t dnVecDescr, void **values) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseDnVecGetValues)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseDnVecGetValues = (cusparseStatus_t (*)(cusparseDnVecDescr_t, void **)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseDnVecGetValues");
			fprintf(stderr, "wrapper_cusparseDnVecGetValues:%p\n", wrapper_cusparseDnVecGetValues);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseDnVecGetValues():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseDnVecGetValues(dnVecDescr, values);
		return retval;
	}
}