<?php
/**
 * Helper classes
 */

class CHelper {
	public static function getCountry($code) {
		 $query = db_select('jl_countries', 'c');
    
	    $query 
	    ->condition('iso_alpha3', $code)
	    ->fields('c', array('id_countries','name','fr','iso_alpha2','iso_alpha3','iso_numeric','currency_code','currency_name','currrency_symbol')); 
	    $result = $query->execute(); 

	    foreach($result as $row) { 
	    	if(isset($row->iso_alpha3) && $row->iso_alpha3 == $code)
	    		return $row;
	    }

	    return null;
	}

	public static function getCountyName($code, $lang) {
		$country = self::getCountry($code);

		if($country == null)
			return;
		if($lang == "fr")
			return $country->fr;
		else
			return $country->name;
	}

	public static function getCountryCurrency($code) {
		$country = self::getCountry($code);
		if($country == null)
			return;
		return $country['currrency_symbol'];
	}

	public static function getCountryCurrencyN($code) {
		$country = self::getCountry($code);
		if($country == null)
			return;
		return $country['currency_name'];
	}
}


class CDate {
	public static function displayFromDB($time) {

	}
}