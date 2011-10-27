package com.ftdichip.ftd2xx;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.util.Localizer;

/**
 * Represents the Device to access a particular the ft2xx device (e.g. FT232BM).
 * <br>
 * <br>
 * <b>Example: </b> Accessing device descriptor information. <br>
 * 
 * <pre>
 * Device[] devices = Service.listDevices();
 * Device device = devices[0];
 * 
 * device.open();
 * 
 * DeviceDescriptor descriptor = device.getDeviceDescriptor();
 * 
 * System.out.println(desc.getManufacturer());
 * System.out.println(desc.getSerialNumber());
 * System.out.println(desc.getProductDescription());
 * 
 * device.close();
 * </pre>
 * 
 * <br>
 * <b>Compatibility with the native ftd2xx-API: </b> <br>
 * <ul>
 * <li>The function {@code FT_SetChars(...)}is not supported. It does not fit
 * into the current design.</li>
 * <li>The parameter names of {@code FT_SetUSBParameters(...)}are renamed for
 * more clearness.
 * <li>Events are currently not supported</li>
 * </ul>
 * 
 * @author Mike Werner
 */
public class Device {

	private final static Logger logger = Logger.getLogger(Device.class
			.getName());

	// default timeout values as specified by the ftd2xx API.
	private final static int DEFAULT_RX_TIMEOUT = 300;

	private final static int DEFAULT_TX_TIMEOUT = 300;

	private EEPROM eeprom = new EEPROM(this);

	private Port port = new Port(this);

	private long resetPipeRetryCount = 50;

	/**
	 * The handle to access the native API.
	 */
	private long handle = -1;

	/**
	 * The devices location within the USB tree.
	 */
	private long locationID;

	private DeviceType type;

	private long readTimeout = DEFAULT_RX_TIMEOUT;

	private long writeTimeout = DEFAULT_TX_TIMEOUT;

	/**
	 * Creates a new <code>Device</code>. The device descriptor is read from
	 * the EEPROM.
	 * 
	 * @param locationID
	 *            the device`s location within the USB tree.
	 * @param deviceType
	 *            the native device type code.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	protected Device(long locationID, long deviceType) throws FTD2xxException {

		this.locationID = locationID;
		type = DeviceType.valueOf(deviceType);

		open();

		getDeviceDescriptor(); // just to initialize the device descriptor.

		close();
	}

	/**
	 * Retrieves this device`s type.
	 * 
	 * @return the type of this device.
	 */
	public DeviceType getType() {

		return type;
	}

	/**
	 * Retrieves this device`s port.
	 * 
	 * @return the port.
	 */
	public Port getPort() {

		return port;
	}

	/**
	 * Retrieves this device`s device descriptor.
	 * 
	 * @return the device descriptor.
	 * @throws FTD2xxException
	 *             if the device descriptor can not be read from the EEPROM.
	 */
	public DeviceDescriptor getDeviceDescriptor() throws FTD2xxException {

		return eeprom.getDeviceDescriptor();
	}

	/**
	 * Retrieves the handle of this device.
	 * 
	 * @return the handle.
	 */
	long getHandle() {

		return handle;
	}

	private void checkIsOpen() {

		if (!isOpen())
			throw new IllegalStateException(Localizer.getLocalizedMessage(
					Device.class, "error.notOpen"));
	}

	/**
	 * Opens this device and sets the default timeout values.
	 * 
	 * @throws FTD2xxException
	 *             if the device can not be opened.
	 */
	public void open() throws FTD2xxException {

		if (isOpen())
			throw new IllegalStateException(Localizer.getLocalizedMessage(
					Device.class, "error.alreadyOpen"));

		logger.info(String.format("Open device %d.", locationID));

		handle = open(locationID);

		// configure device with default values.
		Service.configureDevice(this);
	}

	/**
	 * Opens a device by it`s serial number.
	 * 
	 * @param locationID
	 *            the device`s location within the USB tree.
	 * @return the native handle of the opened device.
	 * @throws FTD2xxException
	 *             if the device can not be opened.
	 */
	private native static long open(long locationID) throws FTD2xxException;

	/**
	 * Closes this device.
	 * 
	 * @throws FTD2xxException
	 *             if the device can not be closed.
	 */
	public void close() throws FTD2xxException {

		checkIsOpen();

		close(handle);

		handle = -1;
	}

