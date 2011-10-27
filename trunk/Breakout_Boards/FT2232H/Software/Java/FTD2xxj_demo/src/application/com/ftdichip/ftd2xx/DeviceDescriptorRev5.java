package com.ftdichip.ftd2xx;

/**
 * Extends the <code>DeviceDescriptorRev4</code> with new fields available for
 * revision 5 devices. <br>
 * <br>
 * <b>For a more detailed description of the fields see the ftd2xx-API
 * specification. </b>
 * 
 * @author Mike Werner
 */
public class DeviceDescriptorRev5 extends DeviceDescriptor {

    /**
     * {@code true}if the in-endpoint A is iso-chronous, {@code false}
     * otherwise.
     */
    private boolean inEndPointAIsochronous;

    /**
     * {@code true}if the in-endpoint B is iso-chronous, {@code false}
     * otherwise.
     */
    private boolean inEndPointBIsochronous;

    /**
     * {@code true}if the out-endpoint A is iso-chronous, {@code false}
     * otherwise.
     */
    private boolean outEndPointAIsochronous;

    /**
     * {@code true}if the out-endpoint B is iso-chronous, {@code false}
     * otherwise.
     */
    private boolean outEndPointBIsochronous;

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
     * {@code true}if the interface A is high current, {@code false}otherwise.
     */
    private boolean interfaceAHighCurrent;

    /**
     * {@code true}if the interface B is high current, {@code false}otherwise.
     */
    private boolean interfaceBHighCurrent;

    /**
     * {@code true}if interface A is 245 FIFO, {@code false}otherwise.
     */
    private boolean interfaceAFifo;

    /**
     * {@code true}if interface A is 245 FIFO CPU target, {@code false}.
     */
    private boolean interfaceAFifoCpuTarget;

    /**
     * {@code true}if interface A is Fast serial, {@code false}otherwise.
     */
    private boolean interfaceAFastSerial;

    /**
     * {@code true}if interface A uses VCP drivers, {@code false}otherwise.
     */
    private boolean interfaceAUseVcpDrivers;

    /**
     * {@code true}if interface B is 245 FIFO, {@code false}otherwise.
     */
    private boolean interfaceBFifo;

    /**
     * {@code true}if interface B is 245 FIFO CPU target, {@code false}.
     */
    private boolean interfaceBFifoCpuTarget;

    /**
     * {@code true}if interface B is Fast serial, {@code false}otherwise.
     */
    private boolean interfaceBFastSerial;

    /**
     * {@code true}if interface B uses VCP drivers, {@code false}otherwise.
     */
    private boolean interfaceBUseVcpDrivers;

    /**
     * Determines whether pullDown is enabled or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isPullDownEnabled() {

        return pullDownEnabled;
    }

    /**
     * Sets the new value of the {@code pullDownEnabled}field.
     * 
     * @param pullDownEnabled
     *            the new value.
     */
    public void setPullDownEnabled(boolean pullDownEnabled) {

        this.pullDownEnabled = pullDownEnabled;
    }

    /**
     * Determines if the programmed serialNumber is used or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isSerialNumberEnabled() {

        return serialNumberEnabled;
    }

    /**
     * Sets the new value of the {@code serialNumberEnabled}field.
     * 
     * @param serialNumberEnabled
     *            the new value.
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
     * @param usbVersion
     *            the new USB version.
     */
    public void setUsbVersion(int usbVersion) {

        this.usbVersion = usbVersion;
    }

    /**
     * Determines whether the programmed USB version us used or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isUsbVersionEnabled() {

        return usbVersionEnabled;
    }

    /**
     * Sets the new value of the {@code usbVersionEnabled}field.
     * 
     * @param usbVersionEnabled
     *            the new value.
     */
    public void setUsbVersionEnabled(boolean usbVersionEnabled) {

        this.usbVersionEnabled = usbVersionEnabled;
    }

    /**
     * Determines whether the in-endpoint A is iso-chronous or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInEndPointAIsochronous() {

        return inEndPointAIsochronous;
    }

    /**
     * Sets the new value of the {@code inEndpointAIsochronous}field.
     * 
     * @param inEndPointAIsochronous
     *            the new value.
     */
    public void setInEndPointAIsochronous(boolean inEndPointAIsochronous) {

        this.inEndPointAIsochronous = inEndPointAIsochronous;
    }

    /**
     * Determines whether the in-endpoint B is iso-chronous or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInEndPointBIsochronous() {

        return inEndPointBIsochronous;
    }

    /**
     * Sets the new value of the {@code inEndpointBIsochronous}field.
     * 
     * @param inEndPointBIsochronous
     *            the new value.
     */
    public void setInEndPointBIsochronous(boolean inEndPointBIsochronous) {

        this.inEndPointBIsochronous = inEndPointBIsochronous;
    }

    /**
     * Determines whether interface A is Fast serial or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInterfaceAFastSerial() {

        return interfaceAFastSerial;
    }

    /**
     * Sets the new value of the {@code interfaceAFastSerial}.
     * 
     * @param interfaceAFastSerial
     *            the new value.
     */
    public void setInterfaceAFastSerial(boolean interfaceAFastSerial) {

        this.interfaceAFastSerial = interfaceAFastSerial;
    }

    /**
     * Determines whether interface A is a 245 FIFO or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInterfaceAFifo() {

        return interfaceAFifo;
    }

    /**
     * Sets the new value of the {@code interfaceAFifo} field.
     * 
     * @param interfaceAFifo
     *            the new value.
     */
    public void setInterfaceAFifo(boolean interfaceAFifo) {

        this.interfaceAFifo = interfaceAFifo;
    }

