package com.ftdichip.ftd2xx.ui.eeprom;

import javax.swing.table.AbstractTableModel;

import com.ftdichip.ftd2xx.EEPROM;
import com.ftdichip.ftd2xx.FTD2xxException;

/**
 * Table model for an device descriptor.
 * 
 * @author Mike Werner
 */
class EEPROMTableModel extends AbstractTableModel {

    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    private final static int NUM_DATA_COLUMNS = 8;

    private final static int NUM_COLUMNS = NUM_DATA_COLUMNS + 1;

    private final static int NUM_BYTES_PER_COLUMN = 2;

    /**
     * The index of the column shown the ASCII representation.
     */
    final static int ASCII_COLUMN_INDEX = NUM_DATA_COLUMNS;

    private final static String ASCII_COLUMN_TEXT = "ASCII";

    private byte data[] = new byte[0];

    private int userAreaSize;

    /**
     * {@inheritDoc}
     */
    public int getColumnCount() {

        return NUM_COLUMNS;
    }
    
    
    /**
     * Retrieves the class of a particular column's data.
     * 
     * @param columnIndex the column index.
     * @return the class of the column's data.
     */
    @Override
    public Class< ? > getColumnClass(int columnIndex) {

        Class<?> result = Long.class;
        
        if(columnIndex == ASCII_COLUMN_INDEX)
            result = String.class;
        
        return result;
    }



    /**
     * {@inheritDoc}
     */
    @Override
    public String getColumnName(int column) {

        String result = ASCII_COLUMN_TEXT;

        if (column != ASCII_COLUMN_INDEX)
            result = Integer.toHexString(column * NUM_BYTES_PER_COLUMN)
                    .toUpperCase();

        return result;
    }

    /**
     * {@inheritDoc}
     */
    public int getRowCount() {

        return data.length / (NUM_COLUMNS * NUM_BYTES_PER_COLUMN) + 1;
    }

    /**
     * {@inheritDoc}
     */
    public Object getValueAt(int row, int column) {

        Object result = null;

        int offset = calculateDataOffset(row, column);

        if (offset + NUM_BYTES_PER_COLUMN < data.length)
            result = getValue(data, offset, NUM_BYTES_PER_COLUMN);

        if (column == ASCII_COLUMN_INDEX)
            result = getASCII(row);

        return result;
    }

    private int calculateDataOffset(int row, int column) {

        return row * NUM_DATA_COLUMNS * NUM_BYTES_PER_COLUMN + column;
    }

    private String getASCII(int row) {

        StringBuilder builder = new StringBuilder();

        int offset = calculateDataOffset(row, 0);
        for (int i = offset; (i - offset < (NUM_DATA_COLUMNS * NUM_BYTES_PER_COLUMN - 1)) && i < data.length; i++) {
            if (Character.isLetterOrDigit((char) data[i]))
                builder.append(data[i]);
            else
                builder.append('.');
        }

        return builder.toString();
    }

    private static long getValue(byte[] buffer, int offset, int numBytes) {

        long result = 0;

        for (int i = 0; i < numBytes; i++) {
            result |= (buffer[offset] & 0xFF) << i;
        }

        return result;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    @SuppressWarnings("unused")
    public boolean isCellEditable(int row, int column) {

        return false;
    }

    /**
     * Initializes this model with the values of a device descriptor.
     * 
     * @param eeprom
     *            the EEPROM to read from.
     * @throws FTD2xxException
     */
    public void update(EEPROM eeprom) throws FTD2xxException {

        userAreaSize = eeprom.getUserAreaSize();
        data = new byte[userAreaSize];

        eeprom.readUserArea(data);

        fireTableDataChanged();
    }

    /**
     * Removes all rows from this model.
     */
    public void clear() {

        data = new byte[0];
        fireTableDataChanged();
    }
}
