package com.ftdichip.ftd2xx;

import java.io.IOException;

/**
 * Signals errors accessing a ftd2xx device.
 * 
 * @author Mike Werner
 */
public class FTD2xxException extends IOException {

    private static final long serialVersionUID = 1L;

    /**
     * Creates a new <code>FTD2xxException</code>.
     * 
     * @param message
     *            The error message.
     */
    public FTD2xxException(String message) {

        super(message);
    }

    /**
     * Creates a new <code>FTD2xxException</code>.
     * 
     * @param cause
     *            The initial cause of the error.
     */
    public FTD2xxException(Throwable cause) {

        initCause(cause);
    }

    /**
     * Creates a new <code>FTD2xxException</code>.
     * 
     * @param message
     *            The error message.
     * @param cause
     *            The initial cause of the error.
     */
    public FTD2xxException(String message, Throwable cause) {

        super(message);

        initCause(cause);
    }
}
