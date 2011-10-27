package com.ftdichip.ftd2xx.ui;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.GraphicsEnvironment;
import java.awt.Rectangle;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JFrame;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;
import com.ftdichip.ftd2xx.ui.deviceDescriptor.DeviceDescriptorViewer;
import com.ftdichip.ftd2xx.ui.deviceTree.DevicesTreePanel;
import com.ftdichip.ftd2xx.ui.eeprom.EEPROMViewer;
import com.ftdichip.ftd2xx.ui.event.SelectionChangeListener;
import com.ftdichip.ftd2xx.ui.event.SelectionChangedEvent;
import com.ftdichip.ftd2xx.ui.terminal.TerminalPanel;

/**
 * Main UI class to show connected devices and related information.
 * 
 * @author Mike Werner
 */
public class Main extends JFrame implements SelectionChangeListener {

	private final static Logger logger = Logger.getLogger(Main.class.getName());

	/**
	 * The <code>serialVersionUID</code>.
	 */
	private static final long serialVersionUID = 1L;

	private javax.swing.JPanel jContentPane = null;

	private JSplitPane jSplitPane = null;

	private JTabbedPane jTabbedPane = null;

	private DeviceDescriptorViewer deviceDescriptorViewer;

	private EEPROMViewer eepromViewer;

	private TerminalPanel terminalPanel;

	/**
	 * This method initializes jSplitPane
	 * 
	 * @return javax.swing.JSplitPane
	 */
	private JSplitPane getJSplitPane() {

		if (jSplitPane == null) {
			jSplitPane = new JSplitPane();

			DevicesTreePanel p = new DevicesTreePanel();
			p.addSelectionChangeListener(this);
			jSplitPane.setLeftComponent(p);
			jSplitPane.setRightComponent(getJTabbedPane());

			jSplitPane.setDividerSize(5);
			jSplitPane.setDividerLocation(200);
		}
		return jSplitPane;
	}

	/**
	 * This method initializes jTabbedPane
	 * 
	 * @return javax.swing.JTabbedPane
	 */
	private JTabbedPane getJTabbedPane() {

		if (jTabbedPane == null) {
			jTabbedPane = new JTabbedPane();
			jTabbedPane.setTabPlacement(SwingConstants.BOTTOM);

			jTabbedPane.addTab("Descriptor", null, getDeviceDescriptorViewer(),
					"Device descriptor information");
			jTabbedPane.addTab("EEPROM", null, getEEPROMViewer(),
					"EEPROM User Area contents");
			jTabbedPane.addTab("Terminal", null, getTerminalPanel(),
					"Simple terminal application");

		}
		return jTabbedPane;
	}

	private DeviceDescriptorViewer getDeviceDescriptorViewer() {

		if (deviceDescriptorViewer == null)
			deviceDescriptorViewer = new DeviceDescriptorViewer();

		return deviceDescriptorViewer;
	}

	private EEPROMViewer getEEPROMViewer() {

		if (eepromViewer == null)
			eepromViewer = new EEPROMViewer();

		return eepromViewer;
	}

	/**
	 * Creates the application and sets it to visible.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {

		Main application = new Main();
		application.setVisible(true);
	}

	/**
	 * This is the default constructor
	 */
	public Main() {

		super();
		initialize();
		centerToScreen();
	}

	private void centerToScreen() {

		Dimension screenSize = GraphicsEnvironment
				.getLocalGraphicsEnvironment().getDefaultScreenDevice()
				.getDefaultConfiguration().getBounds().getSize();

		Rectangle bounds = getBounds();

		int screenCenterX = screenSize.width / 2;
		int screenCenterY = screenSize.height / 2;

		int centerX = bounds.width / 2;
		int centerY = bounds.height / 2;

		bounds.x = screenCenterX - centerX;
		bounds.y = screenCenterY - centerY;

		setBounds(bounds);
	}

	/**
	 * This method initializes this.
	 */
	private void initialize() {

		this.setDefaultCloseOperation(javax.swing.JFrame.EXIT_ON_CLOSE);
		this.setSize(489, 372);
		this.setContentPane(getJContentPane());
		this.setTitle("FTD2xx Device Explorer");
	}

	/**
	 * This method initializes jContentPane
	 * 
	 * @return javax.swing.JPanel
	 */
	private javax.swing.JPanel getJContentPane() {

		if (jContentPane == null) {
			jContentPane = new javax.swing.JPanel();
			jContentPane.setLayout(new java.awt.BorderLayout());
			jContentPane.add(getJSplitPane(), java.awt.BorderLayout.CENTER);
		}
		return jContentPane;
	}

	/**
	 * Getter for terminal panel.
	 * 
	 * @return terminalPanel
	 */
	private Component getTerminalPanel() {
		if (terminalPanel == null) {
			terminalPanel = new TerminalPanel();
		}
		return terminalPanel;
	}

	/**
	 * {@inheritDoc}
	 */
	public void selectionChanged(SelectionChangedEvent event) {

		updateDeviceInformationViewers(event.getAffectedDevice());
	}

	private void updateDeviceInformationViewers(Device device) {

		int componentIndex = 0;
		Component[] viewers = getJTabbedPane().getComponents();

		try {
			if (device != null) {
				device.open(); // for viewers that need an open device
			}
			for (Component c : viewers) {
				try {
					if (device != null)
						((DeviceInformationViewer) c).update(device);
					else
						((DeviceInformationViewer) c).clear();
				} catch (FTD2xxException e) {
					logger.log(Level.SEVERE, String.format(
							"Failed to update \"%s\" viewer.", getJTabbedPane()
									.getTitleAt(componentIndex)), e);

					((DeviceInformationViewer) c).clear();
				}

				componentIndex++;
			}

			if (device != null)
				device.close();
		} catch (FTD2xxException e) {
			logger.log(Level.SEVERE, "Failed to access device.", e);
		}
	}
} // @jve:decl-index=0:visual-constraint="10,10"
