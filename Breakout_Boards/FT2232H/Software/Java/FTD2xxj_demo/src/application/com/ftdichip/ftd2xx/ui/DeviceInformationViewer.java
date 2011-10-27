package com.ftdichip.ftd2xx.ui;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;

/**
 * Interface for viewers that display {@link com.ftdichip.ftd2xx.Device}
 * dependent information.
 * 
 * @author Mike Werner
 */
public interface DeviceInformationViewer {

    /**
     * Updates the viewers particular information.
     * 
     * @param device
     *            the device for which to show the information.
     * @throws FTD2xxException
     *             if the viewer can not retrieve the particular information
     *             from the device.
     */
    public void update(Device device) throws FTD2xxException;

    /**
     * Clears the viewer's contents.
     */
    public void clear();
}
