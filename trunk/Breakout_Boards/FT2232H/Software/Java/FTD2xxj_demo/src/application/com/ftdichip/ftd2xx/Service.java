package com.ftdichip.ftd2xx;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.util.Localizer;
import javax.util.property.Property;
import javax.util.property.PropertyPersistenceManager;

/**
 * Utility class to retrieve and configure connected devices. <br>
 * <br>
 * <b>Note: </b>There are a set of system properties to initialize a device. The
 * following list shows them with there default values.<br>
 * <br>
 * <b>Note: </b> Every property's value that is greater than {@code 0} will be
 * used for device initialisation. <br>
 * <b>Vital properties:</b> <br>
 * <br>
 * <ul>
 * <li><b>com.ftdichip.ftd2xx.Device.configFile </b>=ftd2xxj.properties // File
 * used to load external settings. May be specified as a full {@link URL}.</li>
 * <li><b>com.ftdichip.ftd2xx.Device.writeTimeout</b> = 300</li>
 * <li><b>com.ftdichip.ftd2xx.Device.readTimeout</b> = 300</li>
 * </ul>
 * <br>
 * <br>
 * <b>Optional properties: </b> <br>
 * <br>
 * <ul>
 * <li><b>com.ftdichip.ftd2xx.Device.latencyTimer</b></li>
 * <li><b>com.ftdichip.ftd2xx.Device.usbReceiveBufferSize</b></li>
 * <li><b>com.ftdichip.ftd2xx.Device.usbTransmitBufferSize</b></li>
 * <li><b>com.ftdichip.ftd2xx.Device.resetPipeRetryCount</b></li>
 * </ul>
 * <br>
 * <br>
 * For detailed description of the values see the <i>ftd2xxj </i> API.
 * 
 * @author Mike Werner
 * @see com.ftdichip.ftd2xx.Device
 */
public final class Service {

    private final static Logger logger = Logger.getLogger(Service.class
            .getName());
    
    /**
     * Property to to access the configuration file value.
     */
    @Property(defaultValue = " ")
    private static String configFile;

    /**
     * Property to to access the write timeout value.
     */
    @Property(key="com.ftdichip.ftd2xx.Device.writeTimeout", defaultValue = "300")
    private static int writeTimeout;

    /**
     * Property to to access the read timeout value.
     */
    @Property(key="com.ftdichip.ftd2xx.Device.readTimeout", defaultValue = "300")
    private static int readTimeout;

    /**
     * Property to to access the latency timer value.
     */
    @Property(key="com.ftdichip.ftd2xx.Device.latencyTimer", defaultValue = "-1")
    private static int latencyTimer;

    /**
     * Property to to access the resetPipeRetryCount value.
     */
    @Property(key="com.ftdichip.ftd2xx.Device.resetPipeRetryCount", defaultValue = "-1")
    private static int resetPipeRetryCount;

    /**
     * Property to to access the usbReceiveBufferSize value.
     */
    @Property(key="com.ftdichip.ftd2xx.Device.usbReceiveBufferSize", defaultValue = "-1")
    private static int usbReceiveBufferSize;

    /**
     * Property to to access the usbTransmitBufferSize value.
     */
    @Property(key="com.ftdichip.ftd2xx.Device.usbTransmitBufferSize", defaultValue = "-1")
    private static int usbTransmitBufferSize;

    static {
        try {
            System.loadLibrary("ftd2xxj");

            if (configFile != null)
                loadProperties();

            initializeProperties();
        } catch (IOException e) {
            logger.log(Level.SEVERE, Localizer.getLocalizedMessage(
                    Service.class, "initProperties.error"), e); //$NON-NLS-1$
        }
    }

    private static void loadProperties() throws FileNotFoundException,
            IOException {

        URL url = null;

        /*
         * Is the configuration file specified as a complete URL?
         */
        try {
            url = new URL(configFile);
        } catch (MalformedURLException e) {
            /*
             * If not assume it is an ordinary file.
             */
            url = new File(configFile).toURI().toURL();
        }

        logger.config(Localizer.getLocalizedMessage(Service.class,
                "loadProperties.logger.config", url)); //$NON-NLS-1$

        InputStream in = url.openStream();

        loadProperties(in);

        in.close();
    }

    private static void loadProperties(InputStream in) throws IOException {

        System.getProperties().load(in);
    }

    private static void initializeProperties() {

        try {
            PropertyPersistenceManager.initializeFromSystemProperties(Service.class);
        } catch (Exception e) {
            throw new RuntimeException(Localizer.getLocalizedMessage(
                    Service.class, "initializeProperties.error"), e);
        }
    }

