/**
 * 
 */
package com.burnningsun.pfx_framework;

import android.app.ActionBar;
import android.app.NativeActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
//import static junit.framework.Assert.*;
/**
 * @author cut
 *
 */
public class PFXNativeActivityBase extends NativeActivity {

	/**
	 * 
	 */
	public PFXNativeActivityBase() 
	{
		// TODO Auto-generated constructor stub
	}
	
	 @Override  
	 protected void onCreate(Bundle savedInstanceState) 
	 {
	        super.onCreate(savedInstanceState);
//	        View decorView = getWindow().getDecorView();
//	        int uiOptions = View.SYSTEM_UI_FLAG_FULLSCREEN;
//	        decorView.setSystemUiVisibility(uiOptions);
//	        ActionBar actionBar = getActionBar();
//	        actionBar.hide();
 

	 }

}