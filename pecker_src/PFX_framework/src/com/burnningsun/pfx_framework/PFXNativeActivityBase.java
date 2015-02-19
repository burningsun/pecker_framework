/**
 * 
 */
package com.burnningsun.pfx_framework;


import android.app.NativeActivity;
import android.content.ContextWrapper;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
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
	        PackageManager pkgman = getPackageManager();
	        String strname = getPackageName();
	        
	        ApplicationInfo ai;
	        String var = "";

			try {

				ai = pkgman.getApplicationInfo(strname,
						PackageManager.GET_META_DATA);
				Bundle bu = ai.metaData;
				var = bu.getString("working_lib_name");
				//var = ai.metaData.getString("working_lib_name");
				
			} catch (Exception e) 
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	        System.out.print(var);


	 }
	 
	 static 
	 {
	     System.loadLibrary("PFX_CORE_GLES_S");
	 }


}
