/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.jundat.helloworld;

import java.io.File;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.os.Bundle;
import android.os.Environment;
import android.util.Base64;
import android.util.Log;

import com.jundat.helloworld.classes.AndroidNDKHelper;
import com.sromku.simple.fb.Permissions;
import com.sromku.simple.fb.Properties;
import com.sromku.simple.fb.SimpleFacebook;
import com.sromku.simple.fb.SimpleFacebook.OnInviteListener;
import com.sromku.simple.fb.SimpleFacebook.OnLoginListener;
import com.sromku.simple.fb.SimpleFacebook.OnLogoutListener;
import com.sromku.simple.fb.SimpleFacebook.OnPostScoreListener;
import com.sromku.simple.fb.SimpleFacebook.OnProfileRequestListener;
import com.sromku.simple.fb.SimpleFacebook.OnPublishListener;
import com.sromku.simple.fb.SimpleFacebook.OnScoresRequestListener;
import com.sromku.simple.fb.SimpleFacebookConfiguration;
import com.sromku.simple.fb.entities.Feed;
import com.sromku.simple.fb.entities.Profile;




public class HelloWorld extends Cocos2dxActivity implements AsyncListener
{
	
    ///////////////////////// BEGIN SIMPLE FACEBOOK //////////////////////////////
	protected static final String DIR_TO_SAVE = "HelloWorld";
	protected static final String TAG = "JAVA_HELLO_WORLD";
	
	Permissions[] permissions = new Permissions[] {
			Permissions.BASIC_INFO,
			Permissions.USER_BIRTHDAY,
		    Permissions.USER_PHOTOS,
		    Permissions.EMAIL,
		    Permissions.PUBLISH_ACTION,
		    Permissions.PUBLISH_STREAM,
		    Permissions.READ_REQUESTS,
		    Permissions.USER_ACTIVITIES,
		    Permissions.USER_STATUS
		};
	

	Properties properties = new Properties.Builder()
    .add(Properties.ID)
    .add(Properties.FIRST_NAME)
    .add(Properties.NAME)
    .add(Properties.BIRTHDAY)
    .add(Properties.PICTURE)
    .build();

	
	//NEW SIMPLE FACEBOOK
	SimpleFacebook mSimpleFacebook;

    private void initSimleFacebook() {
    	
    	SimpleFacebookConfiguration configuration = new SimpleFacebookConfiguration.Builder()
        .setAppId("526834920767265")
        .setNamespace("helloworld")
        .setPermissions(permissions)
        .build();
    	
    	SimpleFacebook.setConfiguration(configuration);
    }
    
    @Override
    public void onResume() {
        super.onResume();
        mSimpleFacebook = SimpleFacebook.getInstance(this);
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        mSimpleFacebook.onActivityResult(this, requestCode, resultCode, data); 
        super.onActivityResult(requestCode, resultCode, data);
    } 

    ////////////////////////////////////////////////////////////////
    
    public void LogIn(JSONObject prms) {
    	Log.i(TAG, "CALL LOG IN");
    	
    	OnLoginListener onLoginListener = new OnLoginListener() {
    	    @Override
    	    public void onLogin() {
    	        Log.i(TAG, "onLogin");
    	        
    	        String jsonStr = "{\"isSuccess\" : true}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", null);
    	        }
    	    }

