#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseScsrilu02_numericBoost)(cusparseHandle_t, csrilu02Info_t, int, double *, float *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseScsrilu02_numericBoost(cusparseHandle_t handle, csrilu02Info_t info, int enable_boost, double *tol, float *boost_val) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseScsrilu02_numericBoost)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseScsrilu02_numericBoost = (cusparseStatus_t (*)(cusparseHandle_t, csrilu02Info_t, int, double *, float *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseScsrilu02_numericBoost");
			fprintf(stderr, "wrapper_cusparseScsrilu02_numericBoost:%p\n", wrapper_cusparseScsrilu02_numericBoost);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseScsrilu02_numericBoost():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseScsrilu02_numericBoost(handle, info, enable_boost, tol, boost_val);
		return retval;
	}
}