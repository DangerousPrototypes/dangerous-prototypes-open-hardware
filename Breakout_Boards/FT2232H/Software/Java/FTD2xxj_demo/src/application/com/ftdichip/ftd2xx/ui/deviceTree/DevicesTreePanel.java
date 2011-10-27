package com.ftdichip.ftd2xx.ui.deviceTree;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JToolBar;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;
import javax.util.Localizer;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;
import com.ftdichip.ftd2xx.ui.event.SelectionChangeListener;
import com.ftdichip.ftd2xx.ui.event.SelectionChangeSupport;
import com.ftdichip.ftd2xx.ui.event.SelectionChangedEvent;

/**
 * Tree viewer to list {@link com.ftdichip.ftd2xx.Device}s.
 * 
 * @author Mike Werner
 */
public class DevicesTreePanel extends JPanel implements TreeSelectionListener,
		SelectionChangeSupport {

	private final static Logger logger = Logger
			.getLogger(DevicesTreePanel.class.getName());

	private List<SelectionChangeListener> listeners = new ArrayList<SelectionChangeListener>();

	/**
	 * The <code>serialVersionUID</code>.
	 */
	private static final long serialVersionUID = 1L;

	private JScrollPane jScrollPane = null;

	private JTree jTree = null;

	private JButton refreshButton = null;

	private JToolBar jToolBar = null;

	/**
	 * This is the default constructor
	 */
	public DevicesTreePanel() {

		super();
		initialize();
		refreshLater();
	}

	/**
	 * This method initializes this.
	 */
	private void initialize() {

		this.setLayout(new BorderLayout());
		this.setSize(300, 347);
		this.add(getJScrollPane(), java.awt.BorderLayout.CENTER);
		this.add(getJToolBar(), java.awt.BorderLayout.NORTH);
	}

	/**
	 * Calls {@link #refresh()} within a separate thread.
	 */
	void refreshLater() {

		new Timer(getClass().getSimpleName() + " - refreshLater Timer")
				.schedule(new TimerTask() {

					@Override
					public void run() {

						try {
							logger.fine("Refresh device list.");

							refresh();

							logger.fine("Finished refreshing device list.");
						} catch (Throwable t) {
							logger.log(Level.SEVERE,
									"Failed to refresh device list.", t);

							getRefreshButton().setEnabled(false);

							String title = Localizer.getLocalizedMessage(
									DevicesTreePanel.class,
									"internal.error.title");

							String message = Localizer.getLocalizedMessage(
									DevicesTreePanel.class,
									"internal.error.message");

							showError(title, message, t);
						}
					}
				}, 100);
	}

	/**
	 * Clears the selection, refreshes the tree model and sets the selection to
	 * the first row.
	 */
	void refresh() {

		try {
			jTree.clearSelection();

			((DevicesTreeModel) jTree.getModel()).refresh();

			jTree.setSelectionRow(0);
		} catch (FTD2xxException e) {
			String message = "Failed to refresh device tree.";
			logger.log(Level.SEVERE, message, e);
			showError("FTStatus", message, e);
		}
	}

	private void showError(String title, String message, Throwable t) {

		Throwable cause = t;
		if (t != null) {
			while (cause.getCause() != null) {
				cause = cause.getCause();
			}
		}

		String text = null;
		if (cause != null) {
			text = Localizer.getLocalizedMessage(DevicesTreePanel.class,
					"showError.textWithCause", message, //$NON-NLS-1$
					cause.getMessage());
		} else {
			text = Localizer.getLocalizedMessage(DevicesTreePanel.class,
					"showError.textWithoutCause", message); //$NON-NLS-1$
		}

		JOptionPane.showMessageDialog(this, text, title,
				JOptionPane.ERROR_MESSAGE);
	}

	/**
	 * This method initializes jScrollPane
	 * 
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getJScrollPane() {

		if (jScrollPane == null) {
			jScrollPane = new JScrollPane();
			jScrollPane.setViewportView(getJTree());
		}
		return jScrollPane;
	}

	/**
	 * This method initializes jTree
	 * 
	 * @return javax.swing.JTree
	 */
	private JTree getJTree() {

		if (jTree == null) {
			jTree = new JTree();

			jTree.setModel(new DevicesTreeModel());
			jTree.setCellRenderer(new DeviceRenderer());
			jTree.setRootVisible(false);
			jTree.addTreeSelectionListener(this);
			jTree.getSelectionModel().setSelectionMode(
					TreeSelectionModel.SINGLE_TREE_SELECTION);
		}
		return jTree;
	}

	/**
	 * Notifies all registered {@link SelectionChangeListener}s about selection
	 * change.
	 * 
	 * @param e
	 *            the {@link TreeSelectionEvent}.
	 */
	public void valueChanged(TreeSelectionEvent e) {

		fireSelectionChanged(e.getSource());
	}

	/**
	 * {@inheritDoc}
	 */
	public void addSelectionChangeListener(SelectionChangeListener listener) {

		if (listeners.contains(listener))
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					DevicesTreePanel.class, "error.listenerExists"));

		listeners.add(listener);
	}

	/**
	 * {@inheritDoc}
	 */
	public void removeSelectionChangeListener(SelectionChangeListener listener) {

		if (!listeners.contains(listener))
			throw new IllegalArgumentException(Localizer.getLocalizedMessage(
					DevicesTreePanel.class, "error.listenerNotExists"));

		listeners.remove(listener);
	}

	private void fireSelectionChanged(Object source) {

		for (SelectionChangeListener l : listeners)
			l.selectionChanged(new SelectionChangedEvent(source,
					getSelectedDevice()));
	}

	private Device getSelectedDevice() {

		TreePath path = jTree.getSelectionPath();
		Device device = null;

		if (path != null && path.getPath().length > 0) {
			device = (Device) ((DefaultMutableTreeNode) path.getPath()[1])
					.getUserObject();
		}

		return device;
	}

	/**
	 * This method initializes jButton
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getRefreshButton() {

		if (refreshButton == null) {
			refreshButton = new JButton();
			refreshButton.setFocusPainted(false);
			refreshButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
			refreshButton.setToolTipText("Refreshes the devices tree.");
			refreshButton.setIcon(new ImageIcon(getClass().getResource(
					"/refresh.gif")));

			refreshButton.addActionListener(new ActionListener() {

				/**
				 * Refreshes the device tree.
				 * 
				 * @param e
				 *            the action event.
				 */
				@SuppressWarnings("unused")
				public void actionPerformed(ActionEvent e) {

					refreshLater();
				}
			});
		}
		return refreshButton;
	}

	/**
	 * This method initializes jToolBar
	 * 
	 * @return javax.swing.JToolBar
	 */
	private JToolBar getJToolBar() {

		if (jToolBar == null) {
			jToolBar = new JToolBar();
			jToolBar.setFloatable(false);
			jToolBar
					.setComponentOrientation(java.awt.ComponentOrientation.RIGHT_TO_LEFT);
			jToolBar.setBorderPainted(false);
			jToolBar.setMargin(new java.awt.Insets(4, 0, 0, 0));
			jToolBar.setPreferredSize(new java.awt.Dimension(20, 30));
			jToolBar.add(getRefreshButton());
		}
		return jToolBar;
	}
} // @jve:decl-index=0:visual-constraint="10,10"
