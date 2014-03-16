/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import entities.MultiReport;
import entities.SingleReport;
import entities.User;
import java.util.List;

/**
 *
 * @author Mrkupi
 */
public class SingleReportModel implements BaseModel{
    private List<User> users;
    
    
    public SingleReportModel() {
        
    }

    @Override
    public void getData() {
        
    }

    @Override
    public void parseData(Object data) {
        
    }

    @Override
    public String toData() {
        
        String dataStr      =   "";
        
        for( int i = 0; i < users.size(); ++i ) {
            
        }
    }
}
