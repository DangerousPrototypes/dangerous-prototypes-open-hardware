package com.ftdichip.ftd2xx;


/**
 * Enumeration of valid stop bit values.
 * 
 * @author Mike Werner
 */
public enum StopBits {
    /**
     * 1 stop bit.
     */
    STOP_BITS_1(0),
    
    /**
     * 1.5 stop bits.
     */
    STOP_BITS_1_5(1),
    
    /**
     * 2 stop bits.
     */
    STOP_BITS_2(2);
    
    /**
     * The value associated with this enumeration constant.
     */
    public final int value;
    
    private StopBits(int value) {
        this.value = value;
    }
}
