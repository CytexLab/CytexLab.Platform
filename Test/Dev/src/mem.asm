.intel_syntax noprefix
.section .text

.global memcpy_sse42_asm

memcpy_sse42_asm:
    cmp r8, 0
    jz .done

    test rcx, 15
    jnz .loop_anling
    test rdx, 15
    jnz .loop_anling
.loop_ling:
    movaps xmm0, [rcx]
    movaps [rdx], xmm0

    add rcx, 16
    add rdx, 16
    sub r8, 16
    jz .done

    jmp .loop_ling
.loop_anling:
    movups xmm0, [rcx]
    movups [rdx], xmm0

    add rcx, 16
    add rdx, 16
    sub r8, 16
    jz .done

    jmp .loop_anling
.done:
    ret