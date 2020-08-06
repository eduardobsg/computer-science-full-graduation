package br.com.ufrgs.pdp.maps;

import java.util.List;

import br.com.ufrgs.pdp.localizacao.R;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapActivity;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;
import com.google.android.maps.MyLocationOverlay;
import com.google.android.maps.OverlayItem;
import com.google.android.maps.Overlay;

import android.os.Bundle;
import android.graphics.drawable.Drawable;
import android.view.Menu;

public class MainActivity extends MapActivity {

	private MapController mapController ;
	private MapView mapView ;
	private CustomItemizedOverlay itemizedOverlay ;
	private MyLocationOverlay myLocationOverlay ;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		mapView = ( MapView ) findViewById (R.id.mapview);
		mapView.setBuiltInZoomControls( true );
		
		mapView.setSatellite( false );
		
		mapController = mapView.getController ();
		mapController.setZoom (14) ;
		
		myLocationOverlay = new MyLocationOverlay (this , mapView );
		mapView.getOverlays().add( myLocationOverlay );
		
		List < Overlay> mapOverlays = mapView . getOverlays ();
		
		Drawable drawable = this.getResources().getDrawable (R.drawable.ic_launcher );
		itemizedOverlay = new CustomItemizedOverlay (this , drawable );
		
		GeoPoint point = new GeoPoint ( -23570794 , -46690747) ;
		OverlayItem overlayitem = new OverlayItem (point , "PDP", "Introdução a Android");
		
		itemizedOverlay . addOverlay ( overlayitem );
		
		mapOverlays.add(itemizedOverlay);
		/*
		mv=(MapView)findViewById(R.id.mapView);

	    String coordinates[] = {"1.352566007", "103.78921587"};
	    double lat = Double.parseDouble(coordinates[0]);
	    double lng = Double.parseDouble(coordinates[1]);
	    
	    showLocation(mv, lat, lng);
	    */
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	protected final void showLocation(MapView mv, double latitude, double longitude) {
    	// converte info. de latitude e longitude para micro-graus
        final GeoPoint iiloc = new GeoPoint((int) (latitude*1E6), (int) (longitude*1E6));
        // TODO: obtem referencia para interface de controle do mapa a partir do objeto MapView
        MapController mapController = mv.getController();
        // TODO: indica ao controlador do mapa para centralizar a exibilição em torno de iiloc
        mapController.setCenter(iiloc);
        // TODO: ajustar nível de zoom para 16
        mapController.setZoom(16);
        // TODO: inserir controles de zoom
        mv.setBuiltInZoomControls(true);
}

	@Override
	protected boolean isRouteDisplayed() {
		// TODO Auto-generated method stub
		return false;
	}

}
