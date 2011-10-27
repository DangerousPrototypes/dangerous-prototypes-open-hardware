package com.ftdichip.ftd2xx;

import java.io.IOException;
import java.io.InputStream;

/**
 * <code>InputStream</code> to read data from a
 * {@link com.ftdichip.ftd2xx.Device} using standard Java I/O.
 * 
 * @author Mike Werner
 */
class DeviceInputStream extends InputStream {

    private Device device;

    /**
     * Creates a new <code>DeviceInputStream</code>.
     * 
     * @param device
     *            the device to read from.
     */
    public DeviceInputStream(Device device) {

        this.device = device;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public int read() throws IOException {        
        return device.read();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public int available() throws IOException {

        return (int)device.getReceiveQueueStatus();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public int read(byte[] buffer, int offset, int length) throws IOException {

        return device.read(buffer, offset, length);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public int read(byte[] b) throws IOException {

        return device.read(b);
    }
}
