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

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;

import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.facebook.model.GraphUser;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.FacebookDialog.ShareDialogFeature;

//NEW
import com.jundat.helloworld.classes.AndroidNDKHelper;
import com.sromku.simple.fb.Permissions;
import com.sromku.simple.fb.Properties;
import com.sromku.simple.fb.SimpleFacebook;
import com.sromku.simple.fb.SimpleFacebook.OnLoginListener;
import com.sromku.simple.fb.SimpleFacebook.OnProfileRequestListener;
import com.sromku.simple.fb.SimpleFacebookConfiguration;
import com.sromku.simple.fb.entities.Profile;

import org.json.JSONException;
import org.json.JSONObject;
import android.app.AlertDialog;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.FrameLayout;
//END NEW



public class HelloWorld extends Cocos2dxActivity
{
	
    ///////////////////////// BEGIN SIMPLE FACEBOOK //////////////////////////////
	
	protected static final String TAG = "JAVA_HELLO_WORLD";
	
	Permissions[] permissions = new Permissions[] {
			Permissions.BASIC_INFO,
			Permissions.USER_BIRTHDAY,
		    Permissions.USER_PHOTOS,
		    Permissions.EMAIL,
		    Permissions.PUBLISH_ACTION
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

    //
    
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
    
    public void GetProfile(JSONObject prms) {
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
    
    ///////////////////////// END SIMPLE FACEBOOK //////////////////////////////
	
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
