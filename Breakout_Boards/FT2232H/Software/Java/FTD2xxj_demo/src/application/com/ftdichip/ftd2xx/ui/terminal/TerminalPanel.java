package com.ftdichip.ftd2xx.ui.terminal;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.InputStream;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;
import com.ftdichip.ftd2xx.ui.DeviceInformationViewer;

/**
 * This a simple two-panel terminal window to show how FTD2xxj could be used to
 * send and receive data.
 * 
 * The workflow is the following:<br>
 * 1. Open device with device.open();<br>
 * 2. set port parameters if required with<br> 
 * <code><b>this.device.getPort().set*</b></code><br>
 *  functions;<br>
 * 3. Start separate thread to read data from the device<br>
 * 4. Write data with device.write(...)<br>
 * 
 * @author rsh
 * 
 */
public class TerminalPanel extends JPanel implements DeviceInformationViewer,
		ActionListener {

	private JTextArea taReceived;
	private JTextArea taSend;
	private JTextField tbPortSpeed;
	private Thread reader;
	private Device device;
	private MyDocumentListener changeListener;
	private JButton btStartStop;

	public TerminalPanel() {
		super();
		setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		JPanel jpPortSettings = new JPanel();
		jpPortSettings.setBorder(BorderFactory
				.createTitledBorder("Port settings"));
		jpPortSettings.setLayout(new GridLayout(0, 3));
		tbPortSpeed = new JTextField();
		tbPortSpeed.setText("9600");
		jpPortSettings.add(new JLabel("Port speed:"));
		jpPortSettings.add(tbPortSpeed);
		btStartStop = new JButton("Start");
		btStartStop.setActionCommand("start");
		btStartStop.addActionListener(this);
		jpPortSettings.add(btStartStop);
		add(jpPortSettings);

		// Receive data block
		JPanel jpReceived = new JPanel();
		jpReceived.setBorder(BorderFactory.createTitledBorder("Received data"));
		jpReceived.setLayout(new BorderLayout());
		taReceived = new JTextArea();
		taReceived.setText("");
		taReceived.setLineWrap(true);
		taReceived.setWrapStyleWord(true);
		JScrollPane scrollPane = new JScrollPane(taReceived);
		jpReceived.add(scrollPane);

		// Send data block
		JPanel jpSend = new JPanel();
		jpSend.setBorder(BorderFactory.createTitledBorder("Send data"));
		jpSend.setLayout(new BorderLayout());
		taSend = new JTextArea();
		taSend.setLineWrap(true);
		changeListener = new MyDocumentListener();
		taSend.getDocument().addDocumentListener(changeListener);
		jpSend.add(taSend);

		// Split pane
		JPanel jpDataPanel = new JPanel();
		jpDataPanel.setLayout(new BorderLayout());
		JSplitPane jSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
				jpReceived, jpSend);
		jSplitPane.setResizeWeight(0.5);
		jpDataPanel.add(jSplitPane, BorderLayout.CENTER);
		add(jpDataPanel, BorderLayout.CENTER);
	}

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	@Override
	public void update(Device device) throws FTD2xxException {
		if (null != reader) {
			reader.interrupt();
		}
		this.device = device;
		this.changeListener.setDevice(device);
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub

	}

	public void readPortData() {
		if (null != this.device) {
			byte buffer[] = new byte[1024];
			int len = 0;
			InputStream is = this.device.getInputStream();
			while (true) {
				if (Thread.interrupted())
					break;
				try {
					len = is.available();
					if (len == -1)
						break;
					if (len == 0)
						continue;
					len = is.read(buffer, 0, len);
					if (len > 0) {
						sendDataToScreen(buffer, 0, len);
						System.out.println(format(buffer, 0, len));
					}
				} catch (IOException e) {
					System.out.println("Read exception occurs: "
							+ e.getMessage());
				}
			}
		}
	}

	private String format(byte[] bytes, int offset, int numBytes) {

		StringBuilder buffer = new StringBuilder();

		for (int i = offset; i < numBytes; i++) {
			buffer.append(String.format("%02X ", bytes[i] & 0xFF)); //$NON-NLS-1$        
		}

		return buffer.toString(); //$NON-NLS-1$
	}

	private void sendDataToScreen(byte[] bytes, int offset, int numBytes) {
		String data = new String(bytes, offset, numBytes);
		taReceived.setText(taReceived.getText() + data.toString());

	}

	class MyDocumentListener implements DocumentListener {
		String newline = "\n";
		private Device device;

		public void setDevice(Device device) {
			this.device = device;
		}

		public void insertUpdate(DocumentEvent e) {
			updateLog(e, "inserted into");
		}

		public void removeUpdate(DocumentEvent e) {
			updateLog(e, "removed from");
		}

		public void changedUpdate(DocumentEvent e) {
			// Plain text components do not fire these events
		}

		public void updateLog(DocumentEvent e, String action) {
			Document doc = (Document) e.getDocument();
			int changeLength = e.getLength();
			try {
				String dataToWrite = doc.getText(
						doc.getLength() - changeLength, changeLength);
				byte data[] = dataToWrite.getBytes();
				if (this.device.isOpen()) {
					try {
						this.device.write(data, 0, data.length);
					} catch (FTD2xxException e1) {
						e1.printStackTrace();
					}
				}
			} catch (BadLocationException e1) {
				e1.printStackTrace();
			}
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if ("start".equals(e.getActionCommand())) {
			try {
				if (!this.device.isOpen()) {
					this.device.open();
				}
				this.device.getPort().setBaudRate(
						Integer.parseInt(tbPortSpeed.getText()));
				reader = new Thread() {
					public void run() {
						readPortData();
					}
				};
				reader.start();
				btStartStop.setActionCommand("stop");
				btStartStop.setText("Stop");
			} catch (FTD2xxException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}

		}
		if ("stop".equals(e.getActionCommand())) {
			try {
				reader.interrupt();
				if (this.device.isOpen()) {
					this.device.close();
				}
				btStartStop.setActionCommand("start");
				btStartStop.setText("Start");
			} catch (FTD2xxException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}

		}
	}

}
