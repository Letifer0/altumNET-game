#pragma once

#ifdef INT_2_BYTES

using i16 = signed int;
using i32 = signed long;
using i64 = signed long long;
using u16 = unsigned int;
using u32 = unsigned long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;

#else

using i16 = signed short;
using i32 = signed long;
using i64 = signed long long;
using u16 = unsigned short;
using u32 = unsigned long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;

#endif