			@Override
			public void onThinking() {
				// TODO Auto-generated method stub
				Log.w(TAG, "onThinking");
			}

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.w(TAG, "onException");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", null);
    	        }
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.w(TAG, String.format("onFail: %s", reason));

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", null);
    	        }
			}

			@Override
			public void onNotAcceptingPermissions() {
				// TODO Auto-generated method stub
				Log.w(TAG, "onNotAcceptingPermissions");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted", null);
    	        }
			}
    	};

    	mSimpleFacebook.login(onLoginListener);
    }

    public void LogOut(JSONObject prms) {
    	Log.i(TAG, "CALL LOG OUT");
    	
    	// logout listener
    	OnLogoutListener onLogoutListener = new OnLogoutListener() {
    	    @Override
    	    public void onLogout() {
    	        Log.i(TAG, "onLogout");

    	        String jsonStr = "{\"isSuccess\" : true}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted", null);
    	        }
    	    }

			@Override
			public void onThinking() {
				// TODO Auto-generated method stub
				Log.i(TAG, "onThinking");
			}

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onException");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted", null);
    	        }
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted", null);
    	        }
			}
    	};
    	
    	mSimpleFacebook.logout(onLogoutListener);
    }
    
    public void GetProfile(JSONObject prms) {
    	Log.i(TAG, "CALL GET PROFILE");
    	
    	OnProfileRequestListener onProfileListener = new OnProfileRequestListener() {         
    	    @Override
    	    public void onComplete(Profile profile) {
    	        Log.i(TAG, "onCompletep");
    	        Log.i(TAG, "--id = " + profile.getId());
    	        Log.i(TAG, "--firstname = " + profile.getFirstName());
    	        Log.i(TAG, "--name = " + profile.getName());
    	        Log.i(TAG, "--birthday = " + profile.getBirthday());
    	        Log.i(TAG, "--picture = " + profile.getPicture());
    	        
    	        String jsonStr = "{\"isSuccess\" : true, " +
    	        		"\"id\": \"" + profile.getId() + "\"," +
    	        		"\"firstName\": \"" + profile.getFirstName() + "\"," +
    	        		"\"name\": \"" + profile.getName() + "\"," +
    	        		"\"birthday\": \"" + profile.getBirthday() + "\"," +
    	        		"\"picture\": \"" + profile.getPicture() + "\"" +
    	        		"}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetProfileCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetProfileCompleted", null);
    	        }
    	    }

			@Override
			public void onThinking() {
				// TODO Auto-generated method stub
				Log.i(TAG, "onThinking");
			}

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onException");
				
    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetProfileCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetProfileCompleted", null);
    	        }
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");
				
    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetProfileCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetProfileCompleted", null);
    	        }
			}  
    	};
    	
    	mSimpleFacebook.getProfile(properties, onProfileListener);
    }
    
    public void PublishFeed(JSONObject prms) {
    	Log.i(TAG, "CALL PUBLISH FEED");
    	Log.i(TAG, "Check if picture and link is exactly a link: http://...");
    	
    	boolean withDialog = false;
    	String message = null, 
    			name = null, 
    			caption = null, 
    			description = null, 
    			picture = null, 
    			link = null;
    			
//    	String 	action = null,
//    			actionLink = null,
//    			propertyName = null,
//    			propertyValue = null;
    	
    	try {
    		withDialog 	= prms.getBoolean("withDialog");
			message 	= prms.getString("message");
			name 		= prms.getString("name");
			caption 	= prms.getString("caption");
			description = prms.getString("description");
			picture 	= prms.getString("picture");
			link 		= prms.getString("link");
			
//			action 		= prms.getString("action");
//			actionLink 	= prms.getString("actionLink");
//			propertyName 	= prms.getString("propertyName");
//			propertyValue 	= prms.getString("propertyValue");
			
			Log.i(TAG, "withDialog: " + withDialog);
			Log.i(TAG, "message: " + message);
			Log.i(TAG, "name: " + name);
			Log.i(TAG, "caption: " + caption);
			Log.i(TAG, "description: " + description);
			Log.i(TAG, "picture: " + picture);
			Log.i(TAG, "link: " + link);
			
//			Log.i(TAG, "action: " + action);
//			Log.i(TAG, "actionLink: " + actionLink);
//			Log.i(TAG, "propertyName: " + propertyName);
//			Log.i(TAG, "propertyValue: " + propertyValue);
			
		} catch (JSONException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
    	
    	OnPublishListener onPublishListener = new OnPublishListener() {
    	    
    		@Override
    	    public void onComplete(String postId) {
    	        Log.i(TAG, "onComplete: postId = " + postId);
    	        
    	        String jsonStr = "{\"isSuccess\" : true, \"postId\": \"" + postId + "\"}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPublishFeedCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPublishFeedCompleted", null);
    	        }
    	    }

			@Override
			public void onThinking() {
				// TODO Auto-generated method stub
				Log.i(TAG, "onThinking");
			}

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onException: " + throwable.getMessage());

    	        String jsonStr = "{\"isSuccess\" : false, \"postId\": \"0\"}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPublishFeedCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPublishFeedCompleted", null);
    	        }
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail: " + reason);

    	        String jsonStr = "{\"isSuccess\" : false, \"postId\": \"0\"}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPublishFeedCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPublishFeedCompleted", null);
    	        }
			}
    	};
    	
    	Feed feed = new Feed.Builder()
        .setMessage(message)
        .setName(name)
        .setCaption(caption)
        .setDescription(description)
        .setPicture(picture)
        .setLink(link)
