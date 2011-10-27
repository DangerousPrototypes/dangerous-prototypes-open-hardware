package com.ftdichip.ftd2xx;

/**
 * Enumeration of all supported devices.
 * 
 * @author Mike Werner
 */
public enum DeviceType {
    /**
     * Type of BM devices.
     */
    FT_DEVICE_BM, 
    
    /**
     * Type of AM devices.
     */
    FT_DEVICE_AM, 
    
    /**
     * Type of 100AX devices.
     */
    FT_DEVICE_100AX, 
    
    /**
     * Unknown device. Maybe it is currently not supported by this API.
     */
    FT_DEVICE_UNKNOWN, 
    
    /**
     * Type of 2232C devices.
     */
    FT_DEVICE_2232C, 
    
    /**
     * Type of 232R devices.
     */
    FT_DEVICE_232R;

    /**
     * Searches for constant representing a particular native device type code.
     * 
     * @param deviceType
     *            the native code to search for.
     * @return the constant if one was found, {@code FT_DEVICE_UNKNOWN}
     *         otherwise.
     */
    public static DeviceType valueOf(long deviceType) {

        DeviceType result = null;

        for (DeviceType t : values()) {
            if (t.ordinal() == deviceType) {
                result = t;
                break;
            }
        }

        if (result == null)
            result = FT_DEVICE_UNKNOWN;

        return result;
    }
}
