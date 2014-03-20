/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entities;

import model.UserModel;

/**
 *
 * @author Mrkupi
 */
public class WaittingUser {
    
    private UserModel pairer;
    private UserModel me;
    private Boolean isOrdered;
    
    public WaittingUser( UserModel me )
    {
        isOrdered   =   false;
        this.me     =   me;
    }
    
    synchronized public Boolean orderMe( UserModel user )
    {
        if( isOrdered )
        {
            isOrdered   =   true;
            this.pairer =   user;
            return true;
        }
        return false;
    }
    
    public Boolean hasOrder()
    {
        return isOrdered;
    }
    
    public UserModel getMe()
    {
        return me;
    }
    
    public UserModel getPairer()
    {
        return pairer;
    }
}
