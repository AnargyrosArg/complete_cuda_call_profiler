#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXbsric02_zeroPivot)(cusparseHandle_t, bsric02Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXbsric02_zeroPivot(cusparseHandle_t handle, bsric02Info_t info, int *position) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXbsric02_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXbsric02_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, bsric02Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXbsric02_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXbsric02_zeroPivot:%p\n", wrapper_cusparseXbsric02_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXbsric02_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXbsric02_zeroPivot(handle, info, position);
		return retval;
	}
}