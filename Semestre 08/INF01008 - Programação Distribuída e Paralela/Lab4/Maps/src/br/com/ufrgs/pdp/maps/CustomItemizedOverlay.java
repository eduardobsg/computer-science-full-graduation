package br.com.ufrgs.pdp.maps;

import java.util.ArrayList;

import android.app.AlertDialog;
import android.content.Context;
import android.graphics.drawable.Drawable;

import com.google.android.maps.ItemizedOverlay;
import com.google.android.maps.OverlayItem;

public class CustomItemizedOverlay extends ItemizedOverlay<OverlayItem> {

	private ArrayList<OverlayItem>mOverlays = new ArrayList<OverlayItem>() ;
	private Context context ;
	
	public CustomItemizedOverlay ( Context context , Drawable defaultMarker ) {
		super (boundCenterBottom(defaultMarker));
		this.context = context;
	}
	
	@Override
	protected OverlayItem createItem(int arg0) {
		return mOverlays.get(arg0);
	}

	@Override
	public int size() {
		return mOverlays.size();
	}
	
	public void addOverlay ( OverlayItem overlay ) {
		mOverlays.add ( overlay );
		populate();
	}
	
	protected boolean onTap (int index) {
		OverlayItem item = mOverlays.get(index);
		AlertDialog.Builder dialog = new AlertDialog.Builder( context );
		dialog.setTitle ( item . getTitle ());
		dialog.setMessage ( item . getSnippet ());
		dialog.show ();
		return true ;
	};

}
