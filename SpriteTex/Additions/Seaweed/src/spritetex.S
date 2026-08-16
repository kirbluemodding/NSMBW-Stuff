.global TEX_Seaweed
TEX_Seaweed:
	lwz r5, 4(r28)
	srwi r5, r5, 24
	andi. r5, r5, 0xFF
	b GetTexFilenameForR5