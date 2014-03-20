package com.jundat.dautruongtrithuc;

import java.io.File;
import java.security.*;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.*;

import android.content.Intent;
import android.content.pm.*;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.os.Bundle;
import android.os.Environment;
import android.util.*;
import android.widget.Toast;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.FacebookDialog.ShareDialogFeature;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.OnCompleteListener;
import com.jundat.dautruongtrithuc.classes.AndroidNDKHelper;
import com.sromku.simple.fb.*;
import com.sromku.simple.fb.Permissions;
import com.sromku.simple.fb.SimpleFacebook.*;
import com.sromku.simple.fb.SimpleFacebookConfiguration;
import com.sromku.simple.fb.entities.*;

public class JNIFacebookFunctions implements AsyncListener {

	Cocos2dxActivity mainActivity;

	// /////////////////////// BEGIN SIMPLE FACEBOOK
	// //////////////////////////////

	protected static final String DIR_TO_SAVE = "DauTruongTriThuc";
	protected static final String TAG = "JAVA";

	Permissions[] permissions = new Permissions[] { Permissions.BASIC_INFO,
			Permissions.USER_BIRTHDAY, Permissions.USER_PHOTOS,
			Permissions.EMAIL, Permissions.PUBLISH_ACTION,
			Permissions.PUBLISH_STREAM, Permissions.READ_REQUESTS,
			Permissions.USER_ACTIVITIES, Permissions.USER_STATUS };

	Properties properties = new Properties.Builder().add(Properties.ID)
			.add(Properties.FIRST_NAME).add(Properties.NAME)
			.add(Properties.USER_NAME).add(Properties.BIRTHDAY)
			.add(Properties.PICTURE).build();

	// NEW SIMPLE FACEBOOK
	SimpleFacebook mSimpleFacebook;
	
	//NEW
	private UiLifecycleHelper uiHelper;

	// /////////////////////// BEGIN SIMPLE FACEBOOK
	// //////////////////////////////

	public JNIFacebookFunctions(Cocos2dxActivity mainActivity) {
		this.mainActivity = mainActivity;
	}
	
	public void onSaveInstanceState(Bundle outState) {
	    uiHelper.onSaveInstanceState(outState);
	}
	
	public void onCreate(Bundle savedInstanceState) {

		AndroidNDKHelper.SetNDKReciever(this);
		this.showHashKey();
		this.initSimleFacebook();
		
        //share
        uiHelper = new UiLifecycleHelper(this.mainActivity, new Session.StatusCallback() {  
			
			// callback when session changes state
			@SuppressWarnings("deprecation")
			@Override
			public void call(Session session, SessionState state, Exception exception) {
				// TODO Auto-generated method stub
			}
		});
        uiHelper.onCreate(savedInstanceState);
	}

	
	public void onPause() {
	    uiHelper.onPause();
	}

	public void onDestroy() {
	    uiHelper.onDestroy();
	}
	
	public void onResume() {
		mSimpleFacebook = SimpleFacebook.getInstance(mainActivity);
	    uiHelper.onResume();
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		mSimpleFacebook.onActivityResult(mainActivity, requestCode, resultCode, data);
		
		//share
		uiHelper.onActivityResult(requestCode, resultCode, data, new FacebookDialog.Callback() {
	        @Override
	        public void onError(FacebookDialog.PendingCall pendingCall, Exception error, Bundle data) {
				Log.i("SHARE_DIALOG", "onError");
	        	sendPublishFeedback(false, "");
	        }

	        @Override
	        public void onComplete(FacebookDialog.PendingCall pendingCall, Bundle data) {
	            boolean didComplete = FacebookDialog.getNativeDialogDidComplete(data);
	            if (didComplete) {
	            	Log.i("SHARE_DIALOG", "didComplete = true");
		            String completionGesture = FacebookDialog.getNativeDialogCompletionGesture(data);
	            	Log.i("SHARE_DIALOG", "completionGesture == " + completionGesture);
		            if (completionGesture.contains("post")) {
		            	Log.i("SHARE_DIALOG", "SUCCESS");
		            	String postId = FacebookDialog.getNativeDialogPostId(data);
		            	sendPublishFeedback(true, postId);
					} else { //cancel
		            	Log.i("SHARE_DIALOG", "ERROR");
						sendPublishFeedback(false, "");
					}
				} else {
	            	Log.i("SHARE_DIALOG", "didComplete == false");
					sendPublishFeedback(false, "");
				}	            
	        }
	    });
	}

