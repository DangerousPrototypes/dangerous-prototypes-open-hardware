package com.ftdichip.ftd2xx;

import javax.util.Localizer;

/**
 * Enumeration of all possible <i>Bit Bang Modes </i>.
 * 
 * @author Mike Werner
 */
public enum BitBangMode {

	/**
	 * Resets the I/O <i>Bit Bang </i> mode.
	 */
	RESET(0x0),

	/**
	 * Asynchronous <i>Bit Bang Mode </i>.
	 */
	ASYNCHRONOUS(0x1),

	/**
	 * <i>MPSSE </i> mode.
	 */
	MPSSE(0x2),

	/**
	 * Synchronous <i>Bit Bang Mode </i>
	 */
	SYNCHRONOUS(0x4),

	/**
	 * <i>MCU </i> host bus emulation mode.
	 */
	MCU_HOST_BUS_EMULATION(0x8),

	/**
	 * Fast opto-isolated serial mode.
	 */
	FAST_OPTO_ISOLATED_SERIAL(0x10);

	/**
	 * Holds the native value of a particular {@code BitBangMode}.
	 */
	public final int value;

	private BitBangMode(int value) {

		this.value = value;
	}

	/**
	 * Retrieves the {@code BitBangMode} by it`s native mode value.
	 * 
	 * @param mode
	 *            the native mode value.
	 * @return the enumeration constant representing the mode value.
	 * @throws FTD2xxException
	 *             if the mode value is unknown.
	 */
	public static BitBangMode valueOf(int mode) throws FTD2xxException {

		BitBangMode result = null;

		for (BitBangMode m : values()) {
			if (m.value == mode) {
				result = m;
				break;
			}
		}

		if (result == null) {
			throw new FTD2xxException(Localizer.getLocalizedMessage(
					BitBangMode.class, "valueOf.error.unknownMode", mode));
		}

		return result;
	}
}
