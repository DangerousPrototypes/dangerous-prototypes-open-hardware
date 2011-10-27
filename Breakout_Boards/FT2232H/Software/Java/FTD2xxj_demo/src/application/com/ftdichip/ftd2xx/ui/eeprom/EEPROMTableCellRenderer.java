package com.ftdichip.ftd2xx.ui.eeprom;

import java.awt.Component;

import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.table.DefaultTableCellRenderer;

/**
 * @author we65921
 */
public class EEPROMTableCellRenderer extends DefaultTableCellRenderer {

    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;
    

    /**
     * Sets the horizontal alignment for the component returned by the super
     * class.
     * 
     * @param table
     *            the table this renderer operates on.
     * @param value
     *            the value to render.
     * @param isSelected
     *            determines whether the cell is selected or not.
     * @param hasFocus
     *            determines whether the cell has the focus or not.
     * @param row
     *            the row.
     * @param column
     *            the column.
     * @return the component which renders the value.
     */
    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
            boolean isSelected, boolean hasFocus, int row, int column) {

        Component c = super.getTableCellRendererComponent(table,
                getLabel(value), isSelected, hasFocus, row, column);

        if (c instanceof JLabel) {
            ((JLabel) c).setHorizontalAlignment(SwingConstants.CENTER);
            ((JLabel) c).setIconTextGap(0);
        }

        return c;
    }

    private String getLabel(Object value) {

        String result = "";

        if (value != null)
            result = String.format("%04X", value);

        return result;
    }
}
