package com.dizuo.xapp;

import android.app.Activity;
import android.content.Intent;
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
				Intent intent = new Intent(Intent.ACTION_DIAL);
				startActivity(intent);
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
