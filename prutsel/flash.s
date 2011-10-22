

.global		_FreadUp

_FreadUp:	tblrdh		WO, [W0]
			return

.global _FreadHi

_FreadHi:	tblrdl.b	WO, [W0]
			return

.global _FreadLo
_FreadLo:	tblrdl.b	WO, [++W0]
			return
