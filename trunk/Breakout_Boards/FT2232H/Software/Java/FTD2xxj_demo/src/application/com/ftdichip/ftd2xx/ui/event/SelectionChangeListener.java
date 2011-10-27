package com.ftdichip.ftd2xx.ui.event;


/**
 * Listener for selection changes.
 * 
 * @author Mike Werner
 */
public interface SelectionChangeListener {
    
    /**
     * Signals the selection has changed.
     * 
     * @param event the selection change event.
     */
    public void selectionChanged(SelectionChangedEvent event);
}