	/**
	 * Closes a device.
	 * 
	 * @param handle
	 *            the native handle of the device to close.
	 * @throws FTD2xxException
	 *             if the device can not be closed.
	 */
	private native static void close(long handle) throws FTD2xxException;

	/**
	 * Determines whether this device is open or not.
	 * 
	 * @return <code>true</code> if it is, <code>false</code> otherwise.
	 */
	public boolean isOpen() {

		return handle != -1;
	}

	/**
	 * Resets this device.
	 * 
	 * @throws FTD2xxException
	 *             if the device can not be reset.
	 */
	public void reset() throws FTD2xxException {

		checkIsOpen();

		reset(handle);
	}

	private static native void reset(long handle) throws FTD2xxException;

	/**
	 * Purges the receive buffer of this device.
	 * 
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	public void purgeReceiveBuffer() throws FTD2xxException {

		checkIsOpen();

		purgeReceiveBuffer(handle);
	}

	/**
	 * Purges the receive buffer of a particular device.
	 * 
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	private static native void purgeReceiveBuffer(long handle)
			throws FTD2xxException;

	/**
	 * Purges the transmit buffer of this device.
	 * 
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	public void purgeTransmitBuffer() throws FTD2xxException {

		checkIsOpen();

		purgeTransmitBuffer(handle);
	}

	/**
	 * Purges the transmit buffer of a particular device.
	 * 
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	private static native void purgeTransmitBuffer(long handle)
			throws FTD2xxException;

	/**
	 * Sets the timeout value for both read and write operations.
	 * 
	 * @param timeout
	 *            the new timeout value in milliseconds.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	public void setTimeout(long timeout) throws FTD2xxException {

		checkIsOpen();

		setTimeouts(handle, timeout, timeout);

		readTimeout = timeout;
		writeTimeout = timeout;
	}

	/**
	 * Sets the timeout value for read operations.
	 * 
	 * @param timeout
	 *            the new timeout value in milliseconds (32 bit value).
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	public void setReadTimeout(long timeout) throws FTD2xxException {

		checkIsOpen();

		if (timeout < 0 || timeout > 0xFFFFFFFFL)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidTimeout", timeout));

		setTimeouts(handle, timeout, writeTimeout);

		readTimeout = timeout;
	}

	/**
	 * Retrieves the read timeout value.
	 * 
	 * @return the timeout in milliseconds.
	 */
	public long getReadTimeout() {

		checkIsOpen();

		return readTimeout;
	}

	/**
	 * Retrieves the write timeout value.
	 * 
	 * @return the timeout in milliseconds.
	 */
	public long getWriteTimeout() {

		checkIsOpen();

		return writeTimeout;
	}

	/**
	 * Sets the timeout value for write operations.
	 * 
	 * @param timeout
	 *            the new timeout value in milliseconds.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	public void setWriteTimeout(long timeout) throws FTD2xxException {

		checkIsOpen();

		if (timeout < 0 || timeout > 0xFFFFFFFFL)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidTimeout", timeout));

		setTimeouts(handle, readTimeout, timeout);

		writeTimeout = timeout;
	}

	/**
	 * Sets the timeout values for read and write operations of a particular
	 * device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param readTimeout
	 *            the new read timeout value in milliseconds.
	 * @param writeTimeout
	 *            the new write timeout value in milliseconds.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	private static native void setTimeouts(long handle, long readTimeout,
			long writeTimeout) throws FTD2xxException;

	/**
	 * Retrieves the number of characters in the receive queue.
	 * 
	 * @return the number of characters in the receive queue.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	public long getReceiveQueueStatus() throws FTD2xxException {

		checkIsOpen();

		return getReceiveQueueStatus(handle);
	}

	/**
	 * Retrieves the number of characters in the receive queue of a particular
	 * device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @return the number of characters in the receive queue.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	private static native long getReceiveQueueStatus(long handle)
			throws FTD2xxException;

	/**
	 * Retrieves the number of characters in the transmit queue.
	 * 
	 * @return the number of characters in the transmit queue.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	public long getTransmitQueueStatus() throws FTD2xxException {

		checkIsOpen();

		return getTransmitQueueStatus(handle);
	}

	/**
	 * Retrieves the number of characters in the transmit queue of a particular
	 * device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @return the number of characters in the transmit queue.
	 * @throws FTD2xxException
	 *             if the device can not be accessed.
	 */
	private static native long getTransmitQueueStatus(long handle)
			throws FTD2xxException;

