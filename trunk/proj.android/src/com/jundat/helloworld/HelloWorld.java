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

    //NEW
    private FrameLayout rootView = null;

    //NEW FACEBOOK
	Session m_Session;
	GraphUser m_User;
	

    //NEW
    /* Helper method to get the hold of Cocos2dx Changable View,
     * You can add others views using this view
     */
    private FrameLayout GetRootView()
    {
        if (this.rootView == null)
        {
            this.rootView = (FrameLayout)this.getWindow().getDecorView().findViewById(android.R.id.content);
        }
        return this.rootView;
    }

    //NEW
    private void AddButton()
    {
        Button tapButton = new Button(this);
        tapButton.setText("Tap to change text");
        tapButton.setLayoutParams(new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        
        tapButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                //NEW///////////////////////////////////////////
                // TODO Auto-generated method stub
                HelloWorld.this.ChangeSomethingInCocos();
            }
        });
        
        this.GetRootView().addView(tapButton);
    }
    //END NEW

	
    protected void onCreate(Bundle savedInstanceState){
		
        super.onCreate(savedInstanceState);

        //NEW
        // Try to get your hash key
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
        this.AddButton();
        //END NEW
	}

    //NEW    
    public void ChangeSomethingInCocos()
    {
        // If you want to change anything that cocos handles, please run it on GLThread
        // Because cocos is a non threaded environment, it is required to queue stuff there
        // Every call on NDK opens up a new thread, hence making inconsistency in cocos and NDK
        
        this.runOnGLThread(new Runnable()
                           {
            @Override
            public void run()
            {
                // TODO Auto-generated method stub
                AndroidNDKHelper.SendMessageWithParameters("ChangeLabelSelector", null);
            }
        });
    }


    public void SampleSelectorWithData(JSONObject prms)
    {
        Log.v("SampleSelector", "purchase something called");
        Log.v("SampleSelector", "Passed params are : " + prms.toString());
        
        String CPPFunctionToBeCalled = null;
        try
        {
            CPPFunctionToBeCalled = prms.getString("to_be_called");
        }
        catch (JSONException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("This is a sample popup on Android").
        setTitle("Hello World!").
        setNeutralButton("OK", null).show();
        
        String jsonStr = "{\"sample_dictionary\":{\"sample_array\":[\"1\",\"2\",\"3\",\"4\",\"5\",\"6\",\"7\",\"8\",\"9\",\"10\",\"11\"],\"sample_integer\":1234,\"sample_float\":12.34,\"sample_string\":\"a string\"}}";
        JSONObject prmsToSend = null;
        
        try
        {
            prmsToSend = new JSONObject(jsonStr);
        }
        catch (JSONException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        if (prmsToSend != null)
        {
            AndroidNDKHelper.SendMessageWithParameters(CPPFunctionToBeCalled, prmsToSend);
        }
        else
        {
            AndroidNDKHelper.SendMessageWithParameters(CPPFunctionToBeCalled, null);
        }
    }
    
    public void SampleSelector(JSONObject prms)
    {
        Log.v("SampleSelector", "purchase something called");
        Log.v("SampleSelector", "Passed params are : " + prms.toString());
        
        String CPPFunctionToBeCalled = null;
        try
        {
            CPPFunctionToBeCalled = prms.getString("to_be_called");
        }
        catch (JSONException e)
        {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("This is a sample popup on Android").
        setTitle("Hello World!").
        setNeutralButton("OK", null).show();
        
        AndroidNDKHelper.SendMessageWithParameters(CPPFunctionToBeCalled, null);
    }


    //END NEW
    
    
    
    
    
    
    
    
    
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
