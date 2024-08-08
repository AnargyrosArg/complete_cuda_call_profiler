#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXbsrilu02_zeroPivot)(cusparseHandle_t, bsrilu02Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXbsrilu02_zeroPivot(cusparseHandle_t handle, bsrilu02Info_t info, int *position) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXbsrilu02_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXbsrilu02_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, bsrilu02Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXbsrilu02_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXbsrilu02_zeroPivot:%p\n", wrapper_cusparseXbsrilu02_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXbsrilu02_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXbsrilu02_zeroPivot(handle, info, position);
		return retval;
	}
}