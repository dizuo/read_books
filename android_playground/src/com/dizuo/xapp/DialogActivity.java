package com.dizuo.xapp;

import com.dizuo.xapp.R;

import android.app.Activity;
import android.os.Bundle;
import android.view.Window;
import android.widget.TextView;

public class DialogActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
	    // Be sure to call the super class.
	    super.onCreate(savedInstanceState);
	
	    requestWindowFeature(Window.FEATURE_LEFT_ICON);
	
	    setContentView(R.layout.dialog_activity);
	    
	    // See assets/res/any/layout/dialog_activity.xml for this
	    // view layout definition, which is being set here as
	    // the content of our screen.
	    getWindow().setTitle("This is just a test");
	    
	    Bundle extras = getIntent().getExtras();
	    if (extras != null) {
	    	String value = extras.getString("name");
	    	((TextView) findViewById(R.id.dial_text)).setText(value);
	    }

	    getWindow().setFeatureDrawableResource(Window.FEATURE_LEFT_ICON,
	            android.R.drawable.ic_dialog_alert);	
	}
	   
}
