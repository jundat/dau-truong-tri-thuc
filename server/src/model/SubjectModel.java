/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import db.MySqlConnection_Rd;
import db.Utils.DataRow;
import db.Utils.DataTable;
import entities.Subject;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import libCore.Util;
import share.ShareConstants;

/**
 *
 * @author Mrkupi
 */
public class SubjectModel implements BaseModel{

    public List<Subject> subjects;
    // Singleton
    private static SubjectModel inst;
    static 
    {
        inst    =   new SubjectModel();
    }
    
    private SubjectModel() {
    }
    
    public static SubjectModel getInstance()
    {
        return inst;
    }
    
    @Override
    public void getData() {
        // Already load data
        if( subjects != null )
            return;
        
        subjects      =   new ArrayList<>();
        DataTable dt = MySqlConnection_Rd.getInstance().selectAll( ShareConstants.TABLE_SUBJECT, ShareConstants.SUBJECT_ID, ShareConstants.SUBJECT_NAME, 
                ShareConstants.SUBJECT_ACTIVE, ShareConstants.SUBJECT_NSENTENCE, ShareConstants.SUBJECT_PREFIX );
        
        if( dt != null && dt.size() > 0 ) {
            for( int i = 0; i < dt.size(); ++i )
            {
                DataRow dw  =   dt.get(i);
                Subject sm =   new Subject();
                sm.setId( dw.get( ShareConstants.SUBJECT_ID ) );
                sm.setName( dw.get( ShareConstants.SUBJECT_NAME ) );
                sm.setActive(Boolean.valueOf( dw.get( ShareConstants.SUBJECT_ACTIVE ) ));
                sm.setNumberSentence(Integer.parseInt(dw.get( ShareConstants.SUBJECT_NSENTENCE ) ));
                sm.setPrefix( dw.get( ShareConstants.SUBJECT_PREFIX ) );
                subjects.add( sm );
            }
        }
    }

    @Override
    public void parseData(Object data) {
    }

    @Override
    public String toData() {
        
        String dataStr  =   "{ \"list\":[";
        int nsize       =   subjects.size();
        for( int i = 0; i < nsize; ++i )
        {
            Subject subject =   subjects.get( i );
            
            Map<String, Object> data    =   new HashMap<>();
            data.put( ShareConstants.SUBJECT_ID, subject.getId() );
            data.put( ShareConstants.SUBJECT_NAME, subject.getName());
            data.put( ShareConstants.SUBJECT_ACTIVE, subject.isActive());
            data.put( ShareConstants.SUBJECT_NSENTENCE, subject.getNumberSentence());
            data.put( ShareConstants.SUBJECT_PREFIX, subject.getPrefix());
            
            dataStr     =   dataStr + Util.obj2String( data );

            if( i != ( nsize - 1 ))
            {
                dataStr =   dataStr + ",";
            }
        }
        dataStr     +=  " ]}";
        
        return dataStr;
    }
    
    public Subject getSubjectInfo( String subjectId ) {
        for( int i = 0; i < subjects.size(); ++i )
        {
            Subject subj    =   subjects.get( i );
            if( subj.getId().equals( subjectId ) )
            {
                return subj;
            }
        }
        return null;
    }
    
    public void getSubject( HttpServletRequest req, HttpServletResponse resp ) throws IOException {
        
        String dataStr  =   toData();
        
        if( subjects.size() > 0 )
        {
            try (PrintWriter pw = resp.getWriter()) 
            {
                pw.println( dataStr );
                pw.flush();
            }
        }
    }
}