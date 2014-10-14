package com.dizuo.xapp;

import android.app.ActionBar;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.RelativeLayout;

public class NoteEditActivity extends Activity {
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);		
		setContentView(R.layout.note_edit_main);
		
		ActionBar bar = getActionBar();
		bar.setDisplayHomeAsUpEnabled(true);
		bar.show();
		
		RelativeLayout rl = (RelativeLayout) this.findViewById(R.id.note_edit_hd);		
		rl.setOnClickListener(new View.OnClickListener(){
			@Override
            public void onClick(View view) {
                Log.i("dizuo", "xxxx new xxx");
            }
		});
		
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case android.R.id.home:
			
			Intent intent = new Intent(this, MainActivity.class);
			intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			startActivity(intent);
			
			break;
		default:
			return super.onOptionsItemSelected(item);
		}
		
		return false;
	}
}
