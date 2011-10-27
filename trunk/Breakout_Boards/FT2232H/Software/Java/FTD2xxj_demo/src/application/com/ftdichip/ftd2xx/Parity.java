package com.ftdichip.ftd2xx;

/**
 * Enumeration of valid parity values.
 * 
 * @author Mike Werner
 */
public enum Parity {
    /**
     * No parity used.
     */
    NONE(0), 
    
    /**
     * Odd parity.
     */
    ODD(1), 
    
    /**
     * Even parity.
     */
    EVEN(2), 
    
    /**
     * Mark parity.
     */
    MARK(3), 
    
    /**
     * Space parity.
     */
    SPACE(4);

    /**
     * The value associated with this enumeration constant.
     */
    public final int value;

    private Parity(int value) {

        this.value = value;
    }
}
