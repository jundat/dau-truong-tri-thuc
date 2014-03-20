/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entities;

/**
 *
 * @author Mrkupi
 */
public class Question {
    String questionId;
    String questionContent;
    String a;
    String b;
    String c;
    String d;
    String correct;
    Subject subj;
    
    public Question() {
        
    }
    
    public String getId() {
        return questionId;
    }
    
    public void setId( String id ) {
        this.questionId =   id;
    }
    
    public String getContent() {
        return this.questionContent;
    }
    
    public void setContent( String content ) {
        this.questionContent    =   content;
    }
    
    public String getA() {
        return a;
    }
    
    public void setA( String a ) {
        this.a  =   a;
    }
    
    public String getB() {
        return b;
    }
    
    public void setB( String b ) {
        this.b  =   b;
    }
    
    public String getC() {
        return c;
    }
    
    public void setC( String c ) {
        this.c  =   c;
    }
    
    public String getD() {
        return d;
    }
    
    public void setD( String d ) {
        this.d  =   d;
    }
    
    public String getCorrect() {
        return correct;
    }
    
    public void setCorrect( String correct ) {
        this.correct  =   correct;
    }
    
    public Subject getSubject() {
        return this.subj;
    }
    
    public void setSubject( Subject subj ) {
        this.subj   =   subj;
    }
}
