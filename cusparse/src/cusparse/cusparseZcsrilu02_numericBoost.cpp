#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZcsrilu02_numericBoost)(cusparseHandle_t, csrilu02Info_t, int, double *, cuDoubleComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZcsrilu02_numericBoost(cusparseHandle_t handle, csrilu02Info_t info, int enable_boost, double *tol, cuDoubleComplex *boost_val) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZcsrilu02_numericBoost)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZcsrilu02_numericBoost = (cusparseStatus_t (*)(cusparseHandle_t, csrilu02Info_t, int, double *, cuDoubleComplex *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZcsrilu02_numericBoost");
			fprintf(stderr, "wrapper_cusparseZcsrilu02_numericBoost:%p\n", wrapper_cusparseZcsrilu02_numericBoost);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZcsrilu02_numericBoost():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZcsrilu02_numericBoost(handle, info, enable_boost, tol, boost_val);
		return retval;
	}
}