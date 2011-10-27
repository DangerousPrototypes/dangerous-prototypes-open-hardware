package com.ftdichip.ftd2xx;

import javax.util.Localizer;

/**
 * Stores all data, describing a particular device. This data is stored within
 * the EEPROM and can be written as well. For a detailed description of the date
 * see FTD`s publications. <br>
 * <br>
 * <b>Note: </b>This <code>DeviceDescriptor</code> stores only the data common
 * to all devices, old and new ones. Data that is only available for newer
 * devices is specified by particular sub-classes. <br>
 * <br>
 * <b>For a more detailed description of the fields see the ftd2xx-API
 * specification. </b>
 * 
 * @author Mike Werner
 */
public class DeviceDescriptor {

	private static final int MAX_HEADER_LENGTH = 48;

	/**
	 * Header must be 0.
	 */
	private long signature1 = 0;

	/**
	 * Header must be 0xFFFFFFFF.
	 */
	private long signature2 = 0xFFFFFFFF;

	/**
	 * Version of this descriptor. <br>
	 * <br>
	 * <ul>
	 * <li>0 = Standard data available to all devices.</li>
	 * <li>1 = FT2232C extensions to the standard data.</li>
	 * </ul>
	 */
	private long version = 0;

	/**
	 * The ID of the vendor.
	 */
	private int vendorID;

	/**
	 * The ID of the product.
	 */
	private int productID;

	/**
	 * The manufacturer of the device.
	 */
	private String manufacturer = "";

	/**
	 * The manufacturer`s ID.
	 */
	private String manufacturerID = "";

	/**
	 * A human readable description of the product.
	 */
	private String productDescription = "";

	/**
	 * The serial number of the product.
	 */
	private String serialNumber = "";

	/**
	 * The maximum power this product needs. The value may range from 1 to 500.
	 */
	private int maxPower;

	/**
	 * If <code>true</code> the device supports plug and play.
	 */
	private boolean pnpEnabled;

	/**
	 * If <code>true</code> the device has it`s own power supply. If
	 * <code>false</code> it uses the power provided by the USB.
	 */
	private boolean selfPowered;

	/**
	 * If <code>true</code> the device if capable to be woke up remotely.
	 */
	private boolean remoteWakeupCapable;

	/**
	 * Checks if this device descriptor is valid.
	 * 
	 * @throws InvalidDeviceDescriptorException
	 *             if the total number of characters for manufacturer,
	 *             manufacturerID, description and serialNumber is greater than
	 *             48.
	 */
	protected void validate() throws InvalidDeviceDescriptorException {

		if ((manufacturer.length() + manufacturerID.length()
				+ productDescription.length() + serialNumber.length()) > MAX_HEADER_LENGTH)
			throw new InvalidDeviceDescriptorException(Localizer
					.getLocalizedMessage(DeviceDescriptor.class,
							"error.invalidHeaderLength", MAX_HEADER_LENGTH));
	}

	/**
	 * Retrieves the manufacturer.
	 * 
	 * @return the manufacturer.
	 */
	public String getManufacturer() {

		return manufacturer;
	}

	/**
	 * Sets the new manufacturer.
	 * 
	 * @param manufacturer
	 *            The new manufacturer.
	 */
	public void setManufacturer(String manufacturer) {

		if (manufacturer == null)
			this.manufacturer = "";

		this.manufacturer = manufacturer;
	}

	/**
	 * Retrieves the manufacturerID.
	 * 
	 * @return the manufacturerID.
	 */
	public String getManufacturerID() {

		return manufacturerID;
	}

	/**
	 * Sets the new manufacturerID.
	 * 
	 * @param manufacturerID
	 *            The manufacturerID to set.
	 */
	public void setManufacturerID(String manufacturerID) {

		if (manufacturerID == null)
			this.manufacturerID = "";

		this.manufacturerID = manufacturerID;
	}

	/**
	 * Retrieves the maxPower.
	 * 
	 * @return the maxPower.
	 */
	public int getMaxPower() {

		return maxPower;
	}

