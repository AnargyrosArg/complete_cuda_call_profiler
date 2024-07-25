#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMMOp)(cusparseSpMMOpPlan_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMMOp(cusparseSpMMOpPlan_t plan, void *externalBuffer) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMMOp)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMMOp = (cusparseStatus_t (*)(cusparseSpMMOpPlan_t, void *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMMOp");
			fprintf(stderr, "wrapper_cusparseSpMMOp:%p\n", wrapper_cusparseSpMMOp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMMOp():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMMOp(plan, externalBuffer);
		return retval;
	}
}