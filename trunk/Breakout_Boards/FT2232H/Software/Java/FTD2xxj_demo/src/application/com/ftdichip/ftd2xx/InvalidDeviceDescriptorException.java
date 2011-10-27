package com.ftdichip.ftd2xx;

/**
 * Signals a {@link com.ftdichip.ftd2xx.DeviceDescriptor}contains invalid data.
 * 
 * @author Mike Werner
 */
public class InvalidDeviceDescriptorException extends EEPROMException {
    
    /**
     * <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    /**
     * Creates a new <code>InvalidDeviceDescriptorException</code>.
     *  
     * @param message the message describing the error.
     */
    public InvalidDeviceDescriptorException(String message) {

        super(message);
    }

    /**
     * Creates a new <code>InvalidDeviceDescriptorException</code>.
     * 
     * @param cause the error that caused this exception.
     */
    public InvalidDeviceDescriptorException(Throwable cause) {

        super(cause);
    }

    /**
     * Creates a new <code>InvalidDeviceDescriptorException</code>.
     * 
     * @param message the message describing the error.
     * @param cause the error that caused this exception.
     */
    public InvalidDeviceDescriptorException(String message, Throwable cause) {

        super(message, cause);
    }
}
