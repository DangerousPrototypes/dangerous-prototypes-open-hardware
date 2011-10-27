package com.ftdichip.ftd2xx.ui.deviceTree;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeNode;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;
import com.ftdichip.ftd2xx.Service;

/**
 * The model to be used with the
 * {@link com.ftdichip.ftd2xx.ui.deviceTree.DevicesTreePanel}.
 * 
 * @author Mike Werner
 */
public class DevicesTreeModel extends DefaultTreeModel {

    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    /**
     * Creates a new <code>DevicesTreeModel</code>.
     */
    public DevicesTreeModel() {

        super(null, true);

    }

    /**
     * Refreshes this model.
     * 
     * @throws FTD2xxException
     *             if the devices can not be accessed.
     */
    public void refresh() throws FTD2xxException {

        setRoot(createTree());
        reload();
    }

    private static TreeNode createTree() throws FTD2xxException {

        DefaultMutableTreeNode root = new DefaultMutableTreeNode(
                "FTD2xx Devices");

        for (Device device : Service.listDevices()) {
            root.add(createDeviceNode(device));
        }

        return root;
    }

    private static DefaultMutableTreeNode createDeviceNode(Device device) {

        return new DefaultMutableTreeNode(device, false);
    }    
}
