unsafe extern "C" {
    pub fn test(x: usize) -> usize;
}

#[repr(C)]
struct FmIndexInt32 {
    _data: [u8; 0],
    _marker: core::marker::PhantomData<(*mut u8, core::marker::PhantomPinned)>,
}

#[repr(C)]
struct FmIndexByte32 {
    _data: [u8; 0],
    _marker: core::marker::PhantomData<(*mut u8, core::marker::PhantomPinned)>,
}

#[repr(C)]
struct FmIndexInt64 {
    _data: [u8; 0],
    _marker: core::marker::PhantomData<(*mut u8, core::marker::PhantomPinned)>,
}

#[repr(C)]
struct FmIndexByte64 {
    _data: [u8; 0],
    _marker: core::marker::PhantomData<(*mut u8, core::marker::PhantomPinned)>,
}

#[repr(C)]
pub struct LocateResult {
    _data: [u8; 0],
    _marker: core::marker::PhantomData<(*mut u8, core::marker::PhantomPinned)>,
}

unsafe extern "C" {
    // BYTE 32
    fn construct_byte32(path: *const u8, path_len: usize, width: usize) -> *const FmIndexByte32;
    fn destruct_fm_index_byte32(fm_index: *const FmIndexByte32);
    fn count_byte32(
        fm_index: *const FmIndexByte32,
        pattern: *const u8,
        pattern_len: usize,
    ) -> usize;
    fn size_in_bytes_byte32(fm_index: *const FmIndexByte32) -> usize;
    fn locate_byte32(
        fm_index: *const FmIndexByte32,
        pattern: *const u8,
        pattern_len: usize,
    ) -> *const LocateResult;

    // INT 32
    fn construct_int32(path: *const u8, path_len: usize, width: usize) -> *const FmIndexInt32;
    fn destruct_fm_index_int32(fm_index: *const FmIndexInt32);
    fn count_int32(fm_index: *const FmIndexInt32, pattern: *const u64, pattern_len: usize)
        -> usize;
    fn size_in_bytes_int32(fm_index: *const FmIndexInt32) -> usize;
    fn locate_int32(
        fm_index: *const FmIndexInt32,
        pattern: *const u64,
        pattern_len: usize,
    ) -> *const LocateResult;

    // BYTE 64
    fn construct_byte64(path: *const u8, path_len: usize, width: usize) -> *const FmIndexByte64;
    fn destruct_fm_index_byte64(fm_index: *const FmIndexByte64);
    fn count_byte64(
        fm_index: *const FmIndexByte64,
        pattern: *const u8,
        pattern_len: usize,
    ) -> usize;
    fn size_in_bytes_byte64(fm_index: *const FmIndexByte64) -> usize;
    fn locate_byte64(
        fm_index: *const FmIndexByte64,
        pattern: *const u8,
        pattern_len: usize,
    ) -> *const LocateResult;

    // INT 64
    fn construct_int64(path: *const u8, path_len: usize, width: usize) -> *const FmIndexInt64;
    fn destruct_fm_index_int64(fm_index: *const FmIndexInt64);
    fn count_int64(fm_index: *const FmIndexInt64, pattern: *const u64, pattern_len: usize)
        -> usize;
    fn size_in_bytes_int64(fm_index: *const FmIndexInt64) -> usize;
    fn locate_int64(
        fm_index: *const FmIndexInt64,
        pattern: *const u64,
        pattern_len: usize,
    ) -> *const LocateResult;

    // LOCATE RESULT
    fn locate_len(locate_result: *const LocateResult) -> usize;
    fn locate_get(locate_result: *const LocateResult, index: usize) -> usize;
    fn destruct_locate_result(locate_result: *const LocateResult);
}

/// `C`: char type, either `u8` for byte variants or `u64` for int variants.
pub trait SdslFmIndex<C>: Send {
    fn new(path: &str, width: usize) -> Self;
    fn size(&self) -> usize;
    fn count(&self, pattern: &[C]) -> usize;
    fn locate(&self, pattern: &[C]) -> LocateResultPtr;
}

pub struct FmIndexByte32Ptr(*const FmIndexByte32);
pub struct FmIndexInt32Ptr(*const FmIndexInt32);
pub struct FmIndexByte64Ptr(*const FmIndexByte64);
pub struct FmIndexInt64Ptr(*const FmIndexInt64);

