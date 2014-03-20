/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package httpservice;

import libCore.Config;
import org.apache.log4j.Logger;
import org.eclipse.jetty.jmx.MBeanContainer;
import org.eclipse.jetty.server.Connector;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.nio.SelectChannelConnector;
import org.eclipse.jetty.servlet.ServletHandler;
import org.eclipse.jetty.util.log.Log;
import org.eclipse.jetty.util.thread.QueuedThreadPool;

/**
 *
 * @author ngaht
 */
public class WebServer {

    private static Logger logger_ = Logger.getLogger(WebServer.class);

    public void start() throws Exception {
        Server server = new Server();

        //setup JMX
        MBeanContainer mbContainer = new MBeanContainer(java.lang.management.ManagementFactory.getPlatformMBeanServer());
        server.getContainer().addEventListener(mbContainer);
        server.addBean(mbContainer);
        mbContainer.addBean(Log.getLog());

        QueuedThreadPool threadPool = new QueuedThreadPool();
        threadPool.setMinThreads(100);
        threadPool.setMaxThreads(2000);
        server.setThreadPool(threadPool);
        System.out.println(Config.getHomePath());
        String port = Config.getParam("rest", "port_listen");
        int port_listen = Integer.parseInt(port);

        SelectChannelConnector connector = new SelectChannelConnector();
        connector.setPort(port_listen);
        connector.setMaxIdleTime(30000);
        connector.setConfidentialPort(8443);
        connector.setStatsOn(false);
        connector.setLowResourcesConnections(20000);
        connector.setLowResourcesMaxIdleTime(5000);

        server.setConnectors(new Connector[]{connector});


        ServletHandler handler = new ServletHandler();
        server.setHandler(handler);
        logger_.info(" ************************** ");

        // Handler config
        handler.addServletWithMapping("webservlet.ConfigController", "/config");
        
//        // Handler profile
        handler.addServletWithMapping("webservlet.ProfileController", "/profile");
        
        // Handler user score
        handler.addServletWithMapping("webservlet.SingleScoreController", "/score/single");
        handler.addServletWithMapping("webservlet.MultiScoreController", "/score/multi");
        
        // Handler question response
        handler.addServletWithMapping("webservlet.SubjectController", "/subject");
        
        // Handler user game multi
        handler.addServletWithMapping("webservlet.GamePairerController", "/join");

//        // Handler leaderboard
        handler.addServletWithMapping("webservlet.SingleReportController", "/report/single");
//        handler.addServletWithMapping("webservlet.ReportMulti", "/report/multi");
        
        server.setStopAtShutdown(true);
        server.setSendServerVersion(true);

//        String zk_hosts = Config.getParam("servicemap", "zk_hosts");
//        String servicename = Config.getParam("servicemap", "services");
//        ConfigServiceMap servicemap = ConfigServiceMap.getInstance();
//        servicemap.init(zk_hosts, servicename);

        logger_.info("==============================");
	logger_.info("Webserver is starting to listen");
        
        server.start();
        server.join();
    }
}
