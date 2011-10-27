package com.ftdichip.ftd2xx;

import java.util.NoSuchElementException;

import javax.util.Localizer;

/**
 * Enumeration of all known errors of the FTD2xx API.
 * 
 * @author Mike Werner
 */
public enum FTStatus {
	/**
	 * No error. The operation was successful.
	 */
	FT_OK,

	/**
	 * The handle provided as a parameter is invalid.
	 */
	FT_INVALID_HANDLE,

	/**
	 * The specified device was not found.
	 */
	FT_DEVICE_NOT_FOUND,

	/**
	 * Tried to access a device that was not opened before.
	 */
	FT_DEVICE_NOT_OPENED,

	/**
	 * A general I/O error has occurred.
	 */
	FT_IO_ERROR,

	/**
	 * Not enough resources to perform the operation.
	 */
	FT_INSUFFICIENT_RESOURCES,

	/**
	 * A parameter provided to an operation was invalid.
	 */
	FT_INVALID_PARAMETER,

	/**
	 * The baud rate is invalid.
	 */
	FT_INVALID_BAUD_RATE,

	/**
	 * Tried to erase on a device that was not opened with erase permission.
	 */
	FT_DEVICE_NOT_OPENED_FOR_ERASE,

	/**
	 * Tried to write on a device that was not opened with write permission.
	 */
	FT_DEVICE_NOT_OPENED_FOR_WRITE,

	/**
	 * Writing to the device has failed.
	 */
	FT_FAILED_TO_WRITE_DEVICE,

	/**
	 * Failed to read from the EEPROM.
	 */
	FT_EEPROM_READ_FAILED,

	/**
	 * Failed to write to the EEPROM.
	 */
	FT_EEPROM_WRITE_FAILED,

	/**
	 * Failed to erase the EEPROM.
	 */
	FT_EEPROM_ERASE_FAILED,

	/**
	 * The EEPROM is not present on the device.
	 */
	FT_EEPROM_NOT_PRESENT,

	/**
	 * The EEPROM is not programmed.
	 */
	FT_EEPROM_NOT_PROGRAMMED,

	/**
	 * The arguments provided to an operation are invalid.
	 */
	FT_INVALID_ARGS,

	/**
	 * The operation is not supported for the current device.
	 */
	FT_NOT_SUPPORTED,

	/**
	 * An error has occurred that can not be described in more detail.
	 */
	FT_OTHER_ERROR;

	/**
	 * Retrieves a status value with a particular ordinal.
	 * 
	 * @param ordinal
	 *            the ordinal of the status value to search for.
	 * @return the status with the particular ordinal.
	 */
	public static FTStatus byOrdinal(int ordinal) {

		FTStatus result = null;
		for (FTStatus status : values()) {
			if (status.ordinal() == ordinal) {
				result = status;
				break;
			}
		}

		if (result == null) {
			throw new NoSuchElementException("Unknown ordinal: " + ordinal);
		}

		return result;
	}

	/**
	 * Retrieves the localized message for a particular <code>FTStatus</code>.
	 * 
	 * @param status
	 *            the status value for which to retrieve the localized message.
	 * @return the localized message.
	 */
	public static String getLocalizedMessage(FTStatus status) {

		return Localizer.getLocalizedMessage(FTStatus.class, status.toString());
	}

	/**
	 * Throws the exception related to a particular status value. This method is
	 * used by the native code to throw localized exceptions.
	 * 
	 * @param statusValue
	 *            the status value for which to throw the exception.
	 * @throws FTD2xxException
	 *             the exception related to the status value.
	 */
	static void throwException(int statusValue) throws FTD2xxException {

		try {
			FTStatus status = FTStatus.byOrdinal(statusValue);
			throwNewException(status, getLocalizedMessage(status));
		} catch (NoSuchElementException e) {
			String message = Localizer.getLocalizedMessage(FTStatus.class,
					"undefinedStatus", statusValue);
			throw new FTD2xxException(message);
		} catch (FTD2xxException e) {
			throw e;
		} catch (Exception e) {
			throw (RuntimeException) e;
		}
	}

	private static void throwNewException(FTStatus status, String message)
			throws Exception {

		Exception result = null;

		switch (status) {
		case FT_INVALID_HANDLE:
			/* fall through */
		case FT_INVALID_PARAMETER:
			/* fall through */
		case FT_INVALID_BAUD_RATE:
			/* fall through */
		case FT_INVALID_ARGS:
			result = new IllegalArgumentException(message);
			break;

		case FT_DEVICE_NOT_OPENED_FOR_ERASE:
			/* fall through */
		case FT_DEVICE_NOT_OPENED_FOR_WRITE:
			/* fall through */
		case FT_DEVICE_NOT_OPENED:
			result = new IllegalStateException(message);
			break;

		case FT_EEPROM_READ_FAILED:
			/* fall through */
		case FT_EEPROM_WRITE_FAILED:
			/* fall through */
		case FT_EEPROM_ERASE_FAILED:
			/* fall through */
		case FT_EEPROM_NOT_PRESENT:
			/* fall through */
		case FT_EEPROM_NOT_PROGRAMMED:
			result = new EEPROMException(message);
			break;

		case FT_NOT_SUPPORTED:
			result = new UnsupportedOperationException(message);
			break;

		case FT_DEVICE_NOT_FOUND:
			/* fall through */
		case FT_IO_ERROR:
			/* fall through */
		case FT_INSUFFICIENT_RESOURCES:
			/* fall through */
		case FT_FAILED_TO_WRITE_DEVICE:
			/* fall through */
		default:
			result = new FTD2xxException(message);
			break;
		}

		throw result;
	}
}
