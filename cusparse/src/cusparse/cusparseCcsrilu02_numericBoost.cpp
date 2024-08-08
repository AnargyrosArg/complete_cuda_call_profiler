#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCcsrilu02_numericBoost)(cusparseHandle_t, csrilu02Info_t, int, double *, cuComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCcsrilu02_numericBoost(cusparseHandle_t handle, csrilu02Info_t info, int enable_boost, double *tol, cuComplex *boost_val) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCcsrilu02_numericBoost)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCcsrilu02_numericBoost = (cusparseStatus_t (*)(cusparseHandle_t, csrilu02Info_t, int, double *, cuComplex *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCcsrilu02_numericBoost");
			fprintf(stderr, "wrapper_cusparseCcsrilu02_numericBoost:%p\n", wrapper_cusparseCcsrilu02_numericBoost);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCcsrilu02_numericBoost():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCcsrilu02_numericBoost(handle, info, enable_boost, tol, boost_val);
		return retval;
	}
}