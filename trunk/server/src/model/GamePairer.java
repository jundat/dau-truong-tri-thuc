/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

import entities.Question;
import entities.WaittingUser;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.simple.JSONValue;
import share.ShareConstants;

/**
 *
 * @author Mrkupi
 */
public class GamePairer {
    
    private int connectionTimeout;
    
    private Map<String, List<WaittingUser>> waittingUsers;
    
    private static GamePairer inst;
    static 
    {
        inst    =   new GamePairer();
        // Load list subject
        SubjectModel subjectModel   =   SubjectModel.getInstance();
        subjectModel.getData();
        for( int i = 0; i < subjectModel.subjects.size(); ++i )
        {
            String subjectKey   =   subjectModel.subjects.get(i).getId();
            List<WaittingUser> waits    =   new ArrayList<>();
            inst.waittingUsers.put( subjectKey, waits );
        }
    }
    
    private GamePairer(){
        connectionTimeout   =   Integer.parseInt(libCore.Config.getParam( "MutilConfig", "PairTimeOut" ));
        waittingUsers       =   new HashMap<>();
    }
    
    public static GamePairer getInstance() {
        return inst;
    }
    
    /*
     * return: data info of pairer
     */
    public String join( HttpServletRequest req, HttpServletResponse resp ) throws IOException {
        // Final result
        String resultStr            =   "";
        
        // Data info of pairer
        String pairerStr            =  "";
        
        String dataStr  =   req.getParameter( ShareConstants.DATA );
        Map<String, String> mData   =   (Map<String, String>) JSONValue.parse(dataStr);
        String subjectId            =   "";
        String uid                  =   "";
            
        // Random question
        QuestionModel questionModel =   new QuestionModel();
        System.out.println( "Create package with " + questionModel.questions.size() + " question");
        
        if( mData != null )
        {
            subjectId               =   mData.get( "subjectId" );
            uid                     =   mData.get( ShareConstants.FID );
            UserModel um            =   new UserModel();
            um.uid                  =   uid;
            um.getData();
            
            // Random question
            questionModel.randomQuestionWithSubject(subjectId);
            
            // Empty list for this subject
            List<WaittingUser> waits    =   waittingUsers.get( subjectId );
            final WaittingUser waitU    =   new WaittingUser( um );
            if( waits.size() > 0 ) {
                for( int i = 0; !waitU.hasOrder() && i < waits.size(); ++i ) {
                    WaittingUser pairer = waittingUsers.get( subjectId ).get(i);
                    if( !pairer.hasOrder() ) {
                        waitU.orderMe( pairer );
                        pairer.orderMe( waitU );
                        if( !waitU.hasQuestionPackage() )
                        {
                            waitU.setQuestionPackage( questionModel );
                            waitU.getPairer().setQuestionPackage( questionModel );
                        }
                    }
                }
            }
            
            // Waitting user has not found correctly pairer
            if( !waitU.hasOrder() ) {
                waits.add( waitU );
                
                // time out 100000 count in loop
                long startTime = System.currentTimeMillis();  
                long endTime = startTime + (10 * 1000);

                while(System.currentTimeMillis()<endTime){
                    // Make sure you're not pairer by the other one
                    if( waitU.hasOrder() ) {
                        // Remove you from this list
                        waittingUsers.get( subjectId ).remove( waitU );
                        break;
                    }
                    if( waittingUsers.get( subjectId ).size() > 1 ) {
                        for( int i = 0; !waitU.hasOrder() && i < waits.size(); ++i )
                        {
                            WaittingUser pairer = waittingUsers.get( subjectId ).get(i);
                            if( !pairer.hasOrder() )
                            {
                                // Book this one
                                waitU.orderMe( pairer );
                                pairer.orderMe( waitU );
                                // Set question package
                                if( !waitU.hasQuestionPackage() )
                                {
                                    waitU.setQuestionPackage(questionModel);
                                    waitU.getPairer().setQuestionPackage(questionModel);
                                }
                            }
                        }
                    }
                }
            }
            
            // Try to return pairer info
            if( waitU.hasOrder() ) 
            {
                UserModel pairerModel   =   waitU.getPairer().getMe();
                System.out.println( uid + " has binary " + waitU.toString() );
                
                List<Question> questions    =   waitU.getQuestionPackage().questions;
                String questionStr          =   "";
                // Parse string question
                for( int i = 0; i < questions.size(); ++i )
                {
                    Question quest          =   questions.get(i);
                    String questIterator    =   String.format( "{\"quest\":\"%s\", \"a\":\"%s\", \"b\":\"%s\", \"c\":\"%s\", \"d\":\"%s\", \"right\":\"%s\"}",
                                                       quest.getContent(),
                                                       quest.getA(),
                                                       quest.getB(),
                                                       quest.getC(),
                                                       quest.getD(),
                                                       quest.getCorrect());
                    if( i < (questions.size() - 1) )
                        questIterator       +=  ",";
                    
                    questionStr             +=  questIterator;
                }
                
                resultStr   =   String.format( "{ \"oppId\":\"%s\", \"oppName\":\"%s\", \"oppWin\":%s, \"oppLose\":%s, \"Quest\":[%s] }",
                                               pairerModel.uid,
                                               pairerModel.name,
                                               pairerModel.multiResult.result.getWins(),
                                               pairerModel.multiResult.result.getLoses(),
                                               questionStr );
            }
            System.out.println( uid + " ----> " + resultStr );
        }
        return resultStr;
    }
}