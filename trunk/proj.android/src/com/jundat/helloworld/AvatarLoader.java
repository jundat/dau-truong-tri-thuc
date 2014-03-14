package com.jundat.helloworld;


import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;

import org.json.JSONException;
import org.json.JSONObject;

import android.os.AsyncTask;
import android.util.Log;

public class AvatarLoader extends AsyncTask<String, Void, String> {
	
	AsyncListener listener;
	String tag;
	public String graphUrl;
	public String fbId;
	int w;
	int h;
	String dirToSave;
	String fileToSave;
	
	public AvatarLoader(AsyncListener listener, String tag, String fbId, int w, int h, String dirToSave, String fileToSave) {
		this.listener = listener;
		this.tag = tag;
		this.fbId 	= fbId;
		this.w = w;
		this.h = h;
		this.dirToSave = dirToSave;
		this.fileToSave = fileToSave;
		
		graphUrl = "http://graph.facebook.com/" + fbId + "/picture?redirect=0&height=" + h + "&type=normal&width=" + w;
		Log.i("AVATAR_LOADER", "GRAPH URL: " + graphUrl);
	}

	@Override
	protected String doInBackground(String... params) {
		
		try {
			URL url = new URL(graphUrl);
			InputStream in = url.openConnection().getInputStream();
			Scanner scn = new Scanner(in);
			String response = scn.next();
			JSONObject dataObj = new JSONObject(response).getJSONObject("data");
			String avatarUrl = dataObj.getString("url");
			
			ImageDownloader imd = 
					new ImageDownloader(this.listener, this.tag, avatarUrl, this.dirToSave, this.fileToSave);
			imd.execute("");
			
			Log.i("AvatarURL: ", avatarUrl);
			
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return null;
	}
}
