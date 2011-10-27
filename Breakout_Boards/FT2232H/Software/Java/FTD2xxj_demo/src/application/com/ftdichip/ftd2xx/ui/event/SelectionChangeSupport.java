package com.ftdichip.ftd2xx.ui.event;


/**
 * Interface to register/de-regiser selection change listener.
 * 
 * @author Mike Werner
 */
public interface SelectionChangeSupport {
    
    /**
     * Adds a SelectionChangeListener.
     * 
     * @param listener the listener to be added.
     */
    public void addSelectionChangeListener(SelectionChangeListener listener);
    
    /**
     * Removes a SelectionChangeListener.
     * 
     * @param listener the listener to be removed.
     */
    public void removeSelectionChangeListener(SelectionChangeListener listener);
}
