package com.ftdichip.ftd2xx;

/**
 * Enumeration of possible modem status values.
 * 
 * @author Mike Werner
 */
public enum ModemStatus {

    /**
     * No error occurred.
     */
    OK(0),

    /**
     * The handle used to access a device was invalid.
     */
    INVALID_HANLDE(1),

    /**
     * The specified device was not found. Maybe it was removed.
     */
    DEVICE_NOT_FOUND(2),

    /**
     * The operation failed, because the device is not open.
     */
    DEVICE_NOT_OPENED(3),

    /**
     * An error has occurred while transferring data.
     */
    IO_ERROR(4),

    /**
     * Not enough platform resources to perform the operation.
     */
    INSUFFICIENT_RESOURCES(5),

    /**
     * A parameter specified is invalid.
     */
    INVALID_PARAMETER(6),

    /**
     * The specified baud rate is invalid.
     */
    INVALID_BAUD_RATE(7),

    /**
     * The device was not opened for erasure.
     */
    DEVICE_NOT_OPENED_FOR_ERASE(8),

    /**
     * The device was not opened for writing.
     */
    DEVICE_NOT_OPENED_FOR_WRITE(9),

    /**
     * Failed to write to the device.
     */
    FAILED_TO_WRITE_DEVICE(10),

    /**
     * The EEPROM can not be read.
     */
    EEPROM_READ_FAILED(11),

    /**
     * Failed to write to the EEPROM.
     */
    EEPROM_WRITE_FAILED(12),

    /**
     * The EEPROM can not be erased.
     */
    EEPROM_ERASE_FAILED(13),

    /**
     * No EEPROM installed.
     */
    EEPROM_NOT_PRESENT(14),

    /**
     * Failed to program the EEPROM.
     */
    EEPROM_NOT_PROGRAMMED(15),

    /**
     * The specified arguments are invalid.
     */
    INVALID_ARGS(16),

    /**
     * The operation that was performed is not supported for the device.
     */
    NOT_SUPPORTED(17),

    /**
     * Any other error.
     */
    OTHER_ERROR(18),

    /**
     * If the error is unknown. Maybe when a newer ftd2xx-API is used with new
     * error values.
     */
    UNKNOWN(-1);

    /**
     * The value associated with this constant.
     */
    public final long value;

    private ModemStatus(long value) {

        this.value = value;
    }

    /**
     * Retrieves the status by it`s raw value.
     * 
     * @param value
     *            the value to search for.
     * @return the status value or {@link #UNKNOWN}if no status was found.
     */
    public static ModemStatus byValue(long value) {

        ModemStatus result = null;

        for (ModemStatus s : values()) {
            if (s.value == value) {
                result = s;
                break;
            }
        }

        if (result == null)
            result = UNKNOWN;

        return result;
    }
}
