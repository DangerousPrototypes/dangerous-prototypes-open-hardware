package com.ftdichip.ftd2xx;

/**
 * Enumeration of valid data size values used for a {@code Port}`s data
 * characteristics.
 * 
 * @author Mike Werner
 */
public enum DataBits {
    /**
     * 8 bits used for the data.
     */
    DATA_BITS_8(8),
    
    /**
     * 7 bits used for the data.
     */
    DATA_BITS_7(7),
    
    /**
     * 6 bits used for the data.
     */
    DATA_BITS_6(6),
    
    /**
     * 5 bits used for the data
     */
    DATA_BITS_5(5);
    
    /**
     * The value associated with this enumeration constant.
     */
    public final int value;
    
    private DataBits(int value) {
        this.value = value;
    }
}
