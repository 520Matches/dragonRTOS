ENTRY(_start)
	; disable all interrupts
	csrw CSR_IE, zero
	csrw CSR_IP, zero