    /**
     * Determines whether interface A is a 245 FIFO CPU target or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInterfaceAFifoCpuTarget() {

        return interfaceAFifoCpuTarget;
    }

    /**
     * Sets the new value of the {@code interfaceAFifoCpuTarget} field.
     * 
     * @param interfaceAFifoCpuTarget
     *            the new value.
     */
    public void setInterfaceAFifoCpuTarget(boolean interfaceAFifoCpuTarget) {

        this.interfaceAFifoCpuTarget = interfaceAFifoCpuTarget;
    }

    /**
     * Determines whether interface A is high current or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInterfaceAHighCurrent() {

        return interfaceAHighCurrent;
    }

    /**
     * Sets the new value of the {@code interfaceAHighCurrent} field.
     * 
     * @param interfaceAHighCurrent
     *            the new value.
     */
    public void setInterfaceAHighCurrent(boolean interfaceAHighCurrent) {

        this.interfaceAHighCurrent = interfaceAHighCurrent;
    }

    /**
     * Determines whether interface A uses VCP drivers or not.
     * 
     * @return {@code true} if it does, {@code false} otherwise.
     */
    public boolean isInterfaceAUseVcpDrivers() {

        return interfaceAUseVcpDrivers;
    }

    /**
     * Sets the new value of the {@code interfaceAUseVcpDrivers} field.
     * 
     * @param interfaceAUseVcpDrivers
     *            the new value.
     */
    public void setInterfaceAUseVcpDrivers(boolean interfaceAUseVcpDrivers) {

        this.interfaceAUseVcpDrivers = interfaceAUseVcpDrivers;
    }

    /**
     * Determines whether interface B is Fast serial or not.
     * 
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isInterfaceBFastSerial() {

        return interfaceBFastSerial;
    }

    /**
     * Sets the new value of the {@code interfaceBFastSerial}.
     * 
     * @param interfaceBFastSerial
     *            the new value.
     */
    public void setInterfaceBFastSerial(boolean interfaceBFastSerial) {

        this.interfaceBFastSerial = interfaceBFastSerial;
    }

    /**
     * Determines whether interface B is a 245 FIFO or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInterfaceBFifo() {

        return interfaceBFifo;
    }

    /**
     * Sets the new value of the {@code interfaceBFifo} field.
     * 
     * @param interfaceBFifo
     *            the new value.
     */
    public void setInterfaceBFifo(boolean interfaceBFifo) {

        this.interfaceBFifo = interfaceBFifo;
    }

    /**
     * Determines whether interface B is a 245 FIFO CPU target or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInterfaceBFifoCpuTarget() {

        return interfaceBFifoCpuTarget;
    }

    /**
     * Sets the new value of the {@code interfaceBFifoCpuTarget} field.
     * 
     * @param interfaceBFifoCpuTarget
     *            the new value.
     */
    public void setInterfaceBFifoCpuTarget(boolean interfaceBFifoCpuTarget) {

        this.interfaceBFifoCpuTarget = interfaceBFifoCpuTarget;
    }

    /**
     * Determines whether interface B is high current or not.
     * 
     * @return {@code true}if it is, {@code false}otherwise.
     */
    public boolean isInterfaceBHighCurrent() {

        return interfaceBHighCurrent;
    }

    /**
     * Sets the new value of the {@code interfaceBHighCurrent} field.
     * 
     * @param interfaceBHighCurrent
     *            the new value.
     */
    public void setInterfaceBHighCurrent(boolean interfaceBHighCurrent) {

        this.interfaceBHighCurrent = interfaceBHighCurrent;
    }

    /**
     * Determines whether interface B uses VCP drivers or not.
     * 
     * @return {@code true} if it does, {@code false} otherwise.
     */
    public boolean isInterfaceBUseVcpDrivers() {

        return interfaceBUseVcpDrivers;
    }

    /**
     * Sets the new value of the {@code interfaceBUseVcpDrivers} field.
     * 
     * @param interfaceBUseVcpDrivers
     *            the new value.
     */
    public void setInterfaceBUseVcpDrivers(boolean interfaceBUseVcpDrivers) {

        this.interfaceBUseVcpDrivers = interfaceBUseVcpDrivers;
    }

    /**
     * Determines whether out-endpoint A is iso-chronous or not.
     * 
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isOutEndPointAIsochronous() {

        return outEndPointAIsochronous;
    }

    /**
     * Sets the new value of the {@code outEndPointAIsochronous} field.
     * 
     * @param outEndPointAIsochronous
     *            the new value.
     */
    public void setOutEndPointAIsochronous(boolean outEndPointAIsochronous) {

        this.outEndPointAIsochronous = outEndPointAIsochronous;
    }

    /**
     * Determines whether out-endpoint B is iso-chronous or not.
     * 
     * @return {@code true} if it is, {@code false} otherwise.
     */
    public boolean isOutEndPointBIsochronous() {

        return outEndPointBIsochronous;
    }

    /**
     * Sets the new value of the {@code outEndPointBIsochronous} field.
     * 
     * @param outEndPointBIsochronous
     *            the new value.
     */
    public void setOutEndPointBIsochronous(boolean outEndPointBIsochronous) {

        this.outEndPointBIsochronous = outEndPointBIsochronous;
    }
}
