package com.ftdichip.ftd2xx;

import javax.util.Localizer;

/**
 * Provides access to a FTD2xx device`s EEPROM.
 * 
 * @author Mike Werner
 */
public class EEPROM {

	/**
	 * Owning device.
	 */
	private Device device;

	private DeviceDescriptor deviceDescriptor;

	/**
	 * Creates a new <code>EEPROM</code>.
	 * 
	 * @param device
	 *            the device this <code>EEPROM</code> is associated with.
	 */
	EEPROM(Device device) {

		this.device = device;
	}

	private void checkIsOpen() {

		if (!device.isOpen())
			throw new IllegalStateException(Localizer.getLocalizedMessage(
					EEPROM.class, "error.notOpen"));
	}

	/**
	 * Retrieves this devices device descriptor.
	 * 
	 * @return the device descriptor.
	 * @throws FTD2xxException
	 *             if the device descriptor can not be read from the EEPROM.
	 */
	DeviceDescriptor getDeviceDescriptor() throws FTD2xxException {

		if (deviceDescriptor == null)
			deviceDescriptor = readDeviceDescriptor();

		return deviceDescriptor;
	}

	/**
	 * Reads the device descriptor from the devices EEPROM.
	 * 
	 * @return the device descriptor of the device that owns this EEPROM.
	 *         According to the device a {@code DeviceDescriptor}object is
	 *         returned or one of it`s sub-classes.
	 * @throws FTD2xxException
	 *             if the device descriptor can not be read.
	 */
	public DeviceDescriptor readDeviceDescriptor() throws FTD2xxException {

		checkIsOpen();

		return readDeviceDescriptor(device.getHandle());
	}

	/**
	 * Reads the device descriptor of a particular device out of it`s EEPROM.
	 * 
	 * @param handle
	 *            the handle of the device.
	 * @return the device descriptor of the device that owns this EEPROM.
	 *         According to the device a {@code DeviceDescriptor}object is
	 *         returned or one of it`s sub-classes.
	 * @throws FTD2xxException
	 *             if the device descriptor can not be read.
	 */
	private static native DeviceDescriptor readDeviceDescriptor(long handle)
			throws FTD2xxException;

	/**
	 * Writes the device descriptor of the device that is the owner of this
	 * EEPROM.
	 * 
	 * @param desc
	 *            the device descriptor to be written.
	 * @throws FTD2xxException
	 *             if the device descriptor can not be read.
	 */
	public void writeDeviceDescriptor(DeviceDescriptor desc)
			throws FTD2xxException {

		checkIsOpen();

		desc.validate();

		writeDeviceDescriptor(device.getHandle(), desc);

		deviceDescriptor = desc;
	}

	/**
	 * Writes the device descriptor of a particular device to it`s EEPROM.
	 * 
	 * @param handle
	 *            the handle of the device.
	 * @param desc
	 *            the device descriptor to be written.
	 * @throws FTD2xxException
	 *             if the device descriptor can not be read.
	 */
	private static native void writeDeviceDescriptor(long handle,
			DeviceDescriptor desc) throws FTD2xxException;

	/**
	 * Retrieves the size of the User Area within the EEPROM.
	 * 
	 * @return the size of the User Area in bytes.
	 * @throws FTD2xxException
	 *             if the size can not be read.
	 */
	public int getUserAreaSize() throws FTD2xxException {

		checkIsOpen();

		return readUserAreaSize(device.getHandle());
	}

	/**
	 * Reads the User Area size of a particular device.
	 * 
	 * @param handle
	 *            the device`s native handle.
	 * @return the size in bytes.
	 * @throws FTD2xxException
	 *             if the size can not be read.
	 */
	private static native int readUserAreaSize(long handle)
			throws FTD2xxException;

	/**
	 * Reads the contents of the User Area.
	 * 
	 * @param data
	 *            the buffer to store the data in.
	 * @return the number of bytes read.
	 * @throws FTD2xxException
	 *             if the data can not be read.
	 */
	public int readUserArea(byte[] data) throws FTD2xxException {

		checkIsOpen();

		return readUserArea(device.getHandle(), data);
	}

	/**
	 * Reads the contents of the User Area of a particular device.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param data
	 *            the buffer to store the data in.
	 * @return the number of bytes read.
	 * @throws FTD2xxException
	 *             if the data can not be read.
	 */
	private static native int readUserArea(long handle, byte[] data)
			throws FTD2xxException;

	/**
	 * Writes the new data to the User Area.
	 * 
	 * @param data
	 *            the data to be written.
	 * @throws FTD2xxException
	 *             if the data can not be written.
	 */
	public void writeUserArea(byte[] data) throws FTD2xxException {

		checkIsOpen();

		writeUserArea(device.getHandle(), data);
	}

	/**
	 * Writes data to the USer Area of a particular device.
	 * 
	 * @param handle
	 *            the handle of the device.
	 * @param data
	 *            the data to be written.
	 * @throws FTD2xxException
	 *             if the data can not be written.
	 */
	private static native void writeUserArea(long handle, byte[] data)
			throws FTD2xxException;

	/**
	 * Erases the entire contents of an EEPROM, including the user area.
	 * 
	 * @throws FTD2xxException
	 *             if the EEPROM can not be erased.
	 */
	public void erase() throws FTD2xxException {

		checkIsOpen();

		erase(device.getHandle());
	}

	/**
	 * Erases the entire contents of an EEPROM, including the user area.
	 * 
	 * @param handle
	 *            the handle of the device.
	 * @throws FTD2xxException
	 *             if the EEPROM can not be erased.
	 */
	private static native void erase(long handle) throws FTD2xxException;
}