//        .addAction("Clone", "https://github.com/sromku/android-simple-facebook")
//	    .addProperty("Full documentation", "http://sromku.github.io/android-simple-facebook", "http://sromku.github.io/android-simple-facebook")
//	    .addProperty("Stars", "14")
        .build();
    	    	
    	mSimpleFacebook.publish(feed, onPublishListener);
    }
    
	public void GetAvatar(JSONObject prms) {
    	Log.i(TAG, "Get Avatar");
    	
    	String fbId = null;
    	int	width; 
    	int height;
    	String fileToSave;
    	
    	try {
			fbId 	= prms.getString("fbId");
			width 	= prms.getInt("width");
			height 	= prms.getInt("height");
			fileToSave = fbId + "_" + width + "_" + height + ".jpg";
						
			Log.i(TAG, "fbId: " + fbId);
			Log.i(TAG, "width: " + width);
			Log.i(TAG, "height: " + height);
			
			AvatarLoader avatarloader = new AvatarLoader(this, "GetAvatar", fbId, width, height, DIR_TO_SAVE, fileToSave);
			avatarloader.execute("");
		} catch (JSONException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
    }

	public void DeleteSavedAvatar(JSONObject prms) {
    	Log.i(TAG, "Delete Saved Avatar");
    	
    	String fbId = null;
    	int	width; 
    	int height;
    	String fileToSave;
    	
    	try {
			fbId 	= prms.getString("fbId");
			width 	= prms.getInt("width");
			height 	= prms.getInt("height");
			fileToSave = fbId + "_" + width + "_" + height + ".jpg";
			
			Log.i(TAG, "fbId: " + fbId);
			Log.i(TAG, "width: " + width);
			Log.i(TAG, "height: " + height);
			
			String sdCard = Environment.getExternalStorageDirectory().toString();
	        File myDir = new File(sdCard, DIR_TO_SAVE);
	
	        /*  if specified not exist create new */
	        if(!myDir.exists())
	        {
	            myDir.mkdir();
	            Log.v(TAG, "No director found, return now");
	            return;
	        }
	
	        /* checks the file and if it already exist delete */
	        File file = new File (myDir, fileToSave);

			Log.i(TAG, "FilePath: " + file.getAbsolutePath());
			
	        if (file.exists ()) {
	        	Log.v(TAG, "Already have file, delete now");
	        	file.delete();
	        	Log.v(TAG, "Delete Avatar Successfully.. :)");
	        } else {
	        	Log.v(TAG, "No file found, return now");
	        }

		} catch (JSONException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
    }

    public void PostScore(JSONObject prms) {
    	Log.i(TAG, "CALL POST SCORE");
    	    	
    	OnPostScoreListener onPostScoreListener = new OnPostScoreListener() {

			@Override
			public void onComplete() {
				// TODO Auto-generated method stub
				Log.i(TAG, "onComplete");

    	        String jsonStr = "{\"isSuccess\" : true}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPostScoreCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPostScoreCompleted", null);
    	        }
			}
			
			@Override
			public void onThinking() {
				// TODO Auto-generated method stub
				Log.i(TAG, "onThinking");
			}

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onException");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPostScoreCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPostScoreCompleted", null);
    	        }
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPostScoreCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onPostScoreCompleted", null);
    	        }
			}
    	};
    	
		try {
			int score = prms.getInt("score");
			Log.i(TAG, "SCORE = " + score);
			
	    	mSimpleFacebook.postScore(score, onPostScoreListener);
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
    
    public void GetScores(JSONObject prms) {
    	
    	
    	OnScoresRequestListener onScoresRequestListener = new OnScoresRequestListener() {

			@Override
			public void onComplete(JSONArray result) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onComplete");
				
				Log.i(TAG, "Number of scores = " + result.length());
				
				//Log.i(TAG, result.toString());
				String jsonStr = "{ \"isSuccess\": true, \"scores\": " + result.toString() + "}";
				Log.i(TAG, jsonStr);
				
				try {
	    	        JSONObject prmsToSend = null;
	    	        prmsToSend = new JSONObject(jsonStr);

	    	        AndroidNDKHelper.SendMessageWithParameters("onGetScoresCompleted", prmsToSend);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			
			@Override
			public void onThinking() {
				// TODO Auto-generated method stub
				Log.i(TAG, "onThinking");
			}

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onException");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetScoresCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetScoresCompleted", null);
    	        }
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

    	        String jsonStr = "{\"isSuccess\" : false}";
    	        JSONObject prmsToSend = null;
    	        
    	        try {
    				prmsToSend = new JSONObject(jsonStr);
    			}
    	        catch (JSONException e) {
    				// TODO Auto-generated catch block
    				e.printStackTrace();
    			}
    	        
    	        if (prmsToSend != null) {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetScoresCompleted", prmsToSend);
    	        } else {
    	        	AndroidNDKHelper.SendMessageWithParameters("onGetScoresCompleted", null);
    	        }
			}
    	};
    	
    	mSimpleFacebook.getScores(onScoresRequestListener);
    }
    
    public void InviteAll(JSONObject prms) {
    	
    	OnInviteListener onInviteListener = new OnInviteListener() {

			@Override
			public void onComplete(List<String> invitedFriends, String requestId) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onComplete");
				
				String jsonStr = "{ \"isSuccess\": true, \"requestId\": \"" +
						requestId +	"\", " +
						"\"invitedFriends\": [";
				
				for (int i = 0; i < invitedFriends.size(); i++) {
					jsonStr += "\"" + invitedFriends.get(i) + "\"";
					if(i < invitedFriends.size() - 1) {
						jsonStr += ",";
					}
				}
				jsonStr += "] }";				
				Log.i(TAG, jsonStr);
				
				try {
	    	        JSONObject prmsToSend = null;
	    	        prmsToSend = new JSONObject(jsonStr);
	    	        AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", prmsToSend);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", null);
				}
			}
    	   
    	    @Override
    	    public void onCancel() {
    	        Log.i(TAG, "onCancel: Canceled the dialog");
    	        
    	        try {
	    	        JSONObject prmsToSend = null;
	    	        prmsToSend = new JSONObject("{\"isSuccess\": false}");

	    	        AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", prmsToSend);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", null);
				}
    	    }

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onException");
    	        
    	        try {
	    	        JSONObject prmsToSend = null;
	    	        prmsToSend = new JSONObject("{\"isSuccess\": false}");

	    	        AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", prmsToSend);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", null);
				}
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");
    	        
    	        try {
	    	        JSONObject prmsToSend = null;
	    	        prmsToSend = new JSONObject("{\"isSuccess\": false}");

	    	        AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", prmsToSend);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					AndroidNDKHelper.SendMessageWithParameters("onInviteAllCompleted", null);
				}
			}
    	};

    	try {
			String message = prms.getString("message");
			Log.i(TAG, "MESSAGE = " + message);

	    	mSimpleFacebook.invite(message, onInviteListener);
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}    	
    }
    
    
    
    
    ///////////////////////////////////////////////////////////////

	@Override
	public void onAsyncComplete(String tag, String result) {
		// TODO Auto-generated method stub
		
		if( "GetAvatar" == tag) {
			Log.i("HELLO_WORLD", result);

	        String jsonStr = "{\"isSuccess\" : true, \"path\": \"" + result + "\"}";
	        JSONObject prmsToSend = null;
	        
	        try {
				prmsToSend = new JSONObject(jsonStr);
			}
	        catch (JSONException e) {
				e.printStackTrace();
			}
	        
	        AndroidNDKHelper.SendMessageWithParameters("onGetAvatarCompleted", prmsToSend);
		}
	}     
    
    ////////////////////////////////////////////////////////////////
    
    protected void onCreate(Bundle savedInstanceState){
		
        super.onCreate(savedInstanceState);

        try {
            PackageInfo info = getPackageManager().getPackageInfo(this.getPackageName(), PackageManager.GET_SIGNATURES);
            for (Signature signature : info.signatures) {
                MessageDigest md = MessageDigest.getInstance("SHA");
                md.update(signature.toByteArray());
                Log.e("MY KEY HASH:", Base64.encodeToString(md.digest(), Base64.DEFAULT));
            }
        }
        catch (NameNotFoundException e) {
        }
        catch (NoSuchAlgorithmException e) {
        }

        AndroidNDKHelper.SetNDKReciever(this);
        this.initSimleFacebook();
	}
    
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// HelloWorld should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }
}
