package com.ftdichip.ftd2xx.ui.deviceTree;

import java.awt.Component;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;

/**
 * Renderer to render device contents.
 * 
 * @author Mike Werner
 */
public class DeviceRenderer extends DefaultTreeCellRenderer {

    private final static Logger logger = Logger.getLogger(DeviceRenderer.class
            .getName());
    
    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    /**
     * {@inheritDoc}
     */
    @Override
    public Component getTreeCellRendererComponent(JTree tree, Object value,
            boolean sel, boolean expanded, boolean leaf, int row, boolean focus) {

        return super.getTreeCellRendererComponent(tree, getLabel(value), sel,
                expanded, leaf, row, focus);
    }

    private Object getLabel(Object value) {

        Object result = value;
        Object userObject = ((DefaultMutableTreeNode) value).getUserObject();

        if (userObject instanceof Device) {
            Device device = ((Device) userObject);
            
            try {
                result = device.getDeviceDescriptor().getProductDescription();
            } catch (FTD2xxException e) {
                logger.log(Level.SEVERE, "Failed to read product description.", e);
                
                String type = device.getType().toString();
                result = type.substring("FT_DEVICE_".length());
            }
        }

        return result;
    }
}