	/**
	 * Sets the new maxPower value.
	 * 
	 * @param maxPower
	 *            The maxPower to set.
	 */
	public void setMaxPower(int maxPower) {

		this.maxPower = maxPower;
	}

	/**
	 * Retrieves the pnpEnabled value.
	 * 
	 * @return the pnpEnabled.
	 */
	public boolean isPnpEnabled() {

		return pnpEnabled;
	}

	/**
	 * Sets the new pnpEnabled value.
	 * 
	 * @param pnpEnabled
	 *            The pnpEnabled to set.
	 */
	public void setPnpEnabled(boolean pnpEnabled) {

		this.pnpEnabled = pnpEnabled;
	}

	/**
	 * Retrieves the productDescription.
	 * 
	 * @return the productDescription.
	 */
	public String getProductDescription() {

		return productDescription;
	}

	/**
	 * Sets the new productDescription.
	 * 
	 * @param productDescription
	 *            The productDescription to set.
	 */
	public void setProductDescription(String productDescription) {

		if (productDescription == null)
			this.productDescription = "";

		this.productDescription = productDescription;
	}

	/**
	 * Retrieves the productID.
	 * 
	 * @return the productID.
	 */
	public int getProductID() {

		return productID;
	}

	/**
	 * Sets the new productID.
	 * 
	 * @param productID
	 *            The productID to set.
	 */
	public void setProductID(int productID) {

		this.productID = productID;
	}

	/**
	 * Retrieves the remoteWakeupCapable value.
	 * 
	 * @return the remoteWakeupCapable.
	 */
	public boolean isRemoteWakeupCapable() {

		return remoteWakeupCapable;
	}

	/**
	 * Sets the new remoteWakeupCapable value.
	 * 
	 * @param remoteWakeupCapable
	 *            The remoteWakeupCapable to set.
	 */
	public void setRemoteWakeupCapable(boolean remoteWakeupCapable) {

		this.remoteWakeupCapable = remoteWakeupCapable;
	}

	/**
	 * Retrieves the selfPowered value.
	 * 
	 * @return the selfPowered.
	 */
	public boolean isSelfPowered() {

		return selfPowered;
	}

	/**
	 * Sets the new selfPowered value.
	 * 
	 * @param selfPowered
	 *            The selfPowered to set.
	 */
	public void setSelfPowered(boolean selfPowered) {

		this.selfPowered = selfPowered;
	}

	/**
	 * Retrieves the serilNumber.
	 * 
	 * @return the serialNumber.
	 */
	public String getSerialNumber() {

		return serialNumber;
	}

	/**
	 * Sets the new serialNumber.
	 * 
	 * @param serialNumber
	 *            The serialNumber to set.
	 */
	public void setSerialNumber(String serialNumber) {

		this.serialNumber = serialNumber;
	}

	/**
	 * Retrieves the signature1.
	 * 
	 * @return the signatue1.
	 */
	public long getSignature1() {

		return signature1;
	}

	/**
	 * Sets the value of signature1.
	 * 
	 * @param signatue1
	 *            The signatue1 to set.
	 */
	public void setSignature1(long signatue1) {

		this.signature1 = signatue1;
	}

	/**
	 * Retrieves the signature2.
	 * 
	 * @return the signture2.
	 */
	public long getSignature2() {

		return signature2;
	}

	/**
	 * Sets the new signature2.
	 * 
	 * @param signture2
	 *            The signture2 to set.
	 */
	public void setSignature2(long signture2) {

		this.signature2 = signture2;
	}

	/**
	 * Retrieves the vendorID.
	 * 
	 * @return the vendorID.
	 */
	public int getVendorID() {

		return vendorID;
	}

	/**
	 * Sets the new vendorID.
	 * 
	 * @param vendorID
	 *            The vendorID to set.
	 */
	public void setVendorID(int vendorID) {

		this.vendorID = vendorID;
	}

	/**
	 * Retrieves the version.
	 * 
	 * @return the version.
	 */
	public long getVersion() {

		return version;
	}

	/**
	 * Sets the new version.
	 * 
	 * @param version
	 *            The version to set.
	 */
	public void setVersion(long version) {

		this.version = version;
	}
}
