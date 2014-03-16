/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Mrkupi
 */
public interface BaseModel {
    
    void getData();
    void parseData( Object data );
    String toData();
}
