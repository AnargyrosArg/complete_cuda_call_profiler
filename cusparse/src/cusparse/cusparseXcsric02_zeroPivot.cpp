#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseXcsric02_zeroPivot)(cusparseHandle_t, csric02Info_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseXcsric02_zeroPivot(cusparseHandle_t handle, csric02Info_t info, int *position) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseXcsric02_zeroPivot)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseXcsric02_zeroPivot = (cusparseStatus_t (*)(cusparseHandle_t, csric02Info_t, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseXcsric02_zeroPivot");
			fprintf(stderr, "wrapper_cusparseXcsric02_zeroPivot:%p\n", wrapper_cusparseXcsric02_zeroPivot);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseXcsric02_zeroPivot():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseXcsric02_zeroPivot(handle, info, position);
		return retval;
	}
}