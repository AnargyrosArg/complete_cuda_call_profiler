#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSetMatDiagType)(cusparseMatDescr_t, cusparseDiagType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSetMatDiagType(cusparseMatDescr_t descrA, cusparseDiagType_t diagType) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSetMatDiagType)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSetMatDiagType = (cusparseStatus_t (*)(cusparseMatDescr_t, cusparseDiagType_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSetMatDiagType");
			fprintf(stderr, "wrapper_cusparseSetMatDiagType:%p\n", wrapper_cusparseSetMatDiagType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSetMatDiagType():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSetMatDiagType(descrA, diagType);
		return retval;
	}
}