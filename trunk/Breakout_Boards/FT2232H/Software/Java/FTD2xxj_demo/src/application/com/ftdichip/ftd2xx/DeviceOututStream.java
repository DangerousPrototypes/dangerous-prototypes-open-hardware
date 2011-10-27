package com.ftdichip.ftd2xx;

import java.io.IOException;
import java.io.OutputStream;

/**
 * <code>OutputStream</code> to write data to a
 * {@link com.ftdichip.ftd2xx.Device}using standard Java I/O.
 * 
 * @author Mike Werner
 */
class DeviceOututStream extends OutputStream {

    private Device device;

    /**
     * Creates a new <code>DeviceOututStream</code>.
     * 
     * @param device
     *            the device to write to.
     */
    public DeviceOututStream(Device device) {

        this.device = device;
    }

    /**
     * Writes one byte to the device.
     * 
     * @param b
     *            the byte to write.
     * @throws java.io.IOException
     *             if the byte can not be written.
     */
    @Override
    public void write(int b) throws IOException {

        device.write(b);
    }
        
    /**
     * Writes data to the device.
     * 
     * @param buffer the buffer storing the data to write.
     * @param offset the index of the first byte to write.
     * @param length the number of bytes to write.
     * 
     * @throws java.io.IOException if the data can not be written.
     */
    @Override
    public void write(byte[] buffer, int offset, int length) throws IOException {

        device.write(buffer, offset, length);
    }
    
    /**
     * Writes data to the device.
     * 
     * @param buffer the buffer storing the data to write.
     * @throws java.io.IOException if the data can not be written.
     */
    @Override
    public void write(byte[] buffer) throws IOException {

        device.write(buffer);
    }
}
