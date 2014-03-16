/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package entities;

/**
 *
 * @author Mrkupi
 */
public class SingleResult {
    
    private String id;
    private int wins;
    private int loses;
    private int score;
    
    public SingleResult() {
        
    }
    
    public String getId() {
        return id;
    }
    
    public void setId( String id ) {
        this.id     =   id;
    }
    
    public int getWins() {
        return wins;
    }
    
    public void setWins( int wins ) {
        this.wins  =   wins;
    }
    
    public int getLoses() {
        return loses;
    }
    
    public void setLoses( int loses ) {
        this.loses  =   loses;
    }
    
    public int getScore() {
        return score;
    }
    
    public void setScore( int score ) {
        this.score  =   score;
    }
}
