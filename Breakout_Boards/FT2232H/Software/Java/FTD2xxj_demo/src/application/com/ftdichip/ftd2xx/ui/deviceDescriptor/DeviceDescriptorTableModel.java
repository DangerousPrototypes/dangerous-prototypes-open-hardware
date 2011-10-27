package com.ftdichip.ftd2xx.ui.deviceDescriptor;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Comparator;
import java.util.Map;
import java.util.TreeMap;
import java.util.Map.Entry;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.table.AbstractTableModel;

import com.ftdichip.ftd2xx.DeviceDescriptor;

/**
 * Table model for an device descriptor.
 * 
 * @author Mike Werner
 */
class DeviceDescriptorTableModel extends AbstractTableModel {

    /**
     * The <code>serialVersionUID</code>.
     */
    private static final long serialVersionUID = 1L;

    private final static Logger logger = Logger
            .getLogger(DeviceDescriptorTableModel.class.getName());

    private final static int PROPERTY_COLUMN = 0;

    private final static int VALUE_COLUMN = 1;

    private final static String columns[] = { "Property", "Value" };

    private Map<Method, Object> map = new TreeMap<Method, Object>(
            new PropertyMethodComparator());

    @SuppressWarnings("unchecked")
    private Entry<Method, Object>[] entries = new Entry[0];

    /**
     * {@inheritDoc}
     */
    public int getColumnCount() {

        return columns.length;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String getColumnName(int column) {

        return columns[column];
    }

    /**
     * {@inheritDoc}
     */
    public int getRowCount() {

        int result = 0;

        if (map != null)
            result = map.size();

        return result;
    }

    /**
     * {@inheritDoc}
     */
    public Object getValueAt(int row, int column) {

        Entry<Method, Object> entry = entries[row];
        Object result = null;

        if (column == PROPERTY_COLUMN)
            result = getPropertyMethodName(entry.getKey());

        if (column == VALUE_COLUMN)
            result = entry.getValue();

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
     * @param desc
     *            the device descriptor.
     */
    public void update(DeviceDescriptor desc) {

        map.clear();
        initMap(desc);

        fireTableDataChanged();
    }

    private void initMap(DeviceDescriptor desc) {

        for (Method method : desc.getClass().getMethods()) {// getMethods(desc.getClass().getMethods()))
                                                            // {

            try {
                if (isPropertyMethod(method))
                    map.put(method, getValue(desc, method));

            } catch (Exception e) {
                logger.log(Level.SEVERE,
                        "Failed to retrieve value from method "
                                + method.getName(), e);
            }
        }

        entries = map.entrySet().toArray(entries);
    }

    /**
     * Retrieves the name of a property out of it's getter method.
     * 
     * @param method the getter method.
     * @return the methods name except the starting "get" or "is" prefix.
     */
    String getPropertyMethodName(Method method) {

        String name = method.getName();

        String result = null;

        if (name.startsWith("get"))
            result = name.substring("get".length());
        else
            result = name.substring("is".length());

        return result;
    }

    private boolean isPropertyMethod(Method method) {

        String name = method.getName();

        return (name.startsWith("is") || (name.startsWith("get")
                && !name.equals("getClass") && method.getParameterTypes().length == 0));
    }

    private Object getValue(DeviceDescriptor desc, Method method)
            throws IllegalArgumentException, IllegalAccessException,
            InvocationTargetException {

        return method.invoke(desc, new Object[0]);
    }

    /**
     * Removes all rows from this model.
     */
    public void clear() {

        map.clear();
        fireTableDataChanged();
    }

    private class PropertyMethodComparator implements Comparator<Method> {

        /**
         * Compares two property method names.
         * 
         * @param m1
         *            the first name.
         * @param m2
         *            the second name.
         * @return the result form
         *         {@link String#compareTo(java.lang.String) m1Name.compoareTo(m2name)}
         */
        public int compare(Method m1, Method m2) {

            String m1Name = getPropertyMethodName(m1);
            String m2Name = getPropertyMethodName(m2);

            return m1Name.compareTo(m2Name);
        }
    }
}
