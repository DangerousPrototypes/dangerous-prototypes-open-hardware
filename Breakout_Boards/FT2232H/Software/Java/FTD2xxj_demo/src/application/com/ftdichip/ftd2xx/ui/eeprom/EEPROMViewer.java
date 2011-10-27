package com.ftdichip.ftd2xx.ui.eeprom;

import java.awt.BorderLayout;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.TableColumn;

import com.ftdichip.ftd2xx.Device;
import com.ftdichip.ftd2xx.FTD2xxException;
import com.ftdichip.ftd2xx.ui.DeviceInformationViewer;

/**
 * @author Mike Werner
 */
public class EEPROMViewer extends JPanel implements DeviceInformationViewer {

    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    private JScrollPane jScrollPane = null;

    private JTable dataTable = null;

    private EEPROMTableModel dataTableModel = new EEPROMTableModel();

    /**
     * Creates a new <code>EEPROMViewer</code>.
     */
    public EEPROMViewer() {

        initialize();
    }

    /**
     * This method initializes this
     */
    private void initialize() {

        this.setLayout(new BorderLayout());
        this.add(getJScrollPane(), java.awt.BorderLayout.CENTER);
    }

    /**
     * Updates the data table model with the EEPROM data from a particular
     * device.
     * 
     * @param device
     *            the device.
     * @throws FTD2xxException
     *             if the data can no be read from the device.
     */
    public void update(Device device) throws FTD2xxException {

        dataTableModel.update(device.getEEPROM());
    }

    /**
     * Clears the data table.
     */
    public void clear() {

        dataTableModel.clear();
    }

    /**
     * This method initializes jScrollPane
     * 
     * @return javax.swing.JScrollPane
     */
    private JScrollPane getJScrollPane() {

        if (jScrollPane == null) {
            jScrollPane = new JScrollPane();
            jScrollPane.setViewportView(getDataTable());
        }
        return jScrollPane;
    }

    /**
     * Retrieves the table component showing the EEPROM data. If the table does
     * not exist it will be created first.
     * 
     * @return javax.swing.JTable
     */
    JTable getDataTable() {

        if (dataTable == null) {
            dataTable = new JTable();
            dataTable
                    .setAutoResizeMode(javax.swing.JTable.AUTO_RESIZE_LAST_COLUMN);

            dataTable.setRowHeight(20);
            dataTable.setRowSelectionAllowed(true);
            dataTable.setCellSelectionEnabled(true);
            dataTable
                    .setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);

            dataTable.setModel(dataTableModel);

            dataTable.setDefaultRenderer(Long.class,
                    new EEPROMTableCellRenderer());

            dataTable.getTableHeader().setReorderingAllowed(false);

            // update the ASCII columns minimum width to be the preferred one
            dataTableModel.addTableModelListener(new TableModelListener() {

                public void tableChanged(TableModelEvent e) {

                    if (e.getType() == TableModelEvent.UPDATE) {
                        TableColumn column = getDataTable().getColumnModel()
                                .getColumn(EEPROMTableModel.ASCII_COLUMN_INDEX);

                        column.setMinWidth(column.getPreferredWidth());
                    }
                }
            });
        }
        return dataTable;
    }

} // @jve:decl-index=0:visual-constraint="10,10"