    /**
     * Configures an opened device according to the system properties. Prior to
     * configuration the device is reset and it`s buffers are cleared.
     * 
     * @param device
     *            the device to be configured.
     * @throws FTD2xxException
     *             if the device can not be accessed.
     */
    static void configureDevice(Device device) throws FTD2xxException {

        device.reset();
        device.purgeReceiveBuffer();
        device.purgeTransmitBuffer();

        if (writeTimeout >= 0) {
            logger.config(String.format("writeTimeout: %d", writeTimeout));
            device.setWriteTimeout(writeTimeout);
        }

        if (readTimeout >= 0) {
            logger.config(String.format("readTimeout: %d", readTimeout));
            device.setReadTimeout(readTimeout);
        }

        if (latencyTimer >= 0) {
            logger.config(String.format("latencyTimer: %d", latencyTimer));
            device.setLatencyTimer(latencyTimer);
        }

        if (usbReceiveBufferSize >= 0 && usbTransmitBufferSize >= 0) {
            logger.config(String.format("usbReceiveBufferSize: %d", usbReceiveBufferSize));
            logger.config(String.format("usbTransmitBufferSize: %d", usbTransmitBufferSize));
            device
                    .setUSBParameters(usbReceiveBufferSize,
                            usbTransmitBufferSize);
        }

        if (resetPipeRetryCount >= 0) {
            logger.config(String.format("resetPipeRetryCount: %d", resetPipeRetryCount));
            device.setResetPipeRetryCount(resetPipeRetryCount);
        }
    }

    private Service() {

        // empty to prevent from instantiation
    }

    /**
     * Lists all currently attached devices.
     * 
     * @return All connected devices. If no device is connected an empty array
     *         will be returned.
     * @throws FTD2xxException
     *             if the information cannot be retrieved.
     */
    public static native Device[] listDevices() throws FTD2xxException;

    /**
     * Lists all devices of a particular type.
     * 
     * @param type
     *            the type to search for.
     * @return the list of devices found.
     * @throws FTD2xxException
     *             if the devices can not be listed.
     */
    public static Device[] listDevicesByType(DeviceType type)
            throws FTD2xxException {

        List<Device> devices = new ArrayList<Device>();

        for (Device d : listDevices()) {
            if (d.getType() == type)
                devices.add(d);
        }

        return devices.toArray(new Device[devices.size()]);
    }

    /**
     * Lists all devices which match a particular product description.
     * 
     * @param description
     *            the description to search for.
     * @return the devices found.
     * @throws FTD2xxException
     *             if FTD2xx API can not be accessed.
     */
    public static Device[] listDevicesByDescription(String description)
            throws FTD2xxException {

        List<Device> devices = new ArrayList<Device>();

        for (Device d : listDevices()) {
            try {
                DeviceDescriptor desc = d.getDeviceDescriptor();
                if (desc.getProductDescription().equals(description))
                    devices.add(d);
            } catch (FTD2xxException e) {
                logger.log(Level.SEVERE, "Failed to access device descriptor.",
                        e);
            }
        }

        return devices.toArray(new Device[devices.size()]);
    }

    /**
     * Lists all devices with a particular serial number.
     * 
     * @param serialNumber
     *            the serial number to search for.
     * @return the list of devices found.
     * @throws FTD2xxException
     *             if the devices can not be listed.
     */
    public static Device[] listDevicesBySerialNumber(String serialNumber)
            throws FTD2xxException {

        List<Device> devices = new ArrayList<Device>();

        for (Device d : listDevices()) {
            if (d.getDeviceDescriptor().getSerialNumber() == serialNumber) {
                devices.add(d);
            }
        }

        return devices.toArray(new Device[devices.size()]);
    }

    /**
     * Starts the input task of a device.
     * 
     * @param device
     *            the device for which to start it`s input task.
     * @throws FTD2xxException
     *             if the input task can not be started (e.g. it is already
     *             started).
     */
    public void startInputTask(Device device) throws FTD2xxException {

        startInputTask(device.getHandle());
    }

    /**
     * Starts the input task of a device.
     * 
     * @param handle
     *            the native handle of the device for which to start it`s input
     *            task.
     * @throws FTD2xxException
     *             if the input task can not be started (e.g. it is already
     *             started).
     */
    private static native void startInputTask(long handle)
            throws FTD2xxException;

    /**
     * Stops the input task of a device.
     * 
     * @param device
     *            the device for which to stop it`s input task.
     * @throws FTD2xxException
     *             if the input task can not be stopped (e.g. it is already
     *             stopped).
     */
    public void stopInputTask(Device device) throws FTD2xxException {

        stopInputTask(device.getHandle());
    }

    /**
     * Stops the input task of a device.
     * 
     * @param handle
     *            the native handle of the device for which to stop it`s input
     *            task.
     * @throws FTD2xxException
     *             if the input task can not be stopped (e.g. it is already
     *             stopped).
     */
    private static native void stopInputTask(long handle)
            throws FTD2xxException;
}
