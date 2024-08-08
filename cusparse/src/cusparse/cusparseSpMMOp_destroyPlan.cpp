#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMMOp_destroyPlan)(cusparseSpMMOpPlan_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMMOp_destroyPlan(cusparseSpMMOpPlan_t plan) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMMOp_destroyPlan)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMMOp_destroyPlan = (cusparseStatus_t (*)(cusparseSpMMOpPlan_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMMOp_destroyPlan");
			fprintf(stderr, "wrapper_cusparseSpMMOp_destroyPlan:%p\n", wrapper_cusparseSpMMOp_destroyPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMMOp_destroyPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMMOp_destroyPlan(plan);
		return retval;
	}
}