unsafe impl Send for FmIndexByte32Ptr {}
unsafe impl Send for FmIndexInt32Ptr {}
unsafe impl Send for FmIndexByte64Ptr {}
unsafe impl Send for FmIndexInt64Ptr {}

impl SdslFmIndex<u8> for FmIndexByte32Ptr {
    fn new(path: &str, width: usize) -> FmIndexByte32Ptr {
        let path = path.as_bytes();
        unsafe { FmIndexByte32Ptr(construct_byte32(path.as_ptr(), path.len(), width)) }
    }

    fn size(&self) -> usize {
        unsafe { size_in_bytes_byte32(self.0) }
    }

    fn count(&self, pattern: &[u8]) -> usize {
        unsafe { count_byte32(self.0, pattern.as_ptr(), pattern.len()) }
    }

    fn locate(&self, pattern: &[u8]) -> LocateResultPtr {
        unsafe {
            LocateResultPtr {
                r: locate_byte32(self.0, pattern.as_ptr(), pattern.len()),
            }
        }
    }
}

impl Drop for FmIndexByte32Ptr {
    fn drop(&mut self) {
        unsafe { destruct_fm_index_byte32(self.0) }
    }
}

impl SdslFmIndex<u64> for FmIndexInt32Ptr {
    fn new(path: &str, width: usize) -> FmIndexInt32Ptr {
        let path = path.as_bytes();
        unsafe { FmIndexInt32Ptr(construct_int32(path.as_ptr(), path.len(), width)) }
    }

    fn size(&self) -> usize {
        unsafe { size_in_bytes_int32(self.0) }
    }

    fn count(&self, pattern: &[u64]) -> usize {
        unsafe { count_int32(self.0, pattern.as_ptr(), pattern.len()) }
    }

    fn locate(&self, pattern: &[u64]) -> LocateResultPtr {
        unsafe {
            LocateResultPtr {
                r: locate_int32(self.0, pattern.as_ptr(), pattern.len()),
            }
        }
    }
}

impl Drop for FmIndexInt32Ptr {
    fn drop(&mut self) {
        unsafe { destruct_fm_index_int32(self.0) }
    }
}

impl SdslFmIndex<u8> for FmIndexByte64Ptr {
    fn new(path: &str, width: usize) -> FmIndexByte64Ptr {
        let path = path.as_bytes();
        unsafe { FmIndexByte64Ptr(construct_byte64(path.as_ptr(), path.len(), width)) }
    }

    fn size(&self) -> usize {
        unsafe { size_in_bytes_byte64(self.0) }
    }

    fn count(&self, pattern: &[u8]) -> usize {
        unsafe { count_byte64(self.0, pattern.as_ptr(), pattern.len()) }
    }

    fn locate(&self, pattern: &[u8]) -> LocateResultPtr {
        unsafe {
            LocateResultPtr {
                r: locate_byte64(self.0, pattern.as_ptr(), pattern.len()),
            }
        }
    }
}

impl Drop for FmIndexByte64Ptr {
    fn drop(&mut self) {
        unsafe { destruct_fm_index_byte64(self.0) }
    }
}

impl SdslFmIndex<u64> for FmIndexInt64Ptr {
    fn new(path: &str, width: usize) -> FmIndexInt64Ptr {
        let path = path.as_bytes();
        unsafe { FmIndexInt64Ptr(construct_int64(path.as_ptr(), path.len(), width)) }
    }

    fn size(&self) -> usize {
        unsafe { size_in_bytes_int64(self.0) }
    }

    fn count(&self, pattern: &[u64]) -> usize {
        unsafe { count_int64(self.0, pattern.as_ptr(), pattern.len()) }
    }

    fn locate(&self, pattern: &[u64]) -> LocateResultPtr {
        unsafe {
            LocateResultPtr {
                r: locate_int64(self.0, pattern.as_ptr(), pattern.len()),
            }
        }
    }
}

impl Drop for FmIndexInt64Ptr {
    fn drop(&mut self) {
        unsafe { destruct_fm_index_int64(self.0) }
    }
}

// LOCATE RESULT

pub struct LocateResultPtr {
    r: *const LocateResult,
}

impl LocateResultPtr {
    pub fn len(&self) -> usize {
        unsafe { locate_len(self.r) }
    }

    pub fn get(&self, index: usize) -> usize {
        unsafe { locate_get(self.r, index) }
    }
}

impl Drop for LocateResultPtr {
    fn drop(&mut self) {
        unsafe { destruct_locate_result(self.r) }
    }
}
