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

// BYTE 32

FmIndexByte32* construct_byte32(const char* path, size_t path_len, size_t width) {
	// Convert path to string.
	string path_str         = string(path, path_len);
	FmIndexByte32* fm_index = new FmIndexByte32;
	// Assume 1-byte alphabet always.
	construct(*fm_index, path_str, width);
	return fm_index;
}

void destruct_fm_index_byte32(FmIndexByte32* fm_index) {
	delete fm_index;
}

size_t count_byte32(const FmIndexByte32* fm_index, const uint8_t* pattern, size_t pattern_len) {
	return count(*fm_index, pattern, pattern + pattern_len);
}

size_t size_in_bytes_byte32(const FmIndexByte32* fm_index) {
	return size_in_bytes(*fm_index);
}

LocateResult* locate_byte32(const FmIndexByte32* fm_index, const uint8_t* pattern,
                            size_t pattern_len) {
	LocateResult r       = locate(*fm_index, pattern, pattern + pattern_len);
	LocateResult* result = new LocateResult(r);
	return result;
}

// INT 32

FmIndexInt32* construct_int32(const char* path, size_t path_len, size_t width) {
	// Convert path to string.
	string path_str        = string(path, path_len);
	FmIndexInt32* fm_index = new FmIndexInt32;
	// Assume 1-byte alphabet always.
	construct(*fm_index, path_str, width);
	return fm_index;
}

void destruct_fm_index_int32(FmIndexInt32* fm_index) {
	delete fm_index;
}

size_t count_int32(const FmIndexInt32* fm_index, const uint64_t* pattern, size_t pattern_len) {
	return count(*fm_index, pattern, pattern + pattern_len);
}

size_t size_in_bytes_int32(const FmIndexInt32* fm_index) {
	return size_in_bytes(*fm_index);
}

LocateResult* locate_int32(const FmIndexInt32* fm_index, const uint64_t* pattern,
                           size_t pattern_len) {
	LocateResult r       = locate(*fm_index, pattern, pattern + pattern_len);
	LocateResult* result = new LocateResult(r);
	return result;
}

// BYTE 64

FmIndexByte64* construct_byte64(const char* path, size_t path_len, size_t width) {
	// Convert path to string.
	string path_str         = string(path, path_len);
	FmIndexByte64* fm_index = new FmIndexByte64;
	// Assume 1-byte alphabet always.
	construct(*fm_index, path_str, width);
	return fm_index;
}

void destruct_fm_index_byte64(FmIndexByte64* fm_index) {
	delete fm_index;
}

size_t count_byte64(const FmIndexByte64* fm_index, const uint8_t* pattern, size_t pattern_len) {
	return count(*fm_index, pattern, pattern + pattern_len);
}

size_t size_in_bytes_byte64(const FmIndexByte64* fm_index) {
	return size_in_bytes(*fm_index);
}

LocateResult* locate_byte64(const FmIndexByte64* fm_index, const uint8_t* pattern,
                            size_t pattern_len) {
	LocateResult r       = locate(*fm_index, pattern, pattern + pattern_len);
	LocateResult* result = new LocateResult(r);
	return result;
}

// INT 64

FmIndexInt64* construct_int64(const char* path, size_t path_len, size_t width) {
	// Convert path to string.
	string path_str        = string(path, path_len);
	FmIndexInt64* fm_index = new FmIndexInt64;
	// Assume 1-byte alphabet always.
	construct(*fm_index, path_str, width);
	return fm_index;
}

void destruct_fm_index_int64(FmIndexInt64* fm_index) {
	delete fm_index;
}

size_t count_int64(const FmIndexInt64* fm_index, const uint64_t* pattern, size_t pattern_len) {
	return count(*fm_index, pattern, pattern + pattern_len);
}

size_t size_in_bytes_int64(const FmIndexInt64* fm_index) {
	return size_in_bytes(*fm_index);
}

LocateResult* locate_int64(const FmIndexInt64* fm_index, const uint64_t* pattern,
                           size_t pattern_len) {
	LocateResult r       = locate(*fm_index, pattern, pattern + pattern_len);
	LocateResult* result = new LocateResult(r);
	return result;
}

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
