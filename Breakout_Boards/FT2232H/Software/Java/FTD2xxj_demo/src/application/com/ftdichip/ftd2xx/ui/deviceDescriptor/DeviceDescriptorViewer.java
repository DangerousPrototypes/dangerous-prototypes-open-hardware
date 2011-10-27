package com.ftdichip.ftd2xx.ui.deviceDescriptor;

import java.awt.BorderLayout;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;
import com.ftdichip.ftd2xx.ui.DeviceInformationViewer;

/**
 * Viewer to show the contents of a device descriptor.
 * 
 * @author Mike Werner
 */
public class DeviceDescriptorViewer extends JPanel implements
        DeviceInformationViewer {

    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    private JTable jTable = null;

    private JScrollPane jScrollPane = null;

    /**
     * This is the default constructor
     */
    public DeviceDescriptorViewer() {

        initialize();
    }

    /**
     * This method initializes this.
     */
    private void initialize() {
        
        this.setLayout(new BorderLayout());
        this.add(getJScrollPane(), BorderLayout.CENTER);
    }

    /**
     * This method initializes jTable
     * 
     * @return javax.swing.JTable
     */
    private JTable getJTable() {

        if (jTable == null) {
            jTable = new JTable();
            jTable.setModel(new DeviceDescriptorTableModel());
        }
        return jTable;
    }

    /**
     * This method initializes jScrollPane
     * 
     * @return javax.swing.JScrollPane
     */
    private JScrollPane getJScrollPane() {

        if (jScrollPane == null) {
            jScrollPane = new JScrollPane();            
            jScrollPane.setViewportView(getJTable());
        }
        return jScrollPane;
    }

    /**
     * Displays the devices descriptor information.
     * 
     * @param device
     *            the device.
     * @throws FTD2xxException
     *             if the devices descriptor can not be read.
     */
    public void update(Device device) throws FTD2xxException {

        ((DeviceDescriptorTableModel) jTable.getModel()).update(device
                .getDeviceDescriptor());

    }

    /**
     * Clears the tables model.
     */
    public void clear() {

        ((DeviceDescriptorTableModel) jTable.getModel()).clear();
    }
} // @jve:decl-index=0:visual-constraint="10,10"
