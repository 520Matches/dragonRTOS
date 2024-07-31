.align 4
.global trap_entry
trap_entry:
	csrrw sp, sscratch, sp
