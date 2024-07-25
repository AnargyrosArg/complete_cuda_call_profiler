#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseBlockedEllGet)(cusparseSpMatDescr_t, int64_t *, int64_t *, int64_t *, int64_t *, void **, void **, cusparseIndexType_t *, cusparseIndexBase_t *, cudaDataType *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseBlockedEllGet(cusparseSpMatDescr_t spMatDescr, int64_t *rows, int64_t *cols, int64_t *ellBlockSize, int64_t *ellCols, void **ellColInd, void **ellValue, cusparseIndexType_t *ellIdxType, cusparseIndexBase_t *idxBase, cudaDataType *valueType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseBlockedEllGet)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseBlockedEllGet = (cusparseStatus_t (*)(cusparseSpMatDescr_t, int64_t *, int64_t *, int64_t *, int64_t *, void **, void **, cusparseIndexType_t *, cusparseIndexBase_t *, cudaDataType *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseBlockedEllGet");
			fprintf(stderr, "wrapper_cusparseBlockedEllGet:%p\n", wrapper_cusparseBlockedEllGet);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseBlockedEllGet():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseBlockedEllGet(spMatDescr, rows, cols, ellBlockSize, ellCols, ellColInd, ellValue, ellIdxType, idxBase, valueType);
		return retval;
	}
}