package com.ftdichip.ftd2xx;

import javax.util.Localizer;

/**
 * Provides access to a device`s serial port.
 * 
 * @author Mike Werner
 */
public class Port {

	private Device device;

	/**
	 * Creates a new <code>Port</code>.
	 * 
	 * @param device
	 *            the device this {@code Port}belongs to.
	 */
	Port(Device device) {

		this.device = device;
	}

	/**
	 * Resets this port on the according device.
	 * 
	 * @throws FTD2xxException
	 *             if the port can not be reset.
	 */
	public void reset() throws FTD2xxException {

		reset(device.getHandle());
	}

	/**
	 * Resets a device`s port.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @throws FTD2xxException
	 *             if the port can not be reset.
	 */
	private static native void reset(long handle) throws FTD2xxException;

	/**
	 * Sets the baud rate of the device owning this {@code Port}.
	 * 
	 * @param baudRate
	 *            the new baud rate. The range of the value is 32 bit.
	 * @throws FTD2xxException
	 *             if the baud rate can not be set.
	 */
	public void setBaudRate(long baudRate) throws FTD2xxException {

		// check the upper bound because the native API expects 32 bit values.
		if (baudRate > 0xFFFFFFFFL)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Port.class, "error.invalidBaudRate", baudRate));

		setBaudRate(device.getHandle(), baudRate);
	}

	/**
	 * Sets the baud rate of a device.
	 * 
	 * @param baudRate
	 *            the new baud rate. The range of the value is 32 bit.
	 * @throws FTD2xxException
	 *             if the baud rate can not be set.
	 */
	private static native void setBaudRate(long handle, long baudRate)
			throws FTD2xxException;

	/**
	 * Sets the divisor used for non-standard baud rates. <br>
	 * <br>
	 * <b>Note: </b> The application note "Setting Baude rates for the
	 * FT8U232AM", which is available on <href
	 * link=https://www.ftdichip.com>www.ftdichip.com </href>, describes how to
	 * calculate the divisor for a non standard baude rate.
	 * 
	 * @param divisor
	 *            the new divisor. The range of the value is 16 bit.
	 * @throws FTD2xxException
	 *             if the divisor can not be set.
	 */
	public void setDivisor(int divisor) throws FTD2xxException {

		// check the upper bound because the native API expects 16 bit values.
		if (divisor < 0 || divisor > 0xFFFF)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Port.class, "error.invalidDivisor", divisor));

		setDivisor(device.getHandle(), divisor);
	}

	/**
	 * Sets the divisor of a device`s port used for non-standard baud rates.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param divisor
	 *            the divisor.
	 * @throws FTD2xxException
	 *             if the divisor can not be set.
	 */
	private static native void setDivisor(long handle, int divisor)
			throws FTD2xxException;

	/**
	 * Sets the data characteristics for this port.
	 * 
	 * @param dataBits
	 *            the number of data bits used.
	 * @param stopBits
	 *            the number of stop bits used.
	 * @param parity
	 *            the parity scheme used.
	 * @throws FTD2xxException
	 *             if the data characteristics can not be set.
	 */
	public void setDataCharacteristics(DataBits dataBits, StopBits stopBits,
			Parity parity) throws FTD2xxException {

		setDataCharacteristics(device.getHandle(), dataBits.value,
				stopBits.value, parity.value);
	}

	/**
	 * Sets the data characteristics for a particular device`s port.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param dataBits
	 *            the number of data bits used.
	 * @param stopBits
	 *            the number of stop bits used.
	 * @param parity
	 *            the parity scheme used.
	 * @throws FTD2xxException
	 *             if the data characteristics can not be set.
	 */
	private static native void setDataCharacteristics(long handle,
			int dataBits, int stopBits, int parity) throws FTD2xxException;

	/**
	 * Sets the flow control mode for this port. <br>
	 * <br>
	 * <b>Note: </b> This method only supports modes different from XON XOFF,
	 * because for this mode additional parameters are needed. In order to set
	 * XON XOFF mode use {@link #setFlowControl(FlowControl, char, char)}
	 * instead.
	 * 
	 * @param flowControl
	 *            the new flow control mode.
	 * @throws FTD2xxException
	 *             if the flow control mode can not be set.
	 */
	public void setFlowControl(FlowControl flowControl) throws FTD2xxException {

		if (flowControl == FlowControl.XON_XOFF)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Port.class, "error.setFlowControl1.invalidUsage"));

		setFlowControl(device.getHandle(), flowControl.value, (char) 0,
				(char) 0);
	}

	/**
	 * Sets the flow control mode for this port. <br>
	 * <br>
	 * <b>Note: </b> This method only supports the XON XOFF mode, because for
	 * this mode additional parameters are needed. In order to set different
	 * modes use {@link #setFlowControl(FlowControl)} instead.
	 * 
	 * @param flowControl
	 *            the new flow control mode.
	 * @param xon
	 *            the character to signal XON.
	 * @param xoff
	 *            the character to signal XOFF.
	 * @throws FTD2xxException
	 *             if the flow control mode can not be set.
	 */
	public void setFlowControl(FlowControl flowControl, char xon, char xoff)
			throws FTD2xxException {

		if (flowControl != FlowControl.XON_XOFF)
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					Port.class, "error.setFlowControl2.invalidUsage"));

		setFlowControl(device.getHandle(), flowControl.value, xon, xoff);
	}

	/**
	 * Sets the flow control mode of a particular device`s port.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param flowControl
	 *            the new flow control mode.
	 * @param xon
	 *            the character to signal XON (only used for XON XOFF mode).
	 * @param xoff
	 *            the character to signal XOFF (only used for XON XOFF mode).
	 * @throws FTD2xxException
	 *             if the flow control mode can not be set.
	 */
	private static native void setFlowControl(long handle, int flowControl,
			char xon, char xoff) throws FTD2xxException;

	/**
	 * Sets or clears the <i>Data Terminal Ready </i> signal.
	 * 
	 * @param value
	 *            if {@code true}sets the signal, otherwise the it will be
	 *            cleared.
	 * @throws FTD2xxException
	 *             if the signal can not be set/cleared.
	 */
	public void setDTR(boolean value) throws FTD2xxException {

		setDTR(device.getHandle(), value);
	}

	/**
	 * Sets or clears the <i>Data Terminal Ready </i> signal of a device`s port.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param value
	 *            if {@code true}sets the signal, otherwise the it will be
	 *            cleared.
	 * @throws FTD2xxException
	 *             if the signal can not be set/cleared.
	 */
	private static native void setDTR(long handle, boolean value)
			throws FTD2xxException;

	/**
	 * Sets or clears the <i>Request To Send </i> signal.
	 * 
	 * @param value
	 *            if {@code true}sets the signal, otherwise the it will be
	 *            cleared.
	 * @throws FTD2xxException
	 *             if the signal can not be set/cleared.
	 */
	public void setRTS(boolean value) throws FTD2xxException {

		setRTS(device.getHandle(), value);
	}

	/**
	 * Sets or clears the <i>Request To Send </i> signal of a particular
	 * device`s port.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param value
	 *            if {@code true}sets the signal, otherwise the it will be
	 *            cleared.
	 * @throws FTD2xxException
	 *             if the signal can not be set/cleared.
	 */
	private static native void setRTS(long handle, boolean value)
			throws FTD2xxException;

	/**
	 * Sets the <i>BREAK </i> condition for this device to on/off.
	 * 
	 * @param value
	 *            if {@code true}the <i>BREAK </i> condition is set to ON,
	 *            otherwise to OFF.
	 * @throws FTD2xxException
	 *             if the <i>BREAK </i> condition can not be set.
	 */
	public void setBreakOn(boolean value) throws FTD2xxException {

		setBreakOn(device.getHandle(), value);
	}

	/**
	 * Sets the <i>BREAK </i> condition for a particular device to on/off.
	 * 
	 * @param handle
	 *            the native handle of the device.
	 * @param value
	 *            if {@code true}the <i>BREAK </i> condition is set to ON,
	 *            otherwise to OFF.
	 * @throws FTD2xxException
	 *             if the <i>BREAK </i> condition can not be set.
	 */
	private static native void setBreakOn(long handle, boolean value)
			throws FTD2xxException;

}
