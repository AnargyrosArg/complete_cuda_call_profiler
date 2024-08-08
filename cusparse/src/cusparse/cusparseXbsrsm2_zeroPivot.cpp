#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXbsrsm2_zeroPivot)(cusparseHandle_t, bsrsm2Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXbsrsm2_zeroPivot(cusparseHandle_t handle, bsrsm2Info_t info, int *position) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXbsrsm2_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXbsrsm2_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, bsrsm2Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXbsrsm2_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXbsrsm2_zeroPivot:%p\n", wrapper_cusparseXbsrsm2_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXbsrsm2_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXbsrsm2_zeroPivot(handle, info, position);
		return retval;
	}
}