	/**
	 * Retrieves the resetPipeRetryCount.
	 * 
	 * @return the resetPipeRetryCount.
	 */
	public long getResetPipeRetryCount() {

		checkIsOpen();

		return resetPipeRetryCount;
	}

	/**
	 * Sets the new resetPipeRetryCount. The resetPipeRetryCount controls the
	 * maximum number of times that the driver tries to reset a pipe on which an
	 * error has occurred. In noisy environments, where a lot of USB errors
	 * occur, it may be necessary to increase the default value of 50.
	 * 
	 * @param resetPipeRetryCount
	 *            the new value (32 bit).
	 * @throws FTD2xxException
	 *             if the new value can not be set.
	 */
	public void setResetPipeRetryCount(long resetPipeRetryCount)
			throws FTD2xxException {

		checkIsOpen();

		if (resetPipeRetryCount < 0 || resetPipeRetryCount > 0xFFFFFFFFL)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidResetPipeRetryCount",
					resetPipeRetryCount));

		setResetPipeRetryCount(handle, resetPipeRetryCount);
		this.resetPipeRetryCount = resetPipeRetryCount;
	}

	/**
	 * Sets the new resetPipeRetryCount of a device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param count
	 *            the new value.
	 * @throws FTD2xxException
	 *             if the new value can not be set.
	 */
	private static native void setResetPipeRetryCount(long handle, long count)
			throws FTD2xxException;

	/**
	 * Retrieves the current modem status of this device.
	 * 
	 * @return the status.
	 * @throws FTD2xxException
	 *             if the status can not be retrieved.
	 */
	public ModemStatus getModemStatus() throws FTD2xxException {

		checkIsOpen();

		return ModemStatus.byValue(getModemStatus(handle));
	}

	/**
	 * Retrieves the current modem status of a device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @return the status.
	 * @throws FTD2xxException
	 *             if the status can not be retrieved.
	 */
	private static native long getModemStatus(long handle)
			throws FTD2xxException;

	/**
	 * Retrieves the current value of the latency timer. <br>
	 * <br>
	 * <b>Note: </b> this method is only valid for FT232BM and FT245BM devices.
	 * 
	 * @return the latency timer value.
	 * @throws FTD2xxException
	 *             if the value can not be retrieved.
	 */
	public int getLatencyTimer() throws FTD2xxException {

		checkIsOpen();

		return getLatencyTimer(handle);
	}

	/**
	 * Retrieves the current value of the latency timer. <br>
	 * <br>
	 * <b>Note: </b> this method is only valid for FT232BM and FT245BM devices.
	 * 
	 * @param handle
	 *            the native handle of the device for which to retrieve the
	 *            timer value.
	 * @return the latency timer value.
	 * @throws FTD2xxException
	 *             if the value can not be retrieved.
	 */
	private static native int getLatencyTimer(long handle)
			throws FTD2xxException;

	/**
	 * Sets the new latency timer value for this device.
	 * 
	 * @param value
	 *            the new value in milliseconds. The value range is 1 - 255.
	 * @throws FTD2xxException
	 *             if the value can not be set.
	 */
	public void setLatencyTimer(int value) throws FTD2xxException {

		checkIsOpen();

		if (value < 1 || value > 255)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidLatencyTimer", value));

		setLatencyTimer(handle, value);
	}

	/**
	 * Sets the new latency timer value of a particular device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param value
	 *            the new value in milliseconds. The value range is 1 - 255.
	 * @throws FTD2xxException
	 *             if the value can not be set.
	 */
	private static native void setLatencyTimer(long handle, int value)
			throws FTD2xxException;

	/**
	 * Retrieves the current value of the bit bang mode for this device.
	 * 
	 * @return the mode value.
	 * @throws FTD2xxException
	 *             if the mode can not be retrieved.
	 */
	public BitBangMode getBitBangMode() throws FTD2xxException {

		checkIsOpen();

		return BitBangMode.valueOf(getBitBangMode(handle));
	}

	/**
	 * Retrieves the current value of the bit bang mode of a particular device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @return the mode value.
	 * @throws FTD2xxException
	 *             if the mode can not be retrieved.
	 */
	private static native int getBitBangMode(long handle)
			throws FTD2xxException;

	/**
	 * Sets the <i>Bit Bang Mode </i> to use.
	 * 
	 * @param bitMask
	 *            8 bit mask to specify which pin shall serve as an input (0)
	 *            and which one shall be an output pin (1).
	 * @param mode
	 *            {@code true}selects the <i>Bit Bang Mode </i>.
	 * @throws FTD2xxException
	 *             if the value can not be set.
	 */
	public void setBitBangMode(int bitMask, BitBangMode mode)
			throws FTD2xxException {

		checkIsOpen();

		if (bitMask < 0 || bitMask > 0xFFL)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidBitMask", bitMask));

		setBitBangMode(handle, bitMask, mode.value);
	}

	/**
	 * Resets the <i>Bit Bang Mode </i>.
	 * 
	 * @throws FTD2xxException
	 *             if the the device can not be accessed.
	 */
	public void resetBitBangMode() throws FTD2xxException {

		setBitBangMode(0, BitBangMode.RESET);
	}

	/**
	 * Sets the bit bang mode value of a particular device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param bitMask
	 *            8 bit mask to specify which pin shall serve as an input (0)
	 *            and which one shall be an output pin (1).
	 * @param mode
	 *            {@code true}selects the <i>Bit Bang Mode </i>.
	 * @throws FTD2xxException
	 *             if the value can not be set.
	 */
	private static native void setBitBangMode(long handle, int bitMask, int mode)
			throws FTD2xxException;

	/**
	 * Sets the USB transfer sizes of this device.
	 * 
	 * @param rxBufferSize
	 *            the receive buffer size (32 bit).
	 * @param txBufferSize
	 *            the transmit buffer size (32 bit).
	 * @throws FTD2xxException
	 *             if the parameters can not be set.
	 */
	public void setUSBParameters(long rxBufferSize, long txBufferSize)
			throws FTD2xxException {

		checkIsOpen();

		if (rxBufferSize < 0 || rxBufferSize > 0xFFFFFFFFL)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidRxBufferSize", rxBufferSize));

		if (txBufferSize < 0 || txBufferSize > 0xFFFFFFFFL)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidTxBufferSize", txBufferSize));

		setUSBParameters(handle, rxBufferSize, txBufferSize);
	}

	/**
	 * Sets the USB transfer sizes of a particular device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param rxBufferSize
	 *            the receive buffer size.
	 * @param txBufferSize
	 *            the transmit buffer size.
	 * @throws FTD2xxException
	 *             if the parameters can not be set.
	 */
	private static native void setUSBParameters(long handle, long rxBufferSize,
			long txBufferSize) throws FTD2xxException;

	/**
	 * Reads one byte. This method blocks until at least one byte is available.
	 * 
	 * @return the next byte of data, or -1 if the end of the stream is reached.
	 * @throws FTD2xxException
	 *             if the byte can not be read.
	 */
	public int read() throws FTD2xxException {

		byte buffer[] = { -1 }; // if nothing was read -1 will be returned.
		read(buffer);

		return buffer[0];
	}

	/**
	 * Reads all the data in the receive queue. If no data is available, it
	 * blocks until one was received or the end of the stream was detected. This
	 * method has the same effect as read(buffer, 0, buffer.length).
	 * 
	 * @param buffer
	 *            the buffer to store the data in.
	 * @return the number of bytes read.
	 * @throws FTD2xxException
	 *             if the operation can not be performed.
	 */
	public int read(byte[] buffer) throws FTD2xxException {

		checkIsOpen();

		return read(buffer, 0, buffer.length);
	}

	/**
	 * Reads reads a specified number of bytes. If no data is available, it
	 * blocks until one was received or the end of the stream was detected.
	 * 
	 * @param buffer
	 *            the buffer to store the data in.
	 * @param offset
	 *            the index within the <code>buffer</code> of the first byte
	 *            to store.
	 * @param length
	 *            the number of bytes to read.
	 * @return the number of bytes actually read, or -1 if the end of the stream
	 *         was detected.
	 * @throws FTD2xxException
	 *             if the operation can not be performed.
	 */
	public synchronized int read(byte[] buffer, int offset, int length)
			throws FTD2xxException {

		checkIsOpen();

		if (buffer == null || buffer.length == 0)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidBuffer"));

		if (offset < 0 || (offset + length) > buffer.length)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidOffset", buffer.length, offset));

		int result = read(handle, buffer, offset, length);

		if (logger.isLoggable(Level.FINE))
			logger.fine(Localizer.getLocalizedMessage(Device.class,
					"read.logger.fine", //$NON-NLS-1$
					format(buffer, offset, result)));

		return result;
	}

	/**
	 * Retrieves this device`s {@link InputStream}. This intended for
	 * applications that use standard Java I/O for communication.
	 * 
	 * @return the input stream.
	 */
	public InputStream getInputStream() {

		checkIsOpen();

		return new DeviceInputStream(this);
	}

	/**
	 * Retrieves this device`s {@link OutputStream}. This intended for
	 * applications that use standard Java I/O for communication.
	 * 
	 * @return the output stream.
	 */
	public OutputStream getOutputStream() {

		checkIsOpen();

		return new DeviceOututStream(this);
	}

	/**
	 * Reads reads a specified number of bytes from a particular device. If no
	 * data is available, it blocks until one was received or the end of the
	 * stream was detected.
	 * 
	 * @param handle
	 *            the native device handle.
	 * @param buffer
	 *            the buffer to store the data in.
	 * @param offset
	 *            the index within the <code>buffer</code> of the first byte
	 *            to store.
	 * @param length
	 *            the number of bytes to read.
	 * @return the number of bytes actually read, or -1 if the end of the stream
	 *         was detected.
	 * @throws FTD2xxException
	 *             if the operation can not be performed.
	 */
	private synchronized static native int read(long handle, byte[] buffer,
			int offset, int length) throws FTD2xxException;

	/**
	 * Writes one byte to this device`s transmit queue.
	 * 
	 * @param b
	 *            the byte to write.
	 * @throws FTD2xxException
	 *             if the operation can not be performed.
	 */
	public void write(int b) throws FTD2xxException {

		write(new byte[] { (byte) b });
	}

	/**
	 * Writes data to this device`s transmit queue.
	 * 
	 * @param buffer
	 *            the buffer that stores the data to write.
	 * @throws FTD2xxException
	 *             if the operation can not be performed.
	 */
	public void write(byte[] buffer) throws FTD2xxException {

		write(buffer, 0, buffer.length);
	}

	/**
	 * Writes data to this device`s transmit queue.
	 * 
	 * @param buffer
	 *            the buffer that stores the data to write.
	 * @param offset
	 *            the index of the first byte to write.
	 * @param length
	 *            the number of bytes to write.
	 * @throws FTD2xxException
	 *             if the operation can not be performed.
	 */
	public synchronized void write(byte[] buffer, int offset, int length)
			throws FTD2xxException {

		checkIsOpen();

		if (buffer == null || buffer.length == 0)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidBuffer"));

		if (offset < 0 || (offset + length) > buffer.length)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Device.class, "error.invalidOffset", buffer.length, offset));

		if (logger.isLoggable(Level.FINE))
			logger.fine(Localizer.getLocalizedMessage(Device.class,
					"write.logger.fine", //$NON-NLS-1$
					format(buffer, offset, length)));

		write(handle, buffer, offset, length);
	}

	/**
	 * Writes data to a particular device`s transmit queue.
	 * 
	 * @param handle
	 *            the device`s native handle.
	 * @param buffer
	 *            the buffer that stores the data to write.
	 * @param offset
	 *            the index of the first byte to write.
	 * @param length
	 *            the number of bytes to write.
	 * @throws FTD2xxException
	 *             if the operation can not be performed.
	 */
	private static native void write(long handle, byte[] buffer, int offset,
			int length) throws FTD2xxException;

	private String format(byte[] bytes, int offset, int numBytes) {

		StringBuilder buffer = new StringBuilder();

		for (int i = offset; i < numBytes; i++) {
			buffer.append(String.format("%02X ", bytes[i] & 0xFF)); //$NON-NLS-1$        
		}

		return buffer.toString(); //$NON-NLS-1$
	}

	/**
	 * Retrieves the EEPROM of this device.
	 * 
	 * @return the EEPROM.
	 */
	public synchronized EEPROM getEEPROM() {

		return eeprom;
	}
}
