package com.ftdichip.ftd2xx;

/**
 * Extends the standard <code>DeviceDescriptor</code> with new fields
 * available for revision 4 devices. <br>
 * <br>
 * <b>For a more detailed description of the fields see the ftd2xx-API
 * specification. </b>
 * 
 * @author Mike Werner
 */
public class DeviceDescriptorRev4 extends DeviceDescriptor {

    /**
     * <code>true</code> if the in-endpoint is iso-chronous, <code>false</code>
     * otherwise.
     */
    private boolean inEndPointIsochronous;

    /**
     * <code>true</code> if the out-endpoint is iso-chronous,
     * <code>false</code> otherwise.
     */
    private boolean outEndPointIsochronous;

    /**
     * <code>true</code> if pullDown is enabled, <code>false</code>
     * otherwise.
     */
    private boolean pullDownEnabled;

    /**
     * {@code true}if the serialNumber shall be used, {@code false}otherwise.
     */
    private boolean serialNumberEnabled;

    /**
     * {@code true}if the USB version shall be used.
     */
    private boolean usbVersionEnabled;

    /**
     * Binary Coded Decimal representation of the USB version (e.g. USB 2.0 =
     * 0x200).
     */
    private int usbVersion;
        
    /**
     * Determines whether the in-endpoint is iso-chronous or not.
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isInEndPointIsochronous() {

        return inEndPointIsochronous;
    }
    
    /**
     * Sets the new value of the {@code inEndPointIsochronous} field.
     * 
     * @param inEndPointIsochronous the new value.
     */
    public void setInEndPointIsochronous(boolean inEndPointIsochronous) {

        this.inEndPointIsochronous = inEndPointIsochronous;
    }
    
    /**
     * Determines whether the out-endpoint is iso-chronous or not.
     * 
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isOutEndPointIsochronous() {

        return outEndPointIsochronous;
    }
    
    /**
     * Sets the new value of the {@code outEndPointIsochronous} field.
     * 
     * @param outEndPointIsochronous the new value.
     */
    public void setOutEndPointIsochronous(boolean outEndPointIsochronous) {

        this.outEndPointIsochronous = outEndPointIsochronous;
    }
    
    /**
     * Determines whether pullDown is enabled or not.
     * 
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isPullDownEnabled() {

        return pullDownEnabled;
    }
    
    /**
     * Sets the new value of the {@code pullDownEnabled} field.
     * 
     * @param pullDownEnabled the new value.
     */
    public void setPullDownEnabled(boolean pullDownEnabled) {

        this.pullDownEnabled = pullDownEnabled;
    }
    
    
    /**
     * Determines if the programmed serialNumber is used or not.
     * 
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isSerialNumberEnabled() {

        return serialNumberEnabled;
    }
    
    /**
     * Sets the new value of the {@code serialNumberEnabled} field.
     * 
     * @param serialNumberEnabled the new value.
     */
    public void setSerialNumberEnabled(boolean serialNumberEnabled) {

        this.serialNumberEnabled = serialNumberEnabled;
    }
    
    /**
     * Retrieves the BCD representation of the supported USB version.
     * 
     * @return the USB version.
     */
    public int getUsbVersion() {

        return usbVersion;
    }
    
    /**
     * Sets the new USB version.
     * 
     * @param usbVersion the new USB version.
     */
    public void setUsbVersion(int usbVersion) {

        this.usbVersion = usbVersion;
    }
    
    /**
     * Determines whether the programmed USB version us used or not.
     * 
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isUsbVersionEnabled() {

        return usbVersionEnabled;
    }
    
    /**
     * Sets the new value of the {@code usbVersionEnabled} field.
     * 
     * @param usbVersionEnabled the new value.
     */
    public void setUsbVersionEnabled(boolean usbVersionEnabled) {

        this.usbVersionEnabled = usbVersionEnabled;
    }
}
