.section .text

.global memcpy_sse42_asm
.global memcpy_avx_asm
.global memset_sse42_asm
.global memset_avx_asm

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


memset_sse42_asm:
    cmp r8, 0
    jz .memset_sse42_done

    movzx rdx, dl
    mov rax, 0x0101010101010101
    imul rdx, rax
    movq xmm0, rdx
    punpcklqdq xmm0, xmm0

    test rcx, 15
    jnz .memset_sse42_loop_unaligned
.memset_sse42_loop_aligned:
    movaps [rcx], xmm0

    add rcx, 16
    sub r8, 16
    jz .memset_sse42_done

    jmp .memset_sse42_loop_aligned
.memset_sse42_loop_unaligned:
    movups [rcx], xmm0

    add rcx, 16
    sub r8, 16
    jz .memset_sse42_done

    jmp .memset_sse42_loop_unaligned
.memset_sse42_done:
    ret


memset_avx_asm:
    cmp r8, 0
    jz .memset_avx_done

    movzx   rdx, dl
    mov     rax, 0x0101010101010101
    imul    rdx, rax
    movq    xmm0, rdx
    punpcklqdq xmm0, xmm0
    vinsertf128 ymm0, ymm0, xmm0, 1

    test rcx, 31
    jnz .memset_avx_loop_unaligned
.memset_avx_loop_aligned:
    vmovdqa [rcx], ymm0

    add rcx, 32
    sub r8, 32
    jz .memset_avx_done

    jmp .memset_avx_loop_aligned
.memset_avx_loop_unaligned:
    vmovdqu [rcx], ymm0

    add rcx, 32
    sub r8, 32
    jz .memset_avx_done

    jmp .memset_avx_loop_unaligned
.memset_avx_done:
    vzeroupper
    ret