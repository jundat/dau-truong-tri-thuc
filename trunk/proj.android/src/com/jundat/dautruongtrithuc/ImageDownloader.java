package com.jundat.dautruongtrithuc;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;

import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.os.Environment;
import android.util.Log;



public class ImageDownloader extends AsyncTask<String, Void, Bitmap>
{
	AsyncListener listener;
	String tag;
	String url;
	String dirToSave;
	String fileToSave;
	
	public ImageDownloader(AsyncListener listener, String tag, String url, String dirToSave, String fileToSave) {
		this.listener = listener;
		this.tag = tag;
		this.url = url;
		this.dirToSave = dirToSave;
		this.fileToSave = fileToSave;
	}
	
    @Override
    protected Bitmap doInBackground(String... arg0) 
    {
    	Log.i("DOWN_SAVE", "doInBackground");
        downloadImagesToSdCard(url, dirToSave, fileToSave);
        return null;
    }

    private void downloadImagesToSdCard(String downloadUrl, String imageDir, String imageName)
   	{
    	Log.i("DOWN_SAVE", "downloadImagesToSdCard");
		try
		{
        	URL url = new URL(downloadUrl); //img_URL
	        /* making a directory in sdcard */
	        String sdCard = Environment.getExternalStorageDirectory().toString();
	        String dname = imageDir;
	        File myDir = new File(sdCard, dname);
	
	        /*  if specified not exist create new */
	        if(!myDir.exists())
	        {
	            myDir.mkdir();
	            Log.v("CREATE_DIR", "Create dir");
	        }
	
	        /* checks the file and if it already exist delete */
	        String fname = imageName;
	        File file = new File (myDir, fname);
	        if (file.exists ()) {
	        	Log.v("CREATE_DIR", "Already have file, send back now");
	        	sendToCallback(file.getAbsolutePath());
	        	
	        	return;	        	
	        } else {
	        	Log.v("CREATE_DIR", "Create new file");
	        }
	        
	        String filePath = file.getAbsolutePath();
	        Log.i("PATH", file.getAbsolutePath());
	
        	/* Open a connection */
	        URLConnection ucon = url.openConnection();
	        InputStream inputStream = null;
	        HttpURLConnection httpConn = (HttpURLConnection)ucon;
	        httpConn.setRequestMethod("GET");
	        httpConn.connect();
	
	      	if (httpConn.getResponseCode() == HttpURLConnection.HTTP_OK) 
	      	{
	      		inputStream = httpConn.getInputStream();
	      	}
	
	        FileOutputStream fos = new FileOutputStream(file);  
	        int totalSize = httpConn.getContentLength();
	        int downloadedSize = 0;   
	        byte[] buffer = new byte[1024];
	        int bufferLength = 0;
	        while ((bufferLength = inputStream.read(buffer)) > 0) 
	        {                 
	        	fos.write(buffer, 0, bufferLength);                  
	        	downloadedSize += bufferLength;                 
	        	Log.i("DownloadProgress: ", "downloadedSize: " + downloadedSize + "totalSize: " + totalSize);
	        }
	
	        fos.close();
	        Log.d("SAVE", "Image Saved in sdcard..");
	        
	        /////////////////////////////////////////////////
	        
	        sendToCallback(filePath);
	        
        	/////////////////////////////////////////////////
	    }
	    catch(IOException io)
	    {                  
	         io.printStackTrace();
	         sendToCallback("");
	    }
	    catch(Exception e)
	    {                     
	        e.printStackTrace();
	        sendToCallback("");
	    }
	}
    
    private void sendToCallback(String filePath) {
    	 this.listener.onAsyncComplete(this.tag, filePath);
    }
}