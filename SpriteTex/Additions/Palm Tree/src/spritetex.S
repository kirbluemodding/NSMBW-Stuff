.global TEX_PalmTree
TEX_PalmTree:
	lwz r5, 4(r28)
	srwi r5, r5, 24
	andi. r5, r5, 0xFF
	b GetTexFilenameForR5