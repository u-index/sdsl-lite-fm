#include <sdsl/suffix_arrays.hpp>
#include <string>

using namespace sdsl;
using namespace std;

extern "C" {

// Parameter values: rrr block size which has 63 as default.
// SA sampling: either 32 (default) or 64
// Inverse SA sampling: either 64 (default) or 128. (Should be unused, but idk.)
using FmIndexByte32 = csa_wt<wt_huff<rrr_vector<63>>, 32, 64>;
using FmIndexInt32  = csa_wt<wt_int<rrr_vector<63>>, 32, 64>;
using FmIndexByte64 = csa_wt<wt_huff<rrr_vector<63>>, 64, 128>;
using FmIndexInt64  = csa_wt<wt_int<rrr_vector<63>>, 64, 128>;
using LocateResult  = int_vector<64>;

// macros generated with the help of AI slop
#define CONSTRUCT_FM_WITH_TYPE(TOKEN_LC, TOKEN_CAP) \
  	void* construct_##TOKEN_LC(const char* path, size_t path_len, size_t width) { \
        std::string path_str = std::string(path, path_len);        \
        FmIndex##TOKEN_CAP* fm_index = new FmIndex##TOKEN_CAP;     \
        construct(*fm_index, path_str, width);                     \
        return fm_index;                                           \
    }

#define DESTRUCT_FM_WITH_TYPE(TOKEN_LC, TOKEN_CAP)                    \
    void destruct_fm_index_##TOKEN_LC(FmIndex##TOKEN_CAP* fm_index) { \
    		delete fm_index;                                              \
    }

#define COUNT_WITH_TYPE(TOKEN_LC, TOKEN_CAP, PATTERN_TY)                               \
    size_t count_##TOKEN_LC(const FmIndex##TOKEN_CAP* fm_index, const PATTERN_TY* pattern, size_t pattern_len) { \
    		return count(*fm_index, pattern, pattern + pattern_len);                        \
    }

#define SIZE_IN_BYTES_WITH_TYPE(TOKEN_LC, TOKEN_CAP)                               \
    size_t size_in_bytes_##TOKEN_LC(const FmIndex##TOKEN_CAP* fm_index) { 				 \
    		return size_in_bytes(*fm_index); 																					 \
    }

#define LOCATE_WITH_TYPE(TOKEN_LC, TOKEN_CAP, PATTERN_TY)                               \
    LocateResult* locate_##TOKEN_LC(const FmIndex##TOKEN_CAP* fm_index, const PATTERN_TY* pattern, size_t pattern_len) { \
    		LocateResult r = locate(*fm_index, pattern, pattern + pattern_len); \
    		LocateResult* result = new LocateResult(r); 												\
				return result; 																											\
    }

CONSTRUCT_FM_WITH_TYPE(byte32, Byte32);
CONSTRUCT_FM_WITH_TYPE(int32, Int32);
CONSTRUCT_FM_WITH_TYPE(byte64, Byte64);
CONSTRUCT_FM_WITH_TYPE(int64, Int64);

DESTRUCT_FM_WITH_TYPE(byte32, Byte32);
DESTRUCT_FM_WITH_TYPE(int32, Int32);
DESTRUCT_FM_WITH_TYPE(byte64, Byte64);
DESTRUCT_FM_WITH_TYPE(int64, Int64);

COUNT_WITH_TYPE(byte32, Byte32, uint8_t);
COUNT_WITH_TYPE(int32, Int32, uint64_t);
COUNT_WITH_TYPE(byte64, Byte64, uint8_t);
COUNT_WITH_TYPE(int64, Int64, uint64_t);

SIZE_IN_BYTES_WITH_TYPE(byte32, Byte32);
SIZE_IN_BYTES_WITH_TYPE(int32, Int32);
SIZE_IN_BYTES_WITH_TYPE(byte64, Byte64);
SIZE_IN_BYTES_WITH_TYPE(int64, Int64);

LOCATE_WITH_TYPE(byte32, Byte32, uint8_t);
LOCATE_WITH_TYPE(int32, Int32, uint64_t);
LOCATE_WITH_TYPE(byte64, Byte64, uint8_t);
LOCATE_WITH_TYPE(int64, Int64, uint64_t);

// LOCATE

size_t locate_len(const LocateResult* locate_result) {
	return locate_result->size();
}

size_t locate_get(const LocateResult* locate_result, size_t index) {
	return (*locate_result)[index];
}

void destruct_locate_result(LocateResult* locate_result) {
	delete locate_result;
}
}
