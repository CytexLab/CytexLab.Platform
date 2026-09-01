.section .text

.global memcpy_sse42_asm
.global memcpy_avx_asm

memcpy_sse42_asm:
    cmp r8, 0
    jz .memcpy_sse42_done

    test rcx, 15
    jnz .memcpy_sse42_loop_unaligned
    test rdx, 15
    jnz .memcpy_sse42_loop_unaligned
.memcpy_sse42_loop_aligned:
    movaps xmm0, [rcx]
    movaps [rdx], xmm0

    add rcx, 16
    add rdx, 16
    sub r8, 16
    jz .memcpy_sse42_done

    jmp .memcpy_sse42_loop_aligned
.memcpy_sse42_loop_unaligned:
    movups xmm0, [rcx]
    movups [rdx], xmm0

    add rcx, 16
    add rdx, 16
    sub r8, 16
    jz .memcpy_sse42_done

    jmp .memcpy_sse42_loop_unaligned
.memcpy_sse42_done:
    ret

memcpy_avx_asm:
    cmp r8, 0
    jz .memcpy_avx_done

    test rcx, 31
    jnz .memcpy_avx_loop_unaligned
    test rdx, 31
    jnz .memcpy_avx_loop_unaligned
.memcpy_avx_loop_aligned:
    vmovdqa ymm0, [rcx]
    vmovdqa [rdx], ymm0

    add rcx, 32
    add rdx, 32
    sub r8, 32
    jz .memcpy_avx_done

    jmp .memcpy_avx_loop_aligned
.memcpy_avx_loop_unaligned:
    vmovdqu ymm0, [rcx]
    vmovdqu [rdx], ymm0

    add rcx, 32
    add rdx, 32
    sub r8, 32
    jz .memcpy_avx_done

    jmp .memcpy_avx_loop_unaligned
.memcpy_avx_done:
    vzeroupper
    ret