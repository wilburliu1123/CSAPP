	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 1
	.globl	_multstore              ; -- Begin function multstore
	.p2align	2
_multstore:                             ; @multstore
	.cfi_startproc
; %bb.0:
	stp	x20, x19, [sp, #-32]!   ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]     ; 16-byte Folded Spill
	add	x29, sp, #16            ; =16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x2
	bl	_mult2
	str	x0, [x19]
	ldp	x29, x30, [sp, #16]     ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32     ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                   ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	mov	w0, #0
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