	public void showHashKey() {
		try {
			PackageInfo info = mainActivity.getPackageManager().getPackageInfo(
					mainActivity.getPackageName(),
					PackageManager.GET_SIGNATURES);
			for (Signature signature : info.signatures) {
				MessageDigest md = MessageDigest.getInstance("SHA");
				md.update(signature.toByteArray());
				Log.e("MY KEY HASH:",
						Base64.encodeToString(md.digest(), Base64.DEFAULT));
			}
		} catch (NameNotFoundException e) {
		} catch (NoSuchAlgorithmException e) {
		}
	}

	public void initSimleFacebook() {

		SimpleFacebookConfiguration configuration = new SimpleFacebookConfiguration.Builder()
				.setAppId("526834920767265").setNamespace("dautruongtrithuc")
				.setPermissions(permissions).build();

		SimpleFacebook.setConfiguration(configuration);
	}

	// ///////////////////////////// Facebook Actions
	// /////////////////////////////////

	public void CheckLogIn(JSONObject prms) {
		boolean isLogIn = mSimpleFacebook.isLogin();

		String jsonStr = "{\"isSuccess\" : true, \"isLogIn\": " + isLogIn + "}";
		JSONObject prmsToSend = null;

		try {
			prmsToSend = new JSONObject(jsonStr);
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		AndroidNDKHelper.SendMessageWithParameters("onCheckLogInCompleted",
				prmsToSend);
	}

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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted",
						prmsToSend);
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted",
						prmsToSend);
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.w(TAG, String.format("onFail: %s", reason));

				String jsonStr = "{\"isSuccess\" : false}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted",
						prmsToSend);
			}

			@Override
			public void onNotAcceptingPermissions() {
				// TODO Auto-generated method stub
				Log.w(TAG, "onNotAcceptingPermissions");

				String jsonStr = "{\"isSuccess\" : false}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters("onLogInCompleted",
						prmsToSend);
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted",
						prmsToSend);
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted",
						prmsToSend);
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

				String jsonStr = "{\"isSuccess\" : false}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters("onLogOutCompleted",
						prmsToSend);

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
				Log.i(TAG, "--username = " + profile.getUsername());
				Log.i(TAG, "--birthday = " + profile.getBirthday());
				Log.i(TAG, "--picture = " + profile.getPicture());

				String jsonStr = "{\"isSuccess\" : true, " + "\"id\": \""
						+ profile.getId() + "\"," + "\"firstName\": \""
						+ profile.getFirstName() + "\"," + "\"name\": \""
						+ profile.getName() + "\"," + "\"username\": \""
						+ profile.getUsername() + "\"," + "\"birthday\": \""
						+ profile.getBirthday() + "\"," + "\"picture\": \""
						+ profile.getPicture() + "\"" + "}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onGetProfileCompleted", prmsToSend);
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onGetProfileCompleted", prmsToSend);
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

				String jsonStr = "{\"isSuccess\" : false}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onGetProfileCompleted", prmsToSend);
			}
		};

		mSimpleFacebook.getProfile(properties, onProfileListener);
	}

	public void PublishFeed(JSONObject prms) {
		String name = null, caption = null, description = null, picture = null, link = null;
		try {
			name = prms.getString("name");
			caption = prms.getString("caption");
			description = prms.getString("description");
			picture = prms.getString("picture");
			link = prms.getString("link");

			//share by Facebook App
	    	if (FacebookDialog.canPresentShareDialog(this.mainActivity.getApplicationContext(), ShareDialogFeature.SHARE_DIALOG)) {
	        	FacebookDialog shareDialog = new FacebookDialog.ShareDialogBuilder(this.mainActivity)
	        		.setName(name)
	        		.setCaption(caption)
	        		.setDescription(description)
	    	        .setLink(link)
	    	        .setPicture(picture)
	    	        .build();

	    		uiHelper.trackPendingDialogCall(shareDialog.present());
			} else {
				//share by web dialog
				Bundle params = new Bundle();
			    params.putString("name", name);
			    params.putString("caption", caption);
			    params.putString("description", description);
			    params.putString("link", link);
			    params.putString("picture", picture);

			    WebDialog feedDialog = (
		            new WebDialog.FeedDialogBuilder(mainActivity, Session.getActiveSession(), params))
		            .setOnCompleteListener(new OnCompleteListener() {

		                @Override
		                public void onComplete(Bundle values, FacebookException error) {
		                    if (error == null) {
		                    	Log.i("SHARE", "error");
		                        final String postId = values.getString("post_id");
		                        if (postId != null) {
			                    	Log.i("SHARE", "postId != null");
		                        	sendPublishFeedback(true, postId);
		                        } else {
			                    	Log.i("SHARE", "postId == null");
		                        	sendPublishFeedback(false, "");
		                        }
		                    } else if (error instanceof FacebookOperationCanceledException) {
		                    	Log.i("SHARE", "FacebookOperationCanceledException");
		                    	sendPublishFeedback(false, "");
		                    } else {
		                    	Log.i("SHARE", "Unknown");
		                    	sendPublishFeedback(false, "");
		                    }
		                }
		            })
		            .build();
			    feedDialog.show();
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public void sendPublishFeedback(boolean isSuccess, String postId) {
		String jsonStr = "{\"isSuccess\" : " + isSuccess + ", \"postId\": \"" + postId + "\"}";
		Log.i(TAG, jsonStr);
		JSONObject prmsToSend = null;
		try {
			prmsToSend = new JSONObject(jsonStr);
		} catch (JSONException e) {
			e.printStackTrace();
		}

		AndroidNDKHelper.SendMessageWithParameters("onPublishFeedCompleted", prmsToSend);
	}
	
	public void AutoPublishFeed(JSONObject prms) {
		Log.i(TAG, "AUTO CALL PUBLISH FEED");
		Log.i(TAG, "Check if picture and link is exactly a link: http://...");

		String message = null, name = null, caption = null, description = null, picture = null, link = null;

		try {
			message = prms.getString("message");
			name = prms.getString("name");
			caption = prms.getString("caption");
			description = prms.getString("description");
			picture = prms.getString("picture");
			link = prms.getString("link");

			Log.i(TAG, "message: " + message);
			Log.i(TAG, "name: " + name);
			Log.i(TAG, "caption: " + caption);
			Log.i(TAG, "description: " + description);
			Log.i(TAG, "picture: " + picture);
			Log.i(TAG, "link: " + link);

		} catch (JSONException e) {
			// TODO: handle exception
			e.printStackTrace();
		}

		OnPublishListener onPublishListener = new OnPublishListener() {

			@Override
			public void onComplete(String postId) {
				Log.i(TAG, "onComplete: postId = " + postId);

				String jsonStr = "{\"isSuccess\" : true, \"postId\": \""
						+ postId + "\"}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onPublishFeedCompleted", prmsToSend);
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onPublishFeedCompleted", prmsToSend);
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail: " + reason);

				String jsonStr = "{\"isSuccess\" : false, \"postId\": \"0\"}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onPublishFeedCompleted", prmsToSend);
			}
		};

		Feed feed = new Feed.Builder().setMessage(message).setName(name)
				.setCaption(caption).setDescription(description)
				.setPicture(picture).setLink(link).build();

		mSimpleFacebook.publish(feed, onPublishListener);
	}

	public void GetAvatar(JSONObject prms) {
		Log.i(TAG, "Get Avatar");

		String fbId = null;
		int width;
		int height;
		String fileToSave;

		try {
			fbId = prms.getString("fbId");
			width = prms.getInt("width");
			height = prms.getInt("height");
			fileToSave = fbId + "_" + width + "_" + height + ".jpg";

			Log.i(TAG, "fbId: " + fbId);
			Log.i(TAG, "width: " + width);
			Log.i(TAG, "height: " + height);

			AvatarLoader avatarloader = new AvatarLoader(this, "GetAvatar",
					fbId, width, height, DIR_TO_SAVE, fileToSave);
			avatarloader.execute("");
		} catch (JSONException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}

	public void DeleteSavedAvatar(JSONObject prms) {
		Log.i(TAG, "Delete Saved Avatar");

		String fbId = null;
		int width;
		int height;
		String fileToSave;

		try {
			fbId = prms.getString("fbId");
			width = prms.getInt("width");
			height = prms.getInt("height");
			fileToSave = fbId + "_" + width + "_" + height + ".jpg";

			Log.i(TAG, "fbId: " + fbId);
			Log.i(TAG, "width: " + width);
			Log.i(TAG, "height: " + height);

			String sdCard = Environment.getExternalStorageDirectory()
					.toString();
			File myDir = new File(sdCard, DIR_TO_SAVE);

			/* if specified not exist create new */
			if (!myDir.exists()) {
				myDir.mkdir();
				Log.v(TAG, "No director found, return now");
				return;
			}

			/* checks the file and if it already exist delete */
			File file = new File(myDir, fileToSave);

			Log.i(TAG, "FilePath: " + file.getAbsolutePath());

			if (file.exists()) {
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onPostScoreCompleted", prmsToSend);
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onPostScoreCompleted", prmsToSend);
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

				String jsonStr = "{\"isSuccess\" : false}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onPostScoreCompleted", prmsToSend);
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

				// Log.i(TAG, result.toString());
				String jsonStr = "{ \"isSuccess\": true, \"scores\": "
						+ result.toString() + "}";
				Log.i(TAG, jsonStr);

				JSONObject prmsToSend = null;
				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				AndroidNDKHelper.SendMessageWithParameters(
						"onGetScoresCompleted", prmsToSend);
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
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onGetScoresCompleted", prmsToSend);
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

				String jsonStr = "{\"isSuccess\" : false}";
				JSONObject prmsToSend = null;

				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onGetScoresCompleted", prmsToSend);
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

				String jsonStr = "{ \"isSuccess\": true, \"requestId\": \""
						+ requestId + "\", " + "\"invitedFriends\": [";

				for (int i = 0; i < invitedFriends.size(); i++) {
					jsonStr += "\"" + invitedFriends.get(i) + "\"";
					if (i < invitedFriends.size() - 1) {
						jsonStr += ",";
					}
				}
				jsonStr += "] }";
				Log.i(TAG, jsonStr);

				JSONObject prmsToSend = null;
				try {
					prmsToSend = new JSONObject(jsonStr);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				AndroidNDKHelper.SendMessageWithParameters(
						"onInviteAllCompleted", prmsToSend);
			}

			@Override
			public void onCancel() {
				Log.i(TAG, "onCancel: Canceled the dialog");

				JSONObject prmsToSend = null;
				try {
					prmsToSend = new JSONObject("{\"isSuccess\": false}");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onInviteAllCompleted", prmsToSend);
			}

			@Override
			public void onException(Throwable throwable) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onException");

				JSONObject prmsToSend = null;
				try {
					prmsToSend = new JSONObject("{\"isSuccess\": false}");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onInviteAllCompleted", prmsToSend);
			}

			@Override
			public void onFail(String reason) {
				// TODO Auto-generated method stub
				Log.i(TAG, "onFail");

				JSONObject prmsToSend = null;
				try {
					prmsToSend = new JSONObject("{\"isSuccess\": false}");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				AndroidNDKHelper.SendMessageWithParameters(
						"onInviteAllCompleted", prmsToSend);
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

	// ///////////////////////////// Non-facebook functions
	// /////////////////////////////////

	public void Rate(JSONObject prms) {
		Log.i(TAG, "Rate app");
		AppRater.showRateDialog(this.mainActivity, null, this);
	}

	public void onRateCompleted(String responseType) {
		String jsonStr = "{\"isSuccess\" : true, " + "\"responseType\": \""
				+ responseType + "\"" + "}";
		JSONObject prmsToSend = null;

		try {
			prmsToSend = new JSONObject(jsonStr);
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		AndroidNDKHelper.SendMessageWithParameters("onRateCompleted",
				prmsToSend);
	}

	// /////////////////////////////////////////////////////////////

	@Override
	public void onAsyncComplete(String tag, String result) {
		// TODO Auto-generated method stub

		if ("GetAvatar" == tag) {
			Log.i("HELLO_WORLD", result);

			String jsonStr = "{\"isSuccess\" : true, \"path\": \"" + result
					+ "\"}";
			JSONObject prmsToSend = null;

			try {
				prmsToSend = new JSONObject(jsonStr);
			} catch (JSONException e) {
				e.printStackTrace();
			}

			AndroidNDKHelper.SendMessageWithParameters("onGetAvatarCompleted",
					prmsToSend);
		}
	}

	// //////////////////////////////////////////////////////////////
}
