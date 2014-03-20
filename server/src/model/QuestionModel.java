/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import db.MySqlConnection_Rd;
import db.MySqlConnection_W;
import db.Utils.DataRow;
import db.Utils.DataTable;
import entities.Question;
import entities.Subject;
import java.util.ArrayList;
import java.util.List;
import share.ShareConstants;

/**
 *
 * @author Mrkupi
 */
public class QuestionModel implements BaseModel{

    List<Question>  questions   =   new ArrayList<>();
    
    public QuestionModel() {
    }
    
    @Override
    public void getData() {
    }

    @Override
    public void parseData(Object data) {
    }

    @Override
    public String toData() {
        String questionStr  =   "";
        int nQuestion       =   questions.size();
        if( nQuestion > 0 )
        {
            for( int i = 0; i < nQuestion; ++i )
            {
                Question quest  =   questions.get( i ); 
                String iteratorStr  =   String.format("{ \"quest\": \"%s\", \"a\":\"%s\", \"b\":\"%s\", \"c\":\"%s\", \"d\":\"%s\", \"right\":%s}",
                        quest.getContent(),
                        quest.getA(),
                        quest.getB(),
                        quest.getC(),
                        quest.getD(),
                        quest.getCorrect());
                
                if( i < (nQuestion - 1 ))
                {
                    iteratorStr     += ", ";
                }
                
                questionStr         += iteratorStr;
            }
        }
        
        String strResult    =   String.format("\"Quest\":[ %s ]", questionStr );
        return strResult;
    }
    
    public void randomQuestionWithSubject( String subjectId ) {
        
        // Get subject info
        Subject subj    =   SubjectModel.getInstance().getSubjectInfo(subjectId);
        if( subj != null )
        {
            int nQuestion   =   Integer.parseInt(libCore.Config.getParam( "MutilConfig", "QuestionsPackage" ));
            List<String> randomQuestIds     =   new ArrayList<>();
            int numberQuestionInSubj        =   subj.getNumberSentence();
            String commandWhere =   "";
            for( int i = 0; i < nQuestion; ++i ) {
                int randomInt   =   (int)( Math.random() * numberQuestionInSubj );
                String rand     =   subjectId + String.valueOf( randomInt );
                randomQuestIds.add( rand );
                
                commandWhere    +=  " questionid = " + rand;
                if( i < (nQuestion - 1) )
                {
                    commandWhere    +=  " OR ";
                }
            }
            
            // Querry question
            DataTable dt    =    MySqlConnection_Rd.getInstance().selectCmdWhere( ShareConstants.TABLE_QUESTION, commandWhere, 
                                        "QuestionContent", "A", "B", "C", "D", "Correct" );
            if( dt != null && dt.size() == nQuestion )
            {
                for( int i = 0; i < nQuestion; ++i )
                {
                    DataRow dr  =   dt.get( i );
                    Question quest  =   new Question();
                    quest.setContent( dr.get( "QuestionContent" ) );
                    quest.setA(dr.get( "A" ) );
                    quest.setB(dr.get( "B" ) );
                    quest.setC(dr.get( "C" ) );
                    quest.setD(dr.get( "D" ) );
                    quest.setCorrect( dr.get( "Correct" ) );
                    
                    this.questions.add( quest );
                }
            }
        }
    }
}
