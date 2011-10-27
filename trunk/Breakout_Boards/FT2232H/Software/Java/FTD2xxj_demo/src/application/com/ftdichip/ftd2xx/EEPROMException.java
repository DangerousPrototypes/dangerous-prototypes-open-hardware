package com.ftdichip.ftd2xx;

/**
 * Signals errors accessing a device`s EEPROM.
 * 
 * @author Mike Werner
 */
public class EEPROMException extends FTD2xxException {

    private static final long serialVersionUID = 1L;

    /**
     * Creates a new <code>EEPROMException</code>.
     * 
     * @param message
     *            the error message.
     */
    public EEPROMException(String message) {

        super(message);
    }

    /**
     * Creates a new <code>EEPROMException</code>.
     * 
     * @param cause
     *            the initial cause.
     */
    public EEPROMException(Throwable cause) {

        super(cause);
    }

    /**
     * Creates a new <code>EEPROMException</code>.
     * 
     * @param message
     *            the error message.
     * @param cause
     *            the initial cause.
     */
    public EEPROMException(String message, Throwable cause) {

        super(message, cause);
    }
}
