package com.ftdichip.ftd2xx;


/**
 * Enumeration of valid flow control values.
 * 
 * @author Mike Werner
 */
public enum FlowControl {
    /**
     * No flow control.
     */
    NONE(0x0000),
    
    /**
     * RTS CTS.
     */
    RTS_CTS(0x0100),
    
    /**
     * DTR DSR.
     */
    DTR_DSR(0x0200),
    
    /**
     * XON XOFF.
     */
    XON_XOFF(0x0400);
    
    /**
     * The value of this enumeration constant.
     */
    public final int value;
    
    private FlowControl(int value) {
        this.value = value;
    }
}
