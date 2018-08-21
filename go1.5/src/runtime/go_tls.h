// Copyright 2014 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifdef GOARCH_arm
#define LR R14
#endif

#ifdef GOARCH_amd64
#ifdef GOOS_rumprun
// works for any register r except AX; r != AX verified in all callers
#define get_tls(r)              \
    PUSHQ   SP    \
    PUSHQ   AX    \
    PUSHQ   CX    \
    PUSHQ   DX    \
    PUSHQ   DI    \
    PUSHQ   SI    \
    PUSHQ   R8    \
    PUSHQ   R9    \
    PUSHQ   R10    \
    PUSHQ   R11    \
    PUSHQ   BX    \
    PUSHQ   BP    \
    PUSHQ   R12    \
    PUSHQ   R13    \
    PUSHQ   R14    \
    PUSHQ   R15    \
    LEAQ    x_cgo_get_tls(SB), AX;   \
    CALL    AX;                 \
    POPQ    R15    \
    POPQ    R14    \
    POPQ    R13    \
    POPQ    R12    \
    POPQ    BP    \
    POPQ    BX    \
    POPQ    R11    \
    POPQ    R10    \
    POPQ    R9    \
    POPQ    R8    \
    POPQ    SI    \
    POPQ    DI    \
    POPQ    DX    \
    POPQ    CX    \
    MOVQ    AX, r    \
    POPQ    AX    \
    POPQ    SP
#define g(r)    0(r)
#else
    #define get_tls(r)  MOVQ TLS, r
    #define g(r)    0(r)(TLS*1)
#endif
#endif

#ifdef GOARCH_amd64p32
#define get_tls(r)  MOVL TLS, r
#define g(r)    0(r)(TLS*1)
#endif

#ifdef GOARCH_386
#define get_tls(r)  MOVL TLS, r
#define g(r)    0(r)(TLS*1)
#endif
