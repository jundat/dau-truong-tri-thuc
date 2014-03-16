/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entities;

/**
 *
 * @author Mrkupi
 */
public class User {
    
    private String uid;
    private String name;
    private String avatar;
    private String singleId;
    private String multiId;
    private int jewelry;
    
    public User() {
        
    }
    
    public String getId() {
        return uid;
    }
    
    public void setId( String id ) {
        this.uid     =   id;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName( String name ) {
        this.name  =   name;
    }
    
    public String getAvatar() {
        return avatar;
    }
    
    public void setAvatar( String avatar ) {
        this.avatar  =   avatar;
    }
    
    public String getSingleId() {
        return singleId;
    }
    
    public void setSingleId( String singleId ) {
        this.singleId  =   singleId;
    }
    
    public String getMultiId() {
        return multiId;
    }
    
    public void setMultiId( String multiId ) {
        this.multiId  =   multiId;
    }
    
    public int getJewelry() {
        return jewelry;
    }
    
    public void setJewelry( int jewelry ) {
        this.jewelry  =   jewelry;
    }
}
