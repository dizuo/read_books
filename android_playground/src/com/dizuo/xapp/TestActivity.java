package com.dizuo.xapp;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

// TestActivity 
// call DialogActivity
// call TestChildActivity

public class TestActivity extends Activity {

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.test_main);
		
		Button btn = (Button)findViewById(R.id.new_dialog);
		Button btn1 = (Button)findViewById(R.id.new_activity);
		
		btn.setOnClickListener(new Button.OnClickListener() {			
			@Override
			public void onClick(View v) {
				Intent intent = new Intent();
				intent.setClassName("com.dizuo.xapp", "com.dizuo.xapp.DialogActivity");
				intent.putExtra("name", "dizuo");
				startActivity(intent);
			}
		});
		
		btn1.setOnClickListener(new Button.OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent intent = new Intent();
				intent.setClassName("com.dizuo.xapp", "com.dizuo.xapp.NoteEditActivity");				
				startActivity(intent);
			}
		});
		
		((Button)findViewById(R.id.new_dial)).setOnClickListener(new Button.OnClickListener() {
			@Override
			public void onClick(View v) {
				
				// Intent intent = new Intent(Intent.ACTION_DIAL, Uri.parse("tel:15811339709"));
				// startActivity(intent);
				
				//Intent intent = new Intent(Intent.ACTION_CALL, Uri.parse("tel:556"));
				//startActivity(intent);

				Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://www.qq.com"));
				startActivity(intent);
				
/*				String[] reciver = new String[] { "dizuo@126.com" };  
		        String[] mySbuject = new String[] { "test" };  
		        String myCc = "cc";  
		        String mybody = "测试Email Intent";  
		        Intent myIntent = new Intent(android.content.Intent.ACTION_SEND);  
		        myIntent.setType("plain/text");  
		        myIntent.putExtra(android.content.Intent.EXTRA_EMAIL, reciver);  
		        myIntent.putExtra(android.content.Intent.EXTRA_CC, myCc);  
		        myIntent.putExtra(android.content.Intent.EXTRA_SUBJECT, mySbuject);  
		        myIntent.putExtra(android.content.Intent.EXTRA_TEXT, mybody);  		        
		        // Only For MIUI 指定使用系统默认的邮件发送
		        myIntent.setClassName("com.android.email", "com.kingsoft.mail.compose.ComposeActivity");		        
		        startActivity(Intent.createChooser(myIntent, "mail test"));*/
		        
				// open map
				// Uri uri = Uri.parse("geo:39.984186, 116.307503");  
				// Intent it = new Intent(Intent.ACTION_VIEW, uri);  
				// startActivity(it);  
								
			}
		});
		
		Log.i("dizuo", "onCreate");
		
	}
	
	protected void onDestroy() {
		super.onDestroy();
		
		Log.i("dizuo", "onDestroy");
	}
	
	protected void onResume() {
		super.onResume();
		Log.i("dizuo", "onResume");
	}
	
	protected void onPause() {
		super.onPause();
		Log.i("dizuo", "onPause");
	}
	
	protected void onStart() {
		super.onStart();
		Log.i("dizuo", "onStart");
	}
	
	protected void onStop() {
		super.onStop();
		Log.i("dizuo", "onStop");
	}
	
	protected void onRestart() {
		super.onRestart();
		
		Log.i("dizuo", "onRestart");		
	}
	
	protected void onRestoreInstanceState(Bundle savedInstanceState) {
		super.onRestoreInstanceState(savedInstanceState);
		
		Log.i("dizuo", "onRestoreInstanceState");
	}
	
	protected void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
		
		Log.i("dizuo", "onSaveInstanceState");
	}
	
}
