#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSgtsv2_nopivot)(cusparseHandle_t, int, int, const float *, const float *, const float *, float *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSgtsv2_nopivot(cusparseHandle_t handle, int m, int n, const float *dl, const float *d, const float *du, float *B, int ldb, void *pBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSgtsv2_nopivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSgtsv2_nopivot = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const float *, const float *, const float *, float *, int, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSgtsv2_nopivot");
			fprintf(stderr, "wrapper_cusparseSgtsv2_nopivot:%p\n", wrapper_cusparseSgtsv2_nopivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSgtsv2_nopivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSgtsv2_nopivot(handle, m, n, dl, d, du, B, ldb, pBuffer);
		return retval;
	}
}