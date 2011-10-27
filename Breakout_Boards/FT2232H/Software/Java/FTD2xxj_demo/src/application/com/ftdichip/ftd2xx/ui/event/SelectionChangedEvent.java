package com.ftdichip.ftd2xx.ui.event;

import java.util.EventObject;

import com.ftdichip.ftd2xx.Device;


/**
 * Event to notify about selection changes.
 * 
 * @author Mike Werner
 */
public class SelectionChangedEvent extends EventObject {

    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    private Device affectedDevice;
    
    /**
     * 
     * Creates a new <code>SelectionChangedEvent</code>.
     *
     * @param source the event source.
     * @param device the affected device.
     */
    public SelectionChangedEvent(Object source, Device device) {
        super(source);
        
        affectedDevice = device;
    }
    
    /**
     * Retrieves the device affected by this selection.
     * 
     * @return the selected device.
     */
    public Device getAffectedDevice() {

        return affectedDevice;
    }
}
