/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entities;

import model.QuestionModel;
import model.UserModel;

/**
 *
 * @author Mrkupi
 */
public class WaittingUser {
    
    private WaittingUser pairer;
    private UserModel me;
    private Boolean isOrdered;
    private QuestionModel questionPackage;
    
    public WaittingUser( UserModel me )
    {
        isOrdered   =   false;
        this.me     =   me;
    }
    
    synchronized public Boolean orderMe( WaittingUser user )
    {
        if( !isOrdered )
        {
            isOrdered   =   true;
            this.pairer =   user;
            return true;
        }
        return false;
    }
    
    synchronized public void setQuestionPackage( QuestionModel questionModel ) {
        if( this.questionPackage == null )
        {
            this.questionPackage    =   questionModel;
            System.out.println( me.uid + " has binary " + this.toString() + " ----> set question package has " + this.questionPackage.questions.size() + " sentences" );
        }
    }
    
    public QuestionModel getQuestionPackage() {
        return this.questionPackage;
    }
    
    synchronized public Boolean hasQuestionPackage() {
        return ( this.questionPackage != null );
    }
    
    public Boolean hasOrder()
    {
        return isOrdered;
    }
    
    public UserModel getMe()
    {
        return me;
    }
    
    public WaittingUser getPairer()
    {
        return pairer;
    }
}
