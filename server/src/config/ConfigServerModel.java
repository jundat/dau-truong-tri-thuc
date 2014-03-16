/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package config;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import libCore.Config;

/**
 *
 * @author Mrkupi
 */
public class ConfigServerModel implements BaseResObj{

    private static ConfigServerModel inst   =   new ConfigServerModel();
    static 
    {
        inst.winScore   =   Integer.parseInt( Config.getParam( "MutilConfig", "WinScore" ) );
        inst.loseScore  =   Integer.parseInt( Config.getParam( "MutilConfig", "LoseScore" ) );
        inst.questionsPackage   =   Integer.parseInt( Config.getParam( "MutilConfig", "QuestionsPackage" ) );
        inst.timePackage=   Integer.parseInt( Config.getParam( "MutilConfig", "TimePackage" ) );
        
        inst.helpSkip   =   Integer.parseInt( Config.getParam( "MutilConfig", "HelpSkip" ) );
        inst.helpExclusive  =   Integer.parseInt( Config.getParam( "MutilConfig", "HelpExclusive" ) );
        inst.helpInfinite   =   Integer.parseInt( Config.getParam( "MutilConfig", "HelpInfinite" ) );
        
        inst.jewelry10k =   Integer.parseInt( Config.getParam( "MutilConfig", "Jewelry10k" ) );
        inst.jewelry20k =   Integer.parseInt( Config.getParam( "MutilConfig", "Jewelry20k" ) );
        inst.jewelry50k =   Integer.parseInt( Config.getParam( "MutilConfig", "Jewelry50k" ) );
        inst.jewelry100k =   Integer.parseInt( Config.getParam( "MutilConfig", "Jewelry100k" ) );
        
        inst.jewelryWin =   Integer.parseInt( Config.getParam( "MutilConfig", "JewelryWin" ) );
        inst.jewelryLose=   Integer.parseInt( Config.getParam( "MutilConfig", "JewelryLose" ) );
        inst.jewelryDraw=   Integer.parseInt( Config.getParam( "MutilConfig", "JewelryDraw" ) );
        
        inst.pairTimeOut=   Integer.parseInt( Config.getParam( "MutilConfig", "PairTimeOut" ) );
    }
    
    private int winScore;
    private int loseScore;
    private int questionsPackage;
    private int timePackage;
    private int helpSkip;
    private int helpExclusive;
    private int helpInfinite;
    private int jewelry10k;
    private int jewelry20k;
    private int jewelry50k;
    private int jewelry100k;
    private int jewelryWin;
    private int jewelryLose;
    private int jewelryDraw;
    private int pairTimeOut;
    
    
    public static ConfigServerModel getInst(){
        return inst;
    }
    
    
    public void getConfig( HttpServletRequest req, HttpServletResponse resp ) throws IOException
    {
        Map<String, Object> data    =   toData();
        String content  =   libCore.Util.obj2String( data );
        try (PrintWriter pw = resp.getWriter()) 
        {
            pw.println( content );
            pw.flush();
            pw.close();
        }
    }
    
    @Override
    public Map<String, Object> toData() {
        Map<String, Object> data    =   new HashMap<String, Object>();
        
        data.put( share.ShareConstants.WIN_SCORE, winScore );
        data.put( share.ShareConstants.LOSE_SCORE, loseScore );
        data.put( share.ShareConstants.QUESTION_PACK, questionsPackage );
        data.put( share.ShareConstants.TIME_PACK, timePackage );
        
        data.put( share.ShareConstants.HELP_SKIP, helpSkip );
        data.put( share.ShareConstants.HELP_EXCLUSIVE, helpExclusive );
        data.put( share.ShareConstants.HELP_INFINITE, helpInfinite );
        
        data.put( share.ShareConstants.JEWELRY_10k, jewelry10k );
        data.put( share.ShareConstants.JEWELRY_20k, jewelry20k );
        data.put( share.ShareConstants.JEWELRY_50k, jewelry50k );
        data.put( share.ShareConstants.JEWELRY_100k, jewelry100k );
        
        data.put( share.ShareConstants.JEWELRY_WIN, jewelryWin );
        data.put( share.ShareConstants.JEWELRY_LOSE, jewelryLose );
        data.put( share.ShareConstants.JEWELRY_DRAW, jewelryDraw );
        
        data.put( share.ShareConstants.PAIR_TIME_OUT, pairTimeOut );
        
        return data;
    }
}
