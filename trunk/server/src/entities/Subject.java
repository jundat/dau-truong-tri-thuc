/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entities;

/**
 *
 * @author Mrkupi
 */
public class Subject {
    
    private String subjectId;
    private String name;
    private Boolean active;
    private int numberSentence;
    private String prefix;
    
    public Subject() {
        
    }
    
    public String getId() {
        return subjectId;
    }
    
    public void setId( String id ) {
        this.subjectId  =   id;
    }
    
    public String getName(){
        return name;
    }
    
    public void setName( String name ) {
        this.name   =   name;
    }
    
    public Boolean isActive() {
        return this.active;
    }
    
    public void setActive( boolean isActive ) {
        this.active =   isActive;
    }
    
    public int getNumberSentence() {
        return this.numberSentence;
    }
    
    public void setNumberSentence( int number ) {
        this.numberSentence =   number;
    }
    
    public String getPrefix() {
        return this.prefix;
    }
    
    public void setPrefix( String prefix ){
        this.prefix     =   prefix;
    }